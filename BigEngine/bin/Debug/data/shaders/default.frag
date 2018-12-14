#version 330 core

in vec3 vert_color;
out vec4 frag_color;
vec3 lum = vec3(0.299,0.587, 0.114);
void main()
{
	//frag_color = vec4( vec3(dot(vert_color.rgb, lum)) ,1.0f);
	frag_color = vec4( vert_color ,1.0f);
}