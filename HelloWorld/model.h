#ifndef MODEL_H
#define MODEL_H
#include <GL\glew.h>
#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>
#include <assimp\scene.h>
#include <SOIL\SOIL.h>
#include <iostream>
#include <vector>
#include "shader.h"
#include "mesh.h"

class Model {
private:
	std::vector<Mesh> meshes;
	std::string directory;
	std::vector<Texture> textures_loaded;

	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	GLuint TextureFromFile(const GLchar* path, const std::string &directory);
public:
	Model(const GLchar* path);
	void draw(Shader shader);
};

#endif