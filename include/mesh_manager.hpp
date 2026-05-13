#pragma once
#include <unordered_map>
#include <memory>
#include <string>
#include "mesh.hpp"

class MeshManager {
    public:
        Mesh* load(const std::string& path);
        void clear();
        
    private:
        std::unordered_map<std::string, std::unique_ptr<Mesh>> m_cache;
};