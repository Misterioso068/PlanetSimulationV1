#include "texture_manager.hpp"

Texture* TextureManager::load(const std::string& path) {
    if (m_cache.count(path))
        return m_cache[path].get();
    
    auto texture = std::make_unique<Texture>();
    if (!texture->load(path)) return nullptr;
    
    m_cache[path] = std::move(texture);
    return m_cache[path].get();
}