#ifndef VERTEX_DATA_HPP
#define VERTEX_DATA_HPP


#include <vector>
#include <map>
#include <array>


class VertexData {
public:
	VertexData(void);
	VertexData(const std::string& fileName);

	bool usesTextureCoordinates(void) const;
	bool usesNormals(void) const;
	bool usesIndexing(void) const;

	const std::vector<std::array<float, 4>>& getPositions(void) const;
	const std::vector<std::array<float, 3>>& getTextureCoordinates(void) const;
	const std::vector<std::array<float, 3>>& getNormals(void) const;
	const std::vector<unsigned>& getIndices(void) const;

private:
	bool usingTexCoords_;
	bool usingNormals_;
	bool usingIndexing_;

	std::vector<std::array<float, 4>> positions_;
	std::vector<std::array<float, 3>> texCoords_;
	std::vector<std::array<float, 3>> normals_;
	std::vector<unsigned> indices_;


	char* _buffer;
	size_t _bufferSize;

	void loadFile(const std::string& fileName);
};



#endif // VERTEX_DATA_HPP
