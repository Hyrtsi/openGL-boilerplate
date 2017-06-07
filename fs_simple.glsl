#version 330

// Transformation
uniform mat4 uNormalToCam;

// Textures
uniform sampler2D diffuseSampler;

// Time
uniform float time;

// Interpolated inputs
in vec3 posVar;
in vec3 normVar;
in vec2 texVar;


out vec4 fragColor;


void main()
{
	float x0 = posVar.x*cos(time*0.1) + posVar.y*sin(time*0.1);
	float y0 = -posVar.x*sin(time*0.1) + posVar.y*cos(time*0.1);

	x0 /= time*0.1;
	y0 /= time*0.1;

	float x = 0.0;
	float y = 0.0;

	int it = 0;
	int maxit = 100;

	while (x*x + y*y < 4 && it < maxit) {
		float xtemp = x*x - y*y + x0;
		y = 2*x*y + y0;
		x = xtemp;
		++it;
	}

    fragColor = vec4(it*0.01, pow(it*0.01, 4), pow(it*0.01, 8), 1);
}