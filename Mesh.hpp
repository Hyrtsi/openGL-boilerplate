#ifndef MESH_HPP
#define MESH_HPP


#include "Material.hpp"
#include "VertexData.hpp"


class Mesh {
public:
	Mesh(const VertexData& vertexData, const Material& material);

	void draw(/*const Matrix4Glf& model, const Matrix4Glf& camera, const Matrix4Glf& proj*/);

private:
	const Material*	_material;

	GLuint _vertexArrayObjectId;

	unsigned _nIndices;

	GLuint _positionBufferId;
	GLuint _texCoordBufferId;
	GLuint _normalBufferId;
	GLuint _elementBufferId;
};


#endif	//	MESH_HPP