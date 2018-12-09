//#include "own_shader.h"
//Shader::Shader(const char* vertexPath, const char*fragmentPath) {
//
//	std::string vertexCode;
//	std::string fragmentCode;
//	std::ifstream vShaderFile;
//	std::ifstream fShaderFile;
//
//	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
//	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
//
//	try {
//		vShaderFile.open(vertexPath);
//		fShaderFile.open(fragmentPath);
//		std::stringstream vShaderStream, fShaderStream;
//		vShaderStream << vShaderFile.rdbuf();
//		fShaderStream << fShaderFile.rdbuf();
//		vShaderFile.close();
//		fShaderFile.close();
//
//		vertexCode = vShaderStream.str();
//		fragmentCode = fShaderStream.str();
//	}
//	catch (std::ifstream::failure e) {
//		std::cout << "read shader file fail";
//	}
//
//	const char* vShaderCode = vertexCode.c_str();
//	const char* fShaderCode = fragmentCode.c_str();
//
//	unsigned int vertex, fragment;
//	int success;
//	char infoLog[512];
//
//	vertex = glCreateShader(GL_VERTEX_SHADER);
//	glShaderSource(vertex, 1, &vShaderCode, NULL);
//	glCompileShader(vertex);
//	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
//	if (!success) {
//		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
//		std::cout << "fail shader source:\n" << infoLog << std::endl;
//	}
//
//	fragment = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fragment, 1, &fShaderCode, NULL);
//	glCompileShader(fragment);
//	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
//	if (!success) {
//		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
//		std::cout << "fail fragment shader source:\n" << infoLog << std::endl;
//	}
//
//	this->ID = glCreateProgram();
//	glAttachShader(this->ID, vertex);
//	glAttachShader(this->ID, fragment);
//	glLinkProgram(this->ID);
//
//	glGetProgramiv(this->ID, GL_LINK_STATUS, &success);
//	if (!success) {
//		glGetProgramInfoLog(ID, 512, NULL, infoLog);
//		std::cout << "fail link program:\n" << infoLog << std::endl;
//	}
//
//	glDeleteShader(vertex);
//	glDeleteShader(fragment);
//
//}
//
//void Shader::use() {
//	glUseProgram(this->ID);
//}
//
//void Shader::setBool(const std::string &name, bool value) const {
//	glUniform1i(glGetUniformLocation(this->ID, name.c_str()),(int)value);
//}
//
//void Shader::setInt(const std::string &name, int value) const {
//	glUniform1i(glGetUniformLocation(this->ID, name.c_str()), value);
//}
//
//void Shader::setFloat(const std::string &name, float value) const {
//	glUniform1f(glGetUniformLocation(this->ID, name.c_str()), value);
//}
//
//void Shader::setMat4(const std::string &name, const GLfloat* value) const {
//	glUniformMatrix4fv(glGetUniformLocation(this->ID, name.c_str()), 1, GL_FALSE, value);
//}
//
//void Shader::setMat4(const std::string &name, const glm::mat4 & mat) const {
//	glUniformMatrix4fv(glGetUniformLocation(this->ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
//}
//
//void Shader::setMat3(const std::string &name, const GLfloat* value) const {
//	glUniformMatrix3fv(glGetUniformLocation(this->ID, name.c_str()), 1, GL_FALSE, value);
//}
//
//void Shader::setVec3(const std::string &name, const GLfloat x, const GLfloat y, const GLfloat z) const {
//	glUniform3f(glGetUniformLocation(this->ID, name.c_str()), x, y, z);
//}
//
//void Shader::setVec3(const std::string &name, const glm::vec3 & vec) const {
//	//glUniform3fv(glGetUniformLocation(this->ID, name.c_str()), 1, glm::value_ptr(vec));
//	glUniform3f(glGetUniformLocation(this->ID, name.c_str()), vec.x, vec.y, vec.z);
//}
