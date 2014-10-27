#version 150

in vec3 vertexPostion;

uniform mat4 MVP;

void main()
{

	gl_Position = MVP * vec4(vetexPosition, 1.0);

}