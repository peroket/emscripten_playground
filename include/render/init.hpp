#pragma once

#include <emscripten.h>

namespace Render
{
EM_JS(void, initGlAndLoadShaders, (), {
    let gl = document.getElementById('canvas').getContext('webgl2');

    if (!gl)
        throw Error('Could not load WebGl2 context');

    Module['gl'] = gl;

    const folder = 'shaders';
    const files  = FS.readdir(folder);
    let shaders  = new Map();
    let programs = new Map();

    for (file of files)
    {
        let type = undefined;

        switch (PATH.extname(file))
        {
        case '.vert':
            type = gl.VERTEX_SHADER;
            break;

        case '.frag':
            type = gl.FRAGMENT_SHADER;
            break;

        default:
        }

        if (type == undefined)
            continue;

        // Compile the shader we got
        const shader = gl.createShader(type);
        const source = FS.readFile(PATH.join(folder, file), {encoding : 'utf8', flags : 'r'});

        gl.shaderSource(shader, source);
        gl.compileShader(shader);

        if (!gl.getShaderParameter(shader, gl.COMPILE_STATUS))
        {
            Module.printErr(gl.getShaderInfoLog(shader));
            throw Error('Could not compile shader ' + file);
        }

        // Check if we have the other shader
        const name  = file.slice(0, -5);
        const other = shaders.get(name);

        // If we do not, then store the current one and process the next shader
        if (!other)
        {
            shaders.set(name, shader);
            continue;
        }

        // Otherwise, we can create the program
        const program = gl.createProgram();

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
