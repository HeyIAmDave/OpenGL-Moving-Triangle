#include "ModelLoader.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

ModelLoader::ModelLoader()
{ }

Model & ModelLoader::Load(const std::string & filePath)
{
	if (m_models.find(filePath) == m_models.end())
	{
		tinyobj::attrib_t attrib;
		std::vector<tinyobj::shape_t> shapes;

		std::string warn, err;
		tinyobj::LoadObj(&attrib, &shapes, 0, &warn, &err, ("./data/" + filePath).c_str());

		if (!warn.empty())
			printf("Model Loader warning: %s\n", warn.c_str());
		if (!err.empty())
			printf("Model Loader error: %s\n", err.c_str());

		Mesh mesh;
		for (const auto& shape : shapes)
		{
			for (const auto& index : shape.mesh.indices)
			{
				glm::vec3 pos =
				{
					attrib.vertices[3 * index.vertex_index + 0],
					attrib.vertices[3 * index.vertex_index + 1],
					attrib.vertices[3 * index.vertex_index + 2]
				};

				glm::vec2 texCoord =
				{
					attrib.texcoords[2 * index.texcoord_index + 0],
					attrib.texcoords[2 * index.texcoord_index + 1],
				};

				Vertex vertex(pos, texCoord, { 1, 1, 1 });
				mesh.indices.push_back(mesh.vertices.size());
				mesh.vertices.push_back(vertex);
			}
		}

		std::shared_ptr<Model> model = std::make_shared<Model>();
		model->Init(mesh);

		m_models[filePath] = model;
	}

	return *m_models[filePath];
}

void ModelLoader::CleanUp()
{
	for (auto& model : m_models)
		model.second->CleanUp();
}