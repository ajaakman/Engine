#include <fstream>

#include "GLSL.h"
#include "Utililites/Errors.h"


Engine::GLSL::GLSL()
:m_nNumAttributes(0), m_ProgramID(0), m_VertexShaderID(0), m_FragmentShaderID(0)
{
}

Engine::GLSL::~GLSL()
{
}

void Engine::GLSL::CompileShaders(const std::string & vertexShaderFilepath, const std::string & fragmentShaderFilepath)
{
	GL(m_ProgramID = glCreateProgram());

	GL(m_VertexShaderID = glCreateShader(GL_VERTEX_SHADER));
	if (!m_VertexShaderID)
		FatalError("Vertex shader failed to be created!");

	GL(m_FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER));
	if (!m_FragmentShaderID)
		FatalError("Fragment shader failed to be created!");

	CompileShader(vertexShaderFilepath, m_VertexShaderID);
	CompileShader(fragmentShaderFilepath, m_FragmentShaderID);

}

void Engine::GLSL::LinkShaders()
{
	GL(glAttachShader(m_ProgramID, m_VertexShaderID));
	GL(glAttachShader(m_ProgramID, m_FragmentShaderID));

	GL(glLinkProgram(m_ProgramID));

	GLint isLinked = 0;

	GL(glGetProgramiv(m_ProgramID, GL_LINK_STATUS, (int*)&isLinked));

	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		GL(glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &maxLength));
		char* errorLog = (char*)alloca(maxLength * sizeof(char));
		GL(glGetProgramInfoLog(m_ProgramID, maxLength, &maxLength, &errorLog[0]));

		GL(glDeleteProgram(m_ProgramID));
		GL(glDeleteShader(m_VertexShaderID));
		GL(glDeleteShader(m_FragmentShaderID));

		std::printf("%s\n", &errorLog[0]);
		FatalError("Shaders failed to link!");

		return;
	}

	GL(glDetachShader(m_ProgramID, m_VertexShaderID));
	GL(glDetachShader(m_ProgramID, m_FragmentShaderID));
	GL(glDeleteShader(m_VertexShaderID));
	GL(glDeleteShader(m_FragmentShaderID));

}

void Engine::GLSL::AddAttribute(const std::string & attributeName)
{
	GL(glBindAttribLocation(m_ProgramID, m_nNumAttributes++, attributeName.c_str()));
}

GLuint Engine::GLSL::getUniformLocation(const std::string& uniformName)
{
	GL(GLint location = glGetUniformLocation(m_ProgramID, uniformName.c_str()));
	ASSERT(location != -1);
	if (location == GL_INVALID_INDEX)	
		FatalError("Uniform " + uniformName + " not found in shader");
	
	return location;
}

void Engine::GLSL::Bind()
{
	GL(glUseProgram(m_ProgramID));
	GL(for (int i = 0; i < m_nNumAttributes; ++i)
		glEnableVertexAttribArray(i));
}

void Engine::GLSL::UnBind()
{
	GL(glUseProgram(0));
	GL(for (int i = 0; i < m_nNumAttributes; ++i)
		glDisableVertexAttribArray(i));
}

void Engine::GLSL::CompileShader(const std::string & filepath, GLuint id)
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
	GL(glShaderSource(id, 1, &contentsPtr, nullptr));

	GL(glCompileShader(id));

	GLint result = 0;
	GL(glGetShaderiv(id, GL_COMPILE_STATUS, &result));

	if (result == GL_FALSE)
	{
		GLint maxLength = 0;
		GL(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength));

		char* errorLog = (char*)alloca(maxLength * sizeof(char));
		GL(glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]));

		GL(glDeleteShader(id));

		std::printf("%s\n", &errorLog[0]);
		FatalError("Shader " + filepath + " failed to compile!");

		return;
	}

}
