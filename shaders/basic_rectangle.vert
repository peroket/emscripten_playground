#version 300 es

uniform float u_depth;

in vec2 i_position;

void main()
{
    gl_Position = vec4(i_position, u_depth, 1.0);
}