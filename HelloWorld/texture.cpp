#include "texture.h"

Texture::Texture() {
	glGenTextures(1, &textureId);
	textureUnit = textureCount++;
}

Texture::Texture(const GLchar* filePath) : Texture() {
	loadTexture(filePath);
}

void Texture::loadTexture(const GLchar* filePath) {
	int width, height;
	unsigned char* image = SOIL_load_image(filePath, &width, &height, 0, SOIL_LOAD_RGB);

	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	
	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Texture::getTextureId() const {
	return textureId;
}

void Texture::bindTexture() const {
	glBindTexture(GL_TEXTURE_2D, textureId);
}

void Texture::unbindTexture() const {
	glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Texture::getTextureUnit() const {
	return textureUnit;
}

GLuint Texture::textureCount = 0;