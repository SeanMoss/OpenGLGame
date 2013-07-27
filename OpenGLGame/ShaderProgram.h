#ifndef _SHADER_PROGRAM_H_
#define _SHADER_PROGRAM_H_

#include "ShaderLoader.h"
#include <map>
#include <string>
#include <glm\glm.hpp>
using namespace std;
using namespace glm;

class ShaderProgram
{
public:
	static void SetActive(ShaderProgram* program);

private:
	GLuint programID; //ID of the shader program this represents
	std::map<std::string, unsigned int> uniformMap; //Map of the uniform handles and their names
	bool active; //If this is the current active shader program

private:
	bool hasUniform(std::string key);

public:
	ShaderProgram(const char* vertPath, const char* fragPath);
	~ShaderProgram();

	GLuint GetProgramID();

	void Uniform1f(string key, GLfloat value);
	//void Uniform1d(string key, GLdouble value);
	void Uniform1i(string key, GLint value);
	void Uniform1ui(string key, GLuint value);
	void Uniform1fv(string key, GLsizei size, GLfloat* value);
	//void Uniform1dv(string ket, GLsizei size, GLdouble* value);
	void Uniform1iv(string key, GLsizei size, GLint* value);
	void Uniform1uiv(string key, GLsizei size, GLuint* value);
	void Uniform2f(string key, GLfloat value1, GLfloat value2);
	//void Uniform2d(string key, GLdouble value1, GLdouble value2);
	void Uniform2i(string key, GLint value1, GLint value2);
	void Uniform2ui(string key, GLuint value1, GLuint value2);
	void Uniform2fv(string key, GLsizei size, GLfloat* value);
	//void Uniform2dv(string key, GLsizei size, GLdouble* value);
	void Uniform2iv(string key, GLsizei size, GLint* value);
	void Uniform2uiv(string key, GLsizei size, GLuint* value);
	void Uniform3f(string key, GLfloat value1, GLfloat value2, GLfloat value3);
	//void Uniform3d(string key, GLdouble value1, GLdouble value2, GLdouble value3);
	void Uniform3i(string key, GLint value1, GLint value2, GLint value3);
	void Uniform3ui(string key, GLuint value1, GLuint value2, GLuint value3);
	void Uniform3fv(string key, GLsizei size, GLfloat* value);
	//void Uniform3dv(string key, GLsizei size, GLdouble* value);
	void Uniform3iv(string key, GLsizei size, GLint* value);
	void Uniform3uiv(string key, GLsizei size, GLuint* value);
	void Uniform4f(string key, GLfloat value1, GLfloat value2, GLfloat value3, GLfloat value4);
	//void Uniform4d(string key, GLdouble value1, GLdouble value2, GLdouble value3, GLdouble value4);
	void Uniform4i(string key, GLint value1, GLint value2, GLint value3, GLint value4);
	void Uniform4ui(string key, GLuint value1, GLuint value2, GLuint value3, GLuint value4);
	void Uniform4fv(string key, GLsizei size, GLfloat* value);
	//void Uniform4dv(string key, GLsizei size, GLdouble* value);
	void Uniform4iv(string key, GLsizei size, GLint* value);
	void Uniform4uiv(string key, GLsizei size, GLuint* value);
	void UniformVec2(string key, vec2 value);
	void UniformVec3(string key, vec3 value);
	void UniformVec4(string key, vec4 value);
	void UniformMat2(string key, GLsizei size, GLboolean transpose, mat2 value);
	void UniformMat3(string key, GLsizei size, GLboolean transpose, mat3 value);
	void UniformMat4(string key, GLsizei size, GLboolean transpose, mat4 value);

	//TODO add a way to get uniform attributes
};

#endif