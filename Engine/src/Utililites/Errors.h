#pragma once
#include <string>

#ifdef DEBUG
#define DBG(x) x
#define ASSERT(x) if (!(x)) __debugbreak();
#define GL(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#else 
	#define GL(x) x
	#define ASSERT(x) x
	#define DBG(x)
#endif

extern void FatalError(std::string errorString);
extern void GLClearError();
extern bool GLLogCall(const char* function, const char* file, int line);
