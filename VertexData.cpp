#include "stdafx.h"
#include "VertexData.hpp"




VertexData::VertexData(void) :
	usingTexCoords_(false),
	usingNormals_(false),
	usingIndexing_(false)
{}

VertexData::VertexData(const std::string& fileName) :
	VertexData()
{
	positions_.clear();
	texCoords_.clear();
	normals_.clear();
	indices_.clear();

	char lineHeader[32];
	std::vector<std::array<float, 4>> positions;
	std::vector<std::array<float, 3>> texCoords;
	std::vector<std::array<float, 3>> normals;
	std::vector<std::array<unsigned, 9>> indices;

	loadFile(fileName);

	while (*_buffer) {
		if (sscanf(_buffer, "%s", lineHeader) == 0)
			return;

		_buffer += strlen(lineHeader) + 1;

		if (strcmp(lineHeader, "v") == 0) {
			std::array<float, 4> position = { 0.0f, 0.0f, 0.0f, 1.0f };
			if (sscanf(_buffer, "%f %f %f %f", &position[0], &position[1], &position[2], &position[3]) < 3)
				throw "VertexData: invalid file!"; // TODO_EXCEPTION
			positions.push_back(std::move(position));
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			std::array<float, 3> texCoord = { 0.0f, 0.0f, 0.0f };
			if (sscanf(_buffer, "%f %f %f", &texCoord[0], &texCoord[1], &texCoord[2]) < 2)
				throw "VertexData: invalid file!"; // TODO_EXCEPTION
			texCoord[1] = 1 - texCoord[1];
			texCoords.push_back(std::move(texCoord));
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			std::array<float, 3> normal = { 0.0f, 0.0f, 0.0f };
			if (sscanf(_buffer, "%f %f %f", &normal[0], &normal[1], &normal[2]) < 3)
				throw "VertexData: invalid file!"; // TODO_EXCEPTION
			normals.push_back(std::move(normal));
		}
		else if (strcmp(lineHeader, "f") == 0) {
			std::array<unsigned, 9> index = { 0, 0, 0,  0, 0, 0,  0, 0, 0 };
			if (sscanf(_buffer, "%u %u %u", &index[2], &index[1], &index[0]) == 3 ||
				sscanf(_buffer, "%u//%u %u//%u %u//%u", &index[2], &index[8], &index[1], &index[7], &index[1], &index[6]) == 6 ||
				sscanf(_buffer, "%u/%u %u/%u %u/%u", &index[2], &index[5], &index[1], &index[4], &index[0], &index[3]) == 6 ||
				sscanf(_buffer, "%u/%u/%u %u/%u/%u %u/%u/%u", &index[2], &index[5], &index[8], &index[1], &index[4], &index[7], &index[0], &index[3], &index[6]) == 9)
				indices.push_back(std::move(index));
			else
				throw "VertexData: invalid file!"; // TODO_EXCEPTION
		}

		while (*_buffer++ != 10)
			if (*_buffer == 0)
				break;
	}

	std::map<std::array<unsigned, 3>, unsigned> createdVertices;

	usingTexCoords_ = texCoords.size() > 0;
	usingNormals_ = normals.size() > 0;
	usingIndexing_ = true;

	for (auto& indexArray : indices) {
		if (usingTexCoords_ && (indexArray[3] == 0 || indexArray[4] == 0 || indexArray[5] == 0))
			throw "VertexData: invalid index data (texture coordinates)";

		if (usingNormals_ && (indexArray[6] == 0 || indexArray[7] == 0 || indexArray[8] == 0))
			throw "VertexData: invalid index data (normals)";

		std::array<unsigned, 3> v1 = { indexArray[0], indexArray[3], indexArray[6] };
		std::array<unsigned, 3> v2 = { indexArray[1], indexArray[4], indexArray[7] };
		std::array<unsigned, 3> v3 = { indexArray[2], indexArray[5], indexArray[8] };

		if (createdVertices[v1] == 0) {
			positions_.push_back(positions.at(indexArray[0] - 1));
			if (usingTexCoords_)
				texCoords_.push_back(texCoords.at(indexArray[3] - 1));
			if (usingNormals_)
				normals_.push_back(normals.at(indexArray[6] - 1));

			createdVertices[v1] = positions_.size() - 1;
		}
		indices_.push_back(createdVertices[v1]);

		if (createdVertices[v2] == 0) {
			positions_.push_back(positions.at(indexArray[1] - 1));
			if (usingTexCoords_)
				texCoords_.push_back(texCoords.at(indexArray[4] - 1));
			if (usingNormals_)
				normals_.push_back(normals.at(indexArray[7] - 1));

			createdVertices[v2] = positions_.size() - 1;
		}
		indices_.push_back(createdVertices[v2]);

		if (createdVertices[v3] == 0) {
			positions_.push_back(positions.at(indexArray[2] - 1));
			if (usingTexCoords_)
				texCoords_.push_back(texCoords.at(indexArray[5] - 1));
			if (usingNormals_)
				normals_.push_back(normals.at(indexArray[8] - 1));

			createdVertices[v3] = positions_.size() - 1;
		}
		indices_.push_back(createdVertices[v3]);
	}
}

bool VertexData::usesTextureCoordinates(void) const {
	return usingTexCoords_;
}

bool VertexData::usesNormals(void) const {
	return usingNormals_;
}

bool VertexData::usesIndexing(void) const {
	return usingIndexing_;
}

const std::vector<std::array<float, 4>>& VertexData::getPositions(void) const {
	return positions_;
}

const std::vector<std::array<float, 3>>& VertexData::getTextureCoordinates(void) const {
	return texCoords_;
}

const std::vector<std::array<float, 3>>& VertexData::getNormals(void) const {
	return normals_;
}

const std::vector<unsigned>& VertexData::getIndices(void) const {
	return indices_;
}

void VertexData::loadFile(const std::string& fileName)
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