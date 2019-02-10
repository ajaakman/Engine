#pragma once
#include <string>
#include <GL/glew.h>
class GLSL
{
public:
	GLSL();
	~GLSL();

	void CompileShaders(const std::string& vertexShaderFilepath, const std::string& fragmentShaderFilepath);
	void LinkShaders();
	void AddAttribute(const std::string& attributeName);

	GLuint getUniformLocation(const std::string& uniformName);

	void Bind();
	void UnBind();


private:

	int m_nNumAttributes;

	void CompileShader(const std::string& filepath, GLuint id);

	GLuint m_ProgramID;
	GLuint m_VertexShaderID;
	GLuint m_FragmentShaderID;
};

