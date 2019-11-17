#pragma once

#include <emscripten.h>

EM_JS(void, init, (), {
    Module['createShader'] = function(type, source)
    {
        var gl     = Module.gl;
        var shader = gl.createShader(type);

        gl.shaderSource(shader, source);
        gl.compileShader(shader);

        var success = gl.getShaderParameter(shader, gl.COMPILE_STATUS);
        if (success)
        {
            return shader;
        }

        console.log(gl.getShaderInfoLog(shader));
        gl.deleteShader(shader);

        return undefined;
    };

    Module['createProgram'] = function(vertexShader, fragmentShader)
    {
        var gl      = Module.gl;
        var program = gl.createProgram();

        gl.attachShader(program, vertexShader);
        gl.attachShader(program, fragmentShader);
        gl.linkProgram(program);

        var success = gl.getProgramParameter(program, gl.LINK_STATUS);
        if (success)
        {
            return program;
        }

        console.log(gl.getProgramInfoLog(program));
        gl.deleteProgram(program);

        return undefined;
    };

    Module['gl'] = document.getElementById('canvas').getContext('webgl2');
});

EM_JS(void, initDraw, (), {
    var gl = Module.gl;
    if (!gl)
    {
        return;
    }

    var vertexShaderSource =
        '#version 300 es\nin vec4 a_position;\nvoid main(){gl_Position = a_position;}';
    var fragmentShaderSource =
        '#version 300 es\nprecision mediump float;\nout vec4 outColor;\nvoid main(){outColor = vec4(1, 0, 0.5, 1);}';

    // create GLSL shaders, upload the GLSL source, compile the shaders
    var vertexShader   = Module.createShader(gl.VERTEX_SHADER, vertexShaderSource);
    var fragmentShader = Module.createShader(gl.FRAGMENT_SHADER, fragmentShaderSource);

    // Link the two shaders into a program
    var program = Module.createProgram(vertexShader, fragmentShader);

    // look up where the vertex data needs to go.
    var positionAttributeLocation = gl.getAttribLocation(program, "a_position");

    // Create a buffer and put three 2d clip space points in it
    var positionBuffer = gl.createBuffer();

    // Bind it to ARRAY_BUFFER (think of it as ARRAY_BUFFER = positionBuffer)
    gl.bindBuffer(gl.ARRAY_BUFFER, positionBuffer);

    var positions = [
        0,
        0,
        0,
        0.5,
        0.7,
        0,
    ];
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(positions), gl.STATIC_DRAW);

    // Create a vertex array object (attribute state)
    var vao = gl.createVertexArray();

    // and make it the one we're currently working with
    gl.bindVertexArray(vao);

    // Turn on the attribute
    gl.enableVertexAttribArray(positionAttributeLocation);

    // Tell the attribute how to get data out of positionBuffer (ARRAY_BUFFER)
    var size      = 2;        // 2 components per iteration
    var type      = gl.FLOAT; // the data is 32bit floats
    var normalize = false;    // don't normalize the data
    var stride = 0; // 0 = move forward size * sizeof(type) each iteration to get the next position
    var offset = 0; // start at the beginning of the buffer
    gl.vertexAttribPointer(positionAttributeLocation, size, type, normalize, stride, offset);

    // webglUtils.resizeCanvasToDisplaySize(gl.canvas);

    // Tell WebGL how to convert from clip space to pixels
    gl.viewport(0, 0, gl.canvas.width, gl.canvas.height);

    // Clear the canvas
    gl.clearColor(0, 0, 0, 0);
    gl.clear(gl.COLOR_BUFFER_BIT);

    // Tell it to use our program (pair of shaders)
    gl.useProgram(program);

    // Bind the attribute/buffer set we want.
    gl.bindVertexArray(vao);

    // draw
    var primitiveType = gl.TRIANGLES;
    var offset        = 0;
    var count         = 3;
    gl.drawArrays(primitiveType, offset, count);
});