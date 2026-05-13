#include "mesh_manager.hpp"

Mesh* MeshManager::load(const std::string& path) {
    if (m_cache.count(path))
        return m_cache[path].get();
    
    auto mesh = std::make_unique<Mesh>();
    if (!mesh->load(path)) return nullptr;
    
    m_cache[path] = std::move(mesh);
    return m_cache[path].get();
}