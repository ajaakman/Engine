#pragma once

#include <GL/glew.h>

struct Vertex {
	struct position {
		float x;
		float y;
	} position;
	struct color {
		GLubyte r;
		GLubyte g;
		GLubyte b;
		GLubyte a;
	} color;	
};