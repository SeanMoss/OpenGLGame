#include "ShaderProgram.h"
#include <iostream>

static ShaderProgram* activeProgram;

ShaderProgram::ShaderProgram(const char* vertPath, const char* fragPath)
{
	programID = LoadShaders(vertPath, fragPath);
	if(programID < 1)
	{
		fprintf(stderr, "Failed to load shaders %s and %s. Shutting down.", vertPath, fragPath);
		exit(1);
	}

	//Find all uniforms in code
	int total = -1;
	glGetProgramiv(programID, GL_ACTIVE_UNIFORMS, &total);
	fprintf(stdout, "Found %i uniforms in shader program %i.\n", total, programID);
	for(int i = 0; i < total; i++)
	{
		int nameLength = -1, num = -1;
		GLenum type = GL_ZERO;
		char name[100];
		glGetActiveUniform(programID, (GLuint)i, sizeof(name) - 1, &nameLength, &num, &type, name);
		name[nameLength] = 0;
		std::string nameCopy(&name[0]);
		uniformMap[nameCopy] = (unsigned int)glGetUniformLocation(programID, name);
		std::cout << "Got a uniform, name: " << nameCopy << " location: " << uniformMap[nameCopy] << std::endl;
	}
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(GetProgramID());
}

GLuint ShaderProgram::GetProgramID()
{
	return programID;
}

bool ShaderProgram::hasUniform(std::string key)
{
	return (uniformMap.find(key) != uniformMap.end());
}

//TODO implement methods
void ShaderProgram::Uniform1f(string key, GLfloat value)
{
	if(!hasUniform(key) || !active)
		return;

	glUniform1f(uniformMap[key], value);
}

//void ShaderProgram::Uniform1d(string key, GLdouble value)
//{
//	if(!hasUniform(key) || !active)
//		return;
//
//	glUniform1d(uniformMap[key], value);
//}

void ShaderProgram::Uniform1i(string key, GLint value)
{
	if(!hasUniform(key) || !active)
		return;

	glUniform1i(uniformMap[key], value);
}

void ShaderProgram::Uniform1ui(string key, GLuint value)
{
	if(!hasUniform(key) || !active)
		return;

	glUniform1ui(uniformMap[key], value);
}

void ShaderProgram::Uniform1fv(string key, GLsizei size, GLfloat* value)
{
	if(!hasUniform(key) || !active)
		return;

	glUniform1fv(uniformMap[key], size, value);
}

//void ShaderProgram::Uniform1dv(string key, GLsizei size, GLdouble* value)
//{
//	if(!hasUniform(key) || !active)
//		return;
//
//	glUniform1dv(uniformMap[key], size, value);
//}

void ShaderProgram::Uniform1iv(string key, GLsizei size, GLint* value)
{
	if(!hasUniform(key) || !active)
		return;

	glUniform1iv(uniformMap[key], size, value);
}

void ShaderProgram::Uniform1uiv(string key, GLsizei size, GLuint* value)
{
	if(!hasUniform(key) || !active)
		return;

	glUniform1uiv(uniformMap[key], size, value);
}

void ShaderProgram::Uniform2f(string key, GLfloat value1, GLfloat value2)
{
	if(!hasUniform(key) || !active)
		return;

	glUniform2f(uniformMap[key], value1, value2);
}

//void ShaderProgram::Uniform2d(string key, GLdouble value1, GLdouble value2)
//{
//	if(!hasUniform(key) || !active)
//		return;
//
//	glUniform2d(uniformMap[key], value1, value2);
//}

void ShaderProgram::Uniform2i(string key, GLint value1, GLint value2)
{
	if(!hasUniform(key) || !active)
		return;

	glUniform2i(uniformMap[key], value1, value2);
}

void ShaderProgram::Uniform2ui(string key, GLuint value1, GLuint value2)
{
	if(!hasUniform(key) || !active)
		return;

	glUniform2ui(uniformMap[key], value1, value2);
}

void ShaderProgram::Uniform2fv(string key, GLsizei size, GLfloat* value)
{
	if(!hasUniform(key) || !active)
		return;

	glUniform2fv(uniformMap[key], size, value);
}

//void ShaderProgram::Uniform2dv(string key, GLsizei size, GLdouble* value)
//{
//	if(!hasUniform(key) || !active)
//		return;
//
//	glUniform2dv(uniformMap[key], size, value);
//}

void ShaderProgram::Uniform2iv(string key, GLsizei size, GLint* value)
{
	if(!hasUniform(key) || !active)
		return;

	glUniform2iv(uniformMap[key], size, value);
}

void ShaderProgram::Uniform2uiv(string key, GLsizei size, GLuint* value)
{
	if(!hasUniform(key) || !active)
		return;

	glUniform2uiv(uniformMap[key], size, value);
}

void ShaderProgram::Uniform3f(string key, GLfloat value1, GLfloat value2, GLfloat value3)
{
	if(!hasUniform(key) || !active)
		return;

	glUniform3f(uniformMap[key], value1, value2, value3);
}

//void ShaderProgram::Uniform3d(string key, GLdouble value1, GLdouble value2, GLdouble value3)
//{
//	if(!hasUniform(key) || !active)
//		return;
//
//	glUniform3d(uniformMap[key], value1, value2, value3);
//}

