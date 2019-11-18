#pragma once

#include <emscripten.h>

namespace Render
{
EM_JS(void, initGlAndLoadShaders, (), {
    var gl = document.getElementById('canvas').getContext('webgl2');

    if (!gl)
        throw Error('Could not load WebGl2 context');

    Module['gl'] = gl;

    var folder   = 'shaders';
    var files    = FS.readdir(folder);
    var shaders  = new Map();
    var programs = new Map();

    for (file of files)
    {
        var type = undefined;

        switch (PATH.extname(file))
        {
        case '.vert':
            type = gl.VERTEX_SHADER;
            break;

        case '.frag':
            type = gl.FRAGMENT_SHADER;
            break;

        default:
            found = false;
        }

        if (type == undefined)
            continue;

        // Compile the shader we got
        var shader = gl.createShader(type);
        var source = FS.readFile(PATH.join(folder, file), {encoding : 'utf8', flags : 'r'});

        gl.shaderSource(shader, source);
        gl.compileShader(shader);

        if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS))
        {
            Module.printErr(gl.getShaderInfoLog(shader));
            throw Error('Could not compile shader ' + file);
        }

        // Check if we have the other shader
        var name  = file.slice(0, -5);
        var other = shaders.get(name);

        // If we do not, then store the current one and process the next shader
        if (!other)
        {
            shaders.set(name, shader);
            continue;
        }

        // Otherwise, we can create the program
        var program = gl.createProgram();

        gl.attachShader(program, shader);
        gl.attachShader(program, other);
        gl.linkProgram(program);

        if (!gl.getProgramParameter(program, gl.LINK_STATUS))
        {
            Module.printErr(gl.getProgramInfoLog(program));
            throw Error('Could not link program ' + name);
        }

        // And save it in our list
        programs.set(name, program);
    }

    // Finaly, save the compiled programs so that we can use them to render
    Module['glPrograms'] = programs;
})
}
