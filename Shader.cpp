#include "stdafx.h"
#include "Shader.hpp"

#include <cstdio>


Shader::Shader(	const std::string& vsFileName,
				const std::string& fsFileName)
{
	_vsObjectId = glCreateShader(GL_VERTEX_SHADER);
	_fsObjectId = glCreateShader(GL_FRAGMENT_SHADER);

	GLint compileStatus, infoLogLength;

	//	load and compile vertex shader
	loadFile(vsFileName);
	glShaderSource(_vsObjectId, 1, &_buffer, NULL);
	glCompileShader(_vsObjectId);

	glGetShaderiv(_vsObjectId, GL_COMPILE_STATUS, &compileStatus);

	if (compileStatus == GL_FALSE) {
		glGetShaderiv(_vsObjectId, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* infoLog = new char[infoLogLength];
		glGetShaderInfoLog(_vsObjectId, infoLogLength, &infoLogLength, infoLog);
		glDeleteShader(_vsObjectId);
		throw infoLog;
	}

	//	load and compile fragment shader
	loadFile(fsFileName);
	glShaderSource(_fsObjectId, 1, &_buffer, NULL);
	glCompileShader(_fsObjectId);

	glGetShaderiv(_fsObjectId, GL_COMPILE_STATUS, &compileStatus);

	if (compileStatus == GL_FALSE) {
		glGetShaderiv(_fsObjectId, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* infoLog = new char[infoLogLength];
		glGetShaderInfoLog(_fsObjectId, infoLogLength, &infoLogLength, infoLog);
		glDeleteShader(_fsObjectId);
		throw infoLog;
	}

	//	link it
	_programId = glCreateProgram();
	glAttachShader(_programId, _vsObjectId);
	glAttachShader(_programId, _fsObjectId);
	glLinkProgram(_programId);
	GLint linkStatus;
	glGetProgramiv(_programId, GL_LINK_STATUS, &linkStatus);

	if (linkStatus == GL_FALSE) {
		glGetShaderiv(_programId, GL_INFO_LOG_LENGTH, &infoLogLength);
		char *infoLog = new char[infoLogLength];
		glGetProgramInfoLog(_programId, infoLogLength, NULL, infoLog);
		throw infoLog;
	}
}

Shader::~Shader(void)
{
	if (_vsObjectId != 0)
		glDeleteShader(_vsObjectId);
	if (_fsObjectId != 0)
		glDeleteShader(_fsObjectId);
}

void Shader::loadFile(const std::string& fileName)
{
	FILE *fp = fopen(fileName.c_str(), "rb");
	if (!fp) {
		throw "Text: open failed";
	}
	if (fseek(fp, 0, SEEK_END) < 0) {
		fclose(fp);
		throw "Text: fseek failed";
	}
	_bufferSize = ftell(fp);
	if (fseek(fp, 0, SEEK_SET) < 0) {
		fclose(fp);
		throw "Text: fseek failed";
	}
	_buffer = new char[_bufferSize + 1];
	if (fread(_buffer, 1, _bufferSize, fp) < _bufferSize) {
		fclose(fp);
		throw "Text: read failed";
	}
	_buffer[_bufferSize] = '\0';
}