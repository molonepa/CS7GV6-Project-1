#pragma once

#include "utils/mesh.hpp"
#include "utils/texture.hpp"
#include "utils/shader.hpp"
#include "utils/transform.hpp"

class Object3D {
public:
	//Object3D(const Mesh& mesh, const Texture& texture, const Transform& transform, const Shader& shader) {
		
	//}

	inline void draw(glm::mat4 viewProjectionMatrix) {
		p_shader.bind();
		p_shader.updateUniform("modelMatrix", p_transform.getModelMatrix());
		p_shader.updateUniform("viewProjectionMatrix", viewProjectionMatrix);
		p_texture.bind(0);
		p_mesh.render();
	}
private:
	Mesh p_mesh;
	Texture p_texture;
	Transform p_transform;
	Shader p_shader;
};
