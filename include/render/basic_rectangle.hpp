#pragma once

#include <emscripten.h>

namespace Render
{
EM_JS(void,
      renderBasicRectangle,
      (float xMin,
       float yMin,
       float xMax,
       float yMax,
       float depth,
       float r,
       float g,
       float b,
       float a),
      {
          const gl      = Module.gl;
          const program = Module.glPrograms.get('basic_rectangle');

          // look up where the vertex data needs to go.
          const positionAttributeLocation = gl.getAttribLocation(program, "i_position");
          const depthLocation             = gl.getUniformLocation(program, "u_depth");
          const colorLocation             = gl.getUniformLocation(program, "u_color");

          // Create a buffer and put three 2d clip space points in it
          const positionBuffer = gl.createBuffer();

          // Bind it to ARRAY_BUFFER (think of it as ARRAY_BUFFER = positionBuffer)
          gl.bindBuffer(gl.ARRAY_BUFFER, positionBuffer);

          const positions = [ xMin, yMin, xMin, yMax, xMax, yMax, xMax, yMin ];
          gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(positions), gl.STATIC_DRAW);

          // Create a vertex array object (attribute state)
          const vao = gl.createVertexArray();

          // and make it the one we're currently working with
          gl.bindVertexArray(vao);

          // Turn on the attribute
          gl.enableVertexAttribArray(positionAttributeLocation);

          // Tell the attribute how to get data out of positionBuffer (ARRAY_BUFFER)
          let size        = 2;        // 2 components per iteration
          const type      = gl.FLOAT; // the data is 32bit floats
          const normalize = false;    // don't normalize the data
          const stride =
              0; // 0 = move forward size * sizeof(type) each iteration to get the next position
          let offset = 0; // start at the beginning of the buffer
          gl.vertexAttribPointer(positionAttributeLocation, size, type, normalize, stride, offset);

          // webglUtils.resizeCanvasToDisplaySize(gl.canvas);

          // Tell WebGL how to convert from clip space to pixels
          gl.viewport(0, 0, gl.canvas.width, gl.canvas.height);

          // Clear the canvas
          gl.clearColor(0, 0, 0, 0);
          //   gl.clear(gl.COLOR_BUFFER_BIT);

          // Tell it to use our program (pair of shaders)
          gl.useProgram(program);

          // Bind the attribute/buffer set we want.
          gl.bindVertexArray(vao);

          // draw
          gl.uniform1f(depthLocation, depth);
          gl.uniform4f(colorLocation, r, g, b, a);

          const primitiveType = gl.TRIANGLE_FAN;
          offset              = 0;
          size                = 4;
          gl.drawArrays(primitiveType, offset, size);
      })
}