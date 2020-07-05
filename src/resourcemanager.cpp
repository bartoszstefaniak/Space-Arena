// Bartosz Stefaniak

#include "resourcemanager.hpp"

#include <iostream>

const sf::Texture& ResourceManager::get_texture(const std::string& path, bool smooth, bool repeated)
{
    if(textures.find(path) == textures.end())
    {
        std::unique_ptr<sf::Texture> ptr = std::make_unique<sf::Texture>();
        std::clog << "Loading texture. Path: " << path << "\n";
        if(!ptr->loadFromFile(path))
        {
            std::cerr << "Failed to load texture. Path: " << path << "\n";
            exit(1);
        }
        if(smooth) ptr->setSmooth(true);
        if(repeated) ptr->setRepeated(true);

        textures[path] = std::move(ptr);

        return *textures[path];
    }
    else
    {
        return *textures[path];
    }
}

const sf::Font& ResourceManager::get_font(const std::string& path)
{
    if(fonts.find(path) == fonts.end())
    {
        std::unique_ptr<sf::Font > ptr = std::make_unique<sf::Font>();
        std::clog << "Loading font. Path: " << path << "\n";
        if(!ptr->loadFromFile(path))
        {
            std::cerr << "Failed to load font. Path: " << path << "\n";
            exit(1);
        }

        fonts[path] = std::move(ptr);

        return *fonts[path];
    }
    else
    {
        return *fonts[path];
    }
}