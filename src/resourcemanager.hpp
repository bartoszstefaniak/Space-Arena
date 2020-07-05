// Bartosz Stefaniak

#pragma once

#include <map>
#include <string>
#include <SFML/Graphics.hpp>

/*!
    Class for managing globally textures and fonts.\n
    Manages memory allocations for sf::Texture and sf::Font objects.\n
*/
class ResourceManager
{
public:
    /*!
        const std::string& path - path to texture\n
        bool smooth - if set texture will be smoothed.\n
        bool repeated - if set texture will be repeated, used for backgrounds.\n
        If texture was already loaded returns const reference to it, ignoring smooth and repeated parameters,\n
        otherwise loads setting smooth and repeated parameters.\n
    */
    static const sf::Texture& get_texture(const std::string& path, bool smooth = false, bool repeated = false);

    /*!
        const std::string& path - path to font\n
        If font was already loaded returns const reference to it, otherwise loads it into memory.\n
    */
    static const sf::Font& get_font(const std::string& name);

private:
    inline static std::map<std::string, std::unique_ptr<sf::Texture> > textures;
    inline static std::map<std::string, std::unique_ptr<sf::Font > >   fonts;
};