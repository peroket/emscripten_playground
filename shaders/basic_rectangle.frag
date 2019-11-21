#version 300 es

precision mediump float;

uniform vec4 u_color;

out vec4 o_outColor;

void main()
{
    o_outColor = u_color;
}