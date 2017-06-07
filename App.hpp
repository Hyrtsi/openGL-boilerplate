#ifndef APP_HPP
#define APP_HPP

#include <SFML/Graphics.hpp>
#include <string>

#include "Mesh.hpp"
	

class App {
	public:
		App(const sf::VideoMode& vm, const std::string& name);
		void loop(void);
	private:
		sf::Window _window;

		//opengl stuff
		GLenum	_glewError;

		Shader		_shader;
		Material	_material;
		VertexData	_vertexData;
		Mesh		_mesh;
};




#endif // !APP_HPP
