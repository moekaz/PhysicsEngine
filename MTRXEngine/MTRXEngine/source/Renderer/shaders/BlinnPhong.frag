#version 430 core

in vec3 WorldFragPos;
in vec3 WorldNormal;

out vec4 FragColour;

uniform vec3 viewPos;

void main()
{
	FragColour = vec4(WorldNormal, 1.0);
}
