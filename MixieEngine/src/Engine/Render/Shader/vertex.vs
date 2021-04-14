#version 330 core

layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec3 vertexColor;
out vec3 color;

void main() 
{
color = vertexColor;
gl_Position = vec4(vertexPos,1.0);
//gl_Position = vec4(vertexPos.x,-vertexPos.y,vertexPos.z,1.0);//reverse triangles
};