#pragma once
#ifndef  SHADER_H
#define SHADER_H

#include<glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>


class Shader {

public:
	unsigned int ID;
	Shader(const GLchar* vertexPath, const GLchar *fragmentPath);
	void use();

	void setBool(const std::string & name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setMat4(const std::string &name, const GLfloat* mat_ptr) const;
	void setMat4(const std::string &name, const glm::mat4 &mat) const;
	void setMat3(const std::string &name, const GLfloat* mat_ptr) const;
	void setVec3(const std::string &name, const GLfloat, const GLfloat, const GLfloat) const;
	void setVec3(const std::string &name, const glm::vec3 & vec) const;
};
#endif // ! SHADER_H
