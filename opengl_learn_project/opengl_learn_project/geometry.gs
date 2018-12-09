#version 330 core

layout (points) in;
layout (triangle_strip, max_vertices=5) out;

in VS_OUT{
	vec3 color;
}gs_in[];

out VS_OUT{
	vec3 color;
} gs_out;

void build_house(vec4 position){
	gl_Position = position + vec4(-0.2, -0.2, 0.0, 0.0);
	gs_out.color = gs_in[0].color;
	EmitVertex();
	gl_Position = position + vec4(0.2, -0.2, 0.0 ,0.0);
	gs_out.color = gs_in[0].color + vec3(0.5,0.5,0.5);
	EmitVertex();
	gl_Position = position + vec4(-0.2, 0.2, 0.0, 0.0);
	gs_out.color = gs_in[0].color;
	EmitVertex();
	gl_Position = position + vec4(0.2, 0.2, 0.0, 0.0);
	gs_out.color = gs_in[0].color;
	EmitVertex();
	gl_Position = position + vec4(0.0, 0.4, 0.0, 0.0);
	gs_out.color = gs_in[0].color;
	EmitVertex();
	EndPrimitive();
}

void main(){
	build_house(gl_in[0].gl_Position);
	
}