#include "stdafx.h"
#include "Mesh.hpp"


Mesh::Mesh(const VertexData& vertexData, const Material& material) :
	_material(&material)
{
	auto positions = vertexData.getPositions();
	auto texCoords = vertexData.getTextureCoordinates();
	auto normals = vertexData.getNormals();
	auto indices = vertexData.getIndices();

	//  create and bind the VAO
	glGenVertexArrays(1, &_vertexArrayObjectId);
	glBindVertexArray(_vertexArrayObjectId);

	//  upload the vertex data to GPU and set up the vertex attribute arrays
	glGenBuffers(1, &_positionBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, _positionBufferId);
	glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(std::array<float, 4>), &positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

	glGenBuffers(1, &_texCoordBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, _texCoordBufferId);
	glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(std::array<float, 3>), &texCoords[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

	glGenBuffers(1, &_normalBufferId);
	glBindBuffer(GL_ARRAY_BUFFER, _normalBufferId);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(std::array<float, 3>), &normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

	_nIndices = indices.size();
	glGenBuffers(1, &_elementBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBufferId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _nIndices * sizeof(unsigned), &indices[0], GL_STATIC_DRAW);

	//  unbind the VAO so it won't be changed outside this function
	glBindVertexArray(0);
}

void Mesh::draw(/*const Matrix4Glf& model, const Matrix4Glf& camera, const Matrix4Glf& proj*/)
{
	_material->use(/*model, camera, proj*/);
	glBindVertexArray(_vertexArrayObjectId);

	glDrawElements(GL_TRIANGLES, _nIndices, GL_UNSIGNED_INT, (GLvoid*)0);

	glBindVertexArray(0);
}
