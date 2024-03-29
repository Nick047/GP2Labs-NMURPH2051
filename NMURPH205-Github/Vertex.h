#ifndef Vertex_h
#define Vertex_h

#include <glm/glm.hpp>
using glm::vec4;
using glm::vec3;
using glm::vec2;

struct Vertex
{
	vec3 position;	//3dimensional coordinates
	vec2 texCoords;	//The u,v coordinates of thetexture
	vec4 colours;	//Colors & alpha
}

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

#endif