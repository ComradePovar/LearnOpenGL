#ifndef TEXTURE_H
#define TEXTURE_H

#define GLEW_STATIC
#include <GL\glew.h>
#include <SOIL\SOIL.h>
#include <cstdio>

class Texture {
private:
	static GLuint textureCount;
	GLuint textureUnit;
	GLuint textureId;

public:
	Texture();
	Texture(const GLchar* filePath);

	void bindTexture() const;
	void unbindTexture() const;
	void loadTexture(const GLchar* filePath);

	GLuint getTextureId() const;
	GLuint getTextureUnit() const;
};
#endif