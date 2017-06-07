#ifndef SHADER_HPP
#define SHADER_HPP


#include <string>
#include <GL/glew.h>


class Shader {
public:
	friend class Material;

	Shader(	const std::string& vsFileName,
			const std::string& fsFileName);

	~Shader(void);

private:
	char* _buffer;
	size_t _bufferSize;

	GLuint _vsObjectId;
	GLuint _fsObjectId;
	GLuint _programId;

	void loadFile(const std::string& fileName);
};


#endif	//	SHADER_HPP