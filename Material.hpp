#ifndef MATERIAL_HPP
#define MATERIAL_HPP


#include "Shader.hpp"


class Material {
public:
	friend class Mesh;

	Material(const Shader& shader);

	void use(/*const Matrix4Glf& model, const Matrix4Glf& camera, const Matrix4Glf& proj*/) const;

	void setTime(float time) const;

private:
	const Shader*	_shader;
};


#endif	//	MATERIAL_HPP