#version 330 core

layout (triangles) in;
layout (line_strip, max_vertices=6) out;

in VS_OUT{
 vec2 TexCoords;
 vec3 normal;
 vec3 FragPos;
} gs_in[];


out VS_OUT{
 vec2 TexCoords;
 vec3 normal;
 vec3 FragPos;
} gs_out;

const float MAGNITUDE = 0.4;
// 这里应该搭配专门的fragment shader
void GenerateLine(int index)
{
    gl_Position = gl_in[index].gl_Position;
    EmitVertex();
    gl_Position = gl_in[index].gl_Position + vec4(gs_in[index].normal, 0.0) * MAGNITUDE;
    EmitVertex();
    EndPrimitive();
}

void main()
{
    GenerateLine(0); // 第一个顶点法线
    GenerateLine(1); // 第二个顶点法线
    GenerateLine(2); // 第三个顶点法线
}