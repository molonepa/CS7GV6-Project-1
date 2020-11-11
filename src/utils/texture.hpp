#pragma once

#include <string>
#include <GL/glew.h>

class Texture {
public:
	Texture(const std::string& filename = "data/textures/test_texture.png");
	virtual ~Texture();

	void bind(unsigned int unit);

private:
	GLuint p_texture;
};