void ShaderProgram::Uniform3i(string key, GLint value1, GLint value2, GLint value3)
{
	if(!hasUniform(key) || !active)
		return;

	glUniform3i(uniformMap[key], value1, value2, value3);
}

void ShaderProgram::Uniform3ui(string key, GLuint value1, GLuint value2, GLuint value3)
{
	if(!hasUniform(key) || !active)
		return;

	glUniform3ui(uniformMap[key], value1, value2, value3);
}

void ShaderProgram::Uniform3fv(string key, GLsizei size, GLfloat* value)
{
	if(!hasUniform(key) || !active)
		return;

	glUniform3fv(uniformMap[key], size, value);
}

//void ShaderProgram::Uniform3dv(string key, GLsizei size, GLdouble* value)
//{
//	if(!hasUniform(key) || !active)
//		return;
//
//	glUniform3dv(uniformMap[key], size, value);
//}

void ShaderProgram::Uniform3iv(string key, GLsizei size, GLint* value)
{
	if(!hasUniform(key) || !active)
		return;

	glUniform3iv(uniformMap[key], size, value);
}

void ShaderProgram::Uniform3uiv(string key, GLsizei size, GLuint* value)
{
	if(!hasUniform(key) || !active)
		return;

	glUniform3uiv(uniformMap[key], size, value);
}

void ShaderProgram::Uniform4f(string key, GLfloat value1, GLfloat value2, GLfloat value3, GLfloat value4)
{
	if(!hasUniform(key) || !active)
		return;

	glUniform4f(uniformMap[key], value1, value2, value3, value4);
}

//void ShaderProgram::Uniform4d(string key, GLdouble value1, GLdouble value2, GLdouble value3, GLdouble value4)
//{
//	if(!hasUniform(key) || !active)
//		return;
//
//	glUniform4d(uniformMap[key], value1, value2, value3, value4);
//}

void ShaderProgram::Uniform4i(string key, GLint value1, GLint value2, GLint value3, GLint value4)
{
	if(!hasUniform(key) || !active)
		return;

	glUniform4i(uniformMap[key], value1, value2, value3, value4);
}

void ShaderProgram::Uniform4ui(string key, GLuint value1, GLuint value2, GLuint value3, GLuint value4)
{
	if(!hasUniform(key) || !active)
		return;

	glUniform4ui(uniformMap[key], value1, value2, value3, value4);
}

void ShaderProgram::Uniform4fv(string key, GLsizei size, GLfloat* value)
{
	if(!hasUniform(key) || !active)
		return;

	glUniform4fv(uniformMap[key], size, value);
}

//void ShaderProgram::Uniform4dv(string key, GLsizei size, GLdouble* value)
//{
//	if(!hasUniform(key) || !active)
//		return;
//
//	glUniform4dv(uniformMap[key], size, value);
//}

void ShaderProgram::Uniform4iv(string key, GLsizei size, GLint* value)
{
	if(!hasUniform(key) || !active)
		return;

	glUniform4iv(uniformMap[key], size, value);
}

void ShaderProgram::Uniform4uiv(string key, GLsizei size, GLuint* value)
{
	if(!hasUniform(key) || !active)
		return;

	glUniform4uiv(uniformMap[key], size, value);
}

void ShaderProgram::UniformVec2(string key, vec2 value)
{
	if(!hasUniform(key) || !active)
		return;

	glUniform2f(uniformMap[key], value.x, value.y);
}

void ShaderProgram::UniformVec3(string key, vec3 value)
{
	if(!hasUniform(key) || !active)
		return;

	glUniform3f(uniformMap[key], value.x, value.y, value.z);
}

void ShaderProgram::UniformVec4(string key, vec4 value)
{
	if(!hasUniform(key) || !active)
		return;

	glUniform4f(uniformMap[key], value.x, value.y, value.z, value.w);
}

void ShaderProgram::UniformMat2(string key, GLsizei size, GLboolean transpose, mat2 value)
{
	if(!hasUniform(key) || !active)
		return;

	glUniformMatrix2fv(uniformMap[key], size, transpose, &value[0][0]);
}

void ShaderProgram::UniformMat3(string key, GLsizei size, GLboolean transpose, mat3 value)
{
	if(!hasUniform(key) || !active)
		return;

	glUniformMatrix3fv(uniformMap[key], size, transpose, &value[0][0]);
}

void ShaderProgram::UniformMat4(string key, GLsizei size, GLboolean transpose, mat4 value)
{
	if(!hasUniform(key) || !active)
		return;

	glUniformMatrix4fv(uniformMap[key], size, transpose, &value[0][0]);
}

void ShaderProgram::SetActive(ShaderProgram* program)
{
	if (!program)
	{
		glUseProgram(0);
		return;
	}

	if (activeProgram && activeProgram->programID != program->programID)
	{
		activeProgram->active = false;
		activeProgram = program;
		activeProgram->active = true;
		glUseProgram(activeProgram->programID); 
	}
	else if(!activeProgram)
	{
		activeProgram = program;
		activeProgram->active = true;
		glUseProgram(activeProgram->programID); 
	}
}