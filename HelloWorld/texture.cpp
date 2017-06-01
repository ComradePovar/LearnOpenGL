#include "texture.h"

Texture::Texture() {
	glGenTextures(1, &textureId);
	textureUnit = textureCount++;
}

Texture::Texture(const GLchar* filePath) : Texture() {
	loadTexture(filePath);
}

void Texture::loadTexture(const GLchar* filePath) {
	int width, height, numConponents;
	unsigned char* image = SOIL_load_image(filePath, &width, &height, 0, SOIL_LOAD_RGB);

	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Texture::getTextureId() const {
	return textureId;
}

void Texture::bindTexture() const {
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(GL_TEXTURE_2D, textureId);
}

void Texture::unbindTexture() const {
	glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Texture::getTextureUnit() const {
	return textureUnit;
}

GLuint Texture::textureCount = 0;