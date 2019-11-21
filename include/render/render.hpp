#pragma once

#include <emscripten.h>

EM_JS(void, initDraw, (), {
    var gl = Module.gl;
    // var program = Module.glPrograms.get('simple_test');

    // // look up where the vertex data needs to go.
    // var positionAttributeLocation = gl.getAttribLocation(program, "a_position");

    // // Create a buffer and put three 2d clip space points in it
    // var positionBuffer = gl.createBuffer();

    // // Bind it to ARRAY_BUFFER (think of it as ARRAY_BUFFER = positionBuffer)
    // gl.bindBuffer(gl.ARRAY_BUFFER, positionBuffer);

    // var positions = [
    //     0,
    //     0,
    //     0,
    //     0.5,
    //     0.7,
    //     0,
    // ];
    // gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(positions), gl.STATIC_DRAW);

    // // Create a vertex array object (attribute state)
    // var vao = gl.createVertexArray();

    // // and make it the one we're currently working with
    // gl.bindVertexArray(vao);

    // // Turn on the attribute
    // gl.enableVertexAttribArray(positionAttributeLocation);

    // // Tell the attribute how to get data out of positionBuffer (ARRAY_BUFFER)
    // var size      = 2;        // 2 components per iteration
    // var type      = gl.FLOAT; // the data is 32bit floats
    // var normalize = false;    // don't normalize the data
    // var stride = 0; // 0 = move forward size * sizeof(type) each iteration to get the next
    // position var offset = 0; // start at the beginning of the buffer
    // gl.vertexAttribPointer(positionAttributeLocation, size, type, normalize, stride, offset);

    // // webglUtils.resizeCanvasToDisplaySize(gl.canvas);

    // // Tell WebGL how to convert from clip space to pixels
    // gl.viewport(0, 0, gl.canvas.width, gl.canvas.height);

    // Clear the canvas
    gl.clearColor(0, 0, 0, 0);
    gl.clear(gl.COLOR_BUFFER_BIT);

    // // Tell it to use our program (pair of shaders)
    // gl.useProgram(program);

    // // Bind the attribute/buffer set we want.
    // gl.bindVertexArray(vao);

    // // draw
    // var primitiveType = gl.TRIANGLES;
    // var offset        = 0;
    // var count         = 3;
    // gl.drawArrays(primitiveType, offset, count);
});
