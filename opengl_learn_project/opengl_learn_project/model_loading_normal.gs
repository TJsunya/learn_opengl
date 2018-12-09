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
// ����Ӧ�ô���ר�ŵ�fragment shader
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
    GenerateLine(0); // ��һ�����㷨��
    GenerateLine(1); // �ڶ������㷨��
    GenerateLine(2); // ���������㷨��
}