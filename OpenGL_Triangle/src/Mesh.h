#pragma once
#include "Vertex.h"

#include <vector>

struct Mesh
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
};