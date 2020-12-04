#pragma once

#include <string>
#include <vector>
#include <GL/glew.h>

class Texture {
public:
	Texture(const std::string& filename = "data/textures/test_texture.png");
	Texture(const std::vector<std::string>& filenames);
	virtual ~Texture();

	void bind(unsigned int unit);

private:
	GLuint p_texture;
};
