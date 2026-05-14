#pragma once
#include <unordered_map>
#include <memory>
#include <string>
#include "rendering/texture.hpp"

class TextureManager {
    public:
        Texture* load(const std::string& path);
        void clear();
        
    private:
        std::unordered_map<std::string, std::unique_ptr<Texture>> m_cache;
};