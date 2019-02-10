#include <fstream>

#include "GLSL.h"
#include "Errors.h"


GLSL::GLSL()
:m_nNumAttributes(0), m_ProgramID(0), m_VertexShaderID(0), m_FragmentShaderID(0)
{
}

GLSL::~GLSL()
{
}

void GLSL::CompileShaders(const std::string & vertexShaderFilepath, const std::string & fragmentShaderFilepath)
{
	m_ProgramID = glCreateProgram();

	m_VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (!m_VertexShaderID)
		FatalError("Vertex shader failed to be created!");

	m_FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (!m_FragmentShaderID)
		FatalError("Fragment shader failed to be created!");

	CompileShader(vertexShaderFilepath, m_VertexShaderID);
	CompileShader(fragmentShaderFilepath, m_FragmentShaderID);

}

void GLSL::LinkShaders()
{
	glAttachShader(m_ProgramID, m_VertexShaderID);
	glAttachShader(m_ProgramID, m_FragmentShaderID);

	glLinkProgram(m_ProgramID);

	GLint isLinked = 0;

	glGetProgramiv(m_ProgramID, GL_LINK_STATUS, (int*)&isLinked);

	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &maxLength);
		char* errorLog = (char*)alloca(maxLength * sizeof(char));
		glGetProgramInfoLog(m_ProgramID, maxLength, &maxLength, &errorLog[0]);

		glDeleteProgram(m_ProgramID);
		glDeleteShader(m_VertexShaderID);
		glDeleteShader(m_FragmentShaderID);

		std::printf("%s\n", &errorLog[0]);
		FatalError("Shaders failed to link!");

		return;
	}

	glDetachShader(m_ProgramID, m_VertexShaderID);
	glDetachShader(m_ProgramID, m_FragmentShaderID);
	glDeleteShader(m_VertexShaderID);
	glDeleteShader(m_FragmentShaderID);

}

void GLSL::AddAttribute(const std::string & attributeName)
{
	glBindAttribLocation(m_ProgramID, m_nNumAttributes++, attributeName.c_str());
}

GLuint GLSL::getUniformLocation(const std::string& uniformName)
{
	GLuint location = glGetUniformLocation(m_ProgramID, uniformName.c_str());
	if (location == GL_INVALID_INDEX)	
		FatalError("Uniform " + uniformName + " not found in shader");
	
	return location;
}

void GLSL::Bind()
{
	glUseProgram(m_ProgramID);
	for (int i = 0; i < m_nNumAttributes; ++i)
		glEnableVertexAttribArray(i);
}

void GLSL::UnBind()
{
	glUseProgram(0);
	for (int i = 0; i < m_nNumAttributes; ++i)
		glDisableVertexAttribArray(i);
}

void GLSL::CompileShader(const std::string & filepath, GLuint id)
{
	std::ifstream vertexFile(filepath);
	if (vertexFile.fail())
	{
		perror(filepath.c_str());
		FatalError("Failed to open " + filepath);
	}

	std::string fileContents = "";
	std::string line;

	while (std::getline(vertexFile, line))
		fileContents += line + "\n";

	vertexFile.close();

	const char* contentsPtr = fileContents.c_str();
	glShaderSource(id, 1, &contentsPtr, nullptr);

	glCompileShader(id);

	GLint result = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		char* errorLog = (char*)alloca(maxLength * sizeof(char));
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

		glDeleteShader(id);

		std::printf("%s\n", &errorLog[0]);
		FatalError("Shader " + filepath + " failed to compile!");

		return;
	}

}
