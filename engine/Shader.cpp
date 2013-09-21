#include <iostream>
#include <string>
#include <fstream>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <stdexcept>
#include <boost/container/vector.hpp>
#include <boost/lexical_cast.hpp>

#include "Shader.hpp"


using std::ifstream;
using std::ios;
using std::invalid_argument;
using std::logic_error;
using boost::container::vector;
using boost::lexical_cast;


GLuint Shader::generateShaders(string vertexShader, string fragmentShader) {
	GLuint vertexShaderID   = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	try {
		compileShader(vertexShaderID, vertexShader);
	}
	catch (logic_error &err) {
		//std::cout <<  vertexShader << std::endl;
		throw logic_error(
			"Vertex Shader compilation error:" +
			string(err.what())
		);
	}

	try {
		compileShader(fragmentShaderID, fragmentShader);
	}
	catch (logic_error &err) {
		//std::cout <<  vertexShader << std::endl;
		throw logic_error(
			"FragmentShader compilation error:" +
			string(err.what())
		);
	}


	GLuint programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	try {
		checkProgram(programID);
	}
	catch (logic_error &err) {
		throw logic_error(
				"Shader Program error:" + string(err.what())
		);
	}

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	return programID;
}


GLuint Shader::loadShaders(string vertexShaderFile, string fragmentShaderFile) {
	string vertexShader   = loadShaderFile(vertexShaderFile);
	string fragmentShader = loadShaderFile(fragmentShaderFile);

	return generateShaders(vertexShader, fragmentShader);
}

/**
 * Compile a shader
 */
void Shader::compileShader(GLuint shaderID, string shaderCode)  {
	char const *sourcePointer = shaderCode.c_str();

	glShaderSource(shaderID, 1, &sourcePointer, NULL);
	glCompileShader(shaderID);
	checkShader(shaderID);
}

/**
 * Check the shader compilation for errors
 */
void Shader::checkShader(GLuint shaderID) throw (logic_error) {
	GLint result = GL_FALSE;
	GLint logLength;

	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLength);

	if (result != GL_TRUE) {
		vector<char> errorMsg(logLength + 1);
		glGetShaderInfoLog(shaderID, logLength, NULL, &errorMsg[0]);
		std::cout << "error: " <<  errorMsg[0] << std::endl;
		throw logic_error(
				"Compile status: " + lexical_cast<string>(result) 
				+ ", msg: " + &errorMsg[0]
		);
	}
}

/**
 * check the program
 */
void Shader::checkProgram(GLuint programID) throw (logic_error)  {
	GLint result = GL_FALSE;
	GLint logLength = 1000;

	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &logLength);
	if (result != GL_TRUE) {
		vector<char> errorMsg(logLength + 1);
		glGetProgramInfoLog(programID, logLength, NULL, &errorMsg[0]);
		throw logic_error(&errorMsg[0]);
	}
}

/**
 * Open a file and read the content
 */
string Shader::loadShaderFile(string file) {
	string shaderCode;

	ifstream codeStream(file, ios::in);
	if (codeStream.is_open()) {
		string line = "";

		while (getline(codeStream, line)) {
			shaderCode += "\n" + line;
		}

		codeStream.close();
	}
	else {
		throw invalid_argument("Shader file " + file);
	}

	return shaderCode;
}
