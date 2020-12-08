#pragma once

#include <string>
#include <vector>
#include <GL/glew.h>
#include <cassert>
#include <iostream>

class Texture {
public:
	Texture(const std::string& filename = "assets/textures/test_texture.png");
	Texture(const std::vector<std::string>& filenames);
	virtual ~Texture();

	void bind(unsigned int unit);

private:
	GLuint p_texture;
};
