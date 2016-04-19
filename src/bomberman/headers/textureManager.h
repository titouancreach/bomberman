#pragma once

#include <map>

#include <SFML/Graphics.hpp>

namespace bomber {

  class TextureManager
  {
  private:

    std::map<std::string, sf::Texture> textures;

  public:

    /* load texture from a file */
    void loadTexture(const std::string &name, const std::string &path);

    /* get texture */
    sf::Texture & getRef(const std::string &name);

    TextureManager();
    virtual ~TextureManager();
  };

}
