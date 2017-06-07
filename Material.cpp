#include "stdafx.h"
#include "Material.hpp"

Material::Material(const Shader& shader) :
	_shader(&shader)
{
}

void Material::use() const
{
	glUseProgram(_shader->_programId);
}

void Material::setTime(float time) const
{
	glUniform1f(glGetUniformLocation(_shader->_programId, "time"), time);
}
