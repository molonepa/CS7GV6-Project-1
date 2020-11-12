#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "texture.hpp"

#include <cassert>
#include <iostream>

Texture::Texture(const std::string& filename) {
	stbi_set_flip_vertically_on_load(true);
	// load image data from file
	int width, height, channels;
	unsigned char* imageData = stbi_load(filename.c_str(), &width, &height, &channels, 4);

	if (imageData == NULL) {
		throw std::runtime_error("ERROR: Failed to load texture " + filename);
	}

	// load image data into OpenGL texture
	glGenTextures(1, &p_texture);
	glBindTexture(GL_TEXTURE_2D, p_texture);

	// wrap textures
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// use linear interpolation when minifying and magnifying
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
	stbi_image_free(imageData);
}

Texture::Texture(const std::vector<std::string>& filenames) {
	stbi_set_flip_vertically_on_load(true);
	// load image data from file
	int width, height, channels;
	unsigned char* imageData;

	glGenTextures(1, &p_texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, p_texture);

	for (unsigned int i = 0; i < filenames.size(); i++) {
		imageData = stbi_load(filenames[i].c_str(), &width, &height, &channels, 4);
		if (imageData == NULL) {
			throw std::runtime_error("ERROR: Failed to load texture " + filenames[i]);
		}
		else {
			// load image data into OpenGL cube map texture
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
			stbi_image_free(imageData);
		}
	}

	// wrap textures
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	// use linear interpolation when minifying and magnifying
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture::~Texture() {
	glDeleteTextures(1, &p_texture);
}

void Texture::bind(unsigned int unit) {
	assert(unit >= 0 && unit <= 31);

	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, p_texture);
}
