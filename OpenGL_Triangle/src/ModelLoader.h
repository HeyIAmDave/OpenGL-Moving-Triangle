#pragma once
#include "Model.h"

#include <memory>
#include <unordered_map>

class ModelLoader
{
	using ModelMap = std::unordered_map<std::string, std::shared_ptr<Model>>;

public:
	ModelLoader();

	Model& Load(const std::string& filePath);

	void CleanUp();
private:
	ModelMap m_models;
};