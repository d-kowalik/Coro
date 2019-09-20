#pragma once

#include <vector>

#include "Mesh.hpp"

inline std::vector<Coro::Vertex> vertices{
	{{-0.5f, -0.5f,  0.5f},  {0.0f,  0.0f, 1.0f}, {0.f, 0.f}},
	{{ 0.5f, -0.5f,  0.5f},  {0.0f,  0.0f, 1.0f}, {0.f, 0.f}},
	{{ 0.5f,  0.5f,  0.5f},  {0.0f,  0.0f, 1.0f}, {0.f, 0.f}},
	{{-0.5f,  0.5f,  0.5f},  {0.0f,  0.0f, 1.0f}, {0.f, 0.f}},
															 
	{{-0.5f,  0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}, {0.f, 0.f}},
	{{-0.5f,  0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}, {0.f, 0.f}},
	{{-0.5f, -0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}, {0.f, 0.f}},
	{{-0.5f, -0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}, {0.f, 0.f}},
															 
	{{ 0.5f,  0.5f,  0.5f},  {1.0f,  0.0f,  0.0f}, {0.f, 0.f}},
	{{ 0.5f,  0.5f, -0.5f},  {1.0f,  0.0f,  0.0f}, {0.f, 0.f}},
	{{ 0.5f, -0.5f, -0.5f},  {1.0f,  0.0f,  0.0f}, {0.f, 0.f}},
	{{ 0.5f, -0.5f,  0.5f},  {1.0f,  0.0f,  0.0f}, {0.f, 0.f}},
															 
	{{-0.5f, -0.5f, -0.5f},  {0.0f, -1.0f,  0.0f}, {0.f, 0.f}},
	{{ 0.5f, -0.5f, -0.5f},  {0.0f, -1.0f,  0.0f}, {0.f, 0.f}},
	{{ 0.5f, -0.5f,  0.5f},  {0.0f, -1.0f,  0.0f}, {0.f, 0.f}},
	{{-0.5f, -0.5f,  0.5f},  {0.0f, -1.0f,  0.0f}, {0.f, 0.f}},
															 
	{{-0.5f,  0.5f, -0.5f},  {0.0f,  1.0f,  0.0f}, {0.f, 0.f}},
	{{ 0.5f,  0.5f, -0.5f},  {0.0f,  1.0f,  0.0f}, {0.f, 0.f}},
	{{ 0.5f,  0.5f,  0.5f},  {0.0f,  1.0f,  0.0f}, {0.f, 0.f}},
	{{-0.5f,  0.5f,  0.5f},  {0.0f,  1.0f,  0.0f}, {0.f, 0.f}},
};

inline std::vector<unsigned> getIndices() {
	std::vector<unsigned> indices{};
	indices.reserve(36);

	for (int j = 0; indices.size() < 36; j += 4) {
		indices.push_back(j);
		indices.push_back(j + 1);
		indices.push_back(j + 3);
		indices.push_back(j + 1);
		indices.push_back(j + 2);
		indices.push_back(j + 3);
	}

	return indices;
}