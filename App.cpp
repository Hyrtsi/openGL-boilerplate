#include "stdafx.h"
#include "App.hpp"

#include <GL/glew.h>

App::App(const sf::VideoMode & vm, const std::string & name) :
	_window		(vm, name),
	_glewError	(glewInit()),
	_shader		("vs_simple.glsl", "fs_simple.glsl"),
	_material	(_shader),
	_vertexData	("quad.obj"),
	_mesh		(_vertexData, _material)
{
	_window.setFramerateLimit(60);

	// Activate the window for OpenGL rendering
	_window.setActive();

	//glewExperimental = true; // Needed in core profile
	if (_glewError != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return;
	}
}

void App::loop(void)
{
	float time = 0.0f;
	while (_window.isOpen())
	{
		time += 0.1f;
		_material.setTime(time);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		_mesh.draw();

		// OpenGL drawing commands go here...
		// End the current frame and display its contents on screen
		_window.display();


		// Event processing
		sf::Event event;
		while (_window.pollEvent(event))
		{
			// Request for closing the window
			if (event.type == sf::Event::Closed)
				_window.close();
		}
	}
}
