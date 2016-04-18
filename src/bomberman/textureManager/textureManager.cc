#include <SFML/Graphics.hpp>

#include "textureManager.h"

namespace bomber {

/*!
   \brief Constructor of the TextureManager
*/
TextureManager::TextureManager() {
}

/*!
   \brief Destructor of the TextureManager
*/
TextureManager::~TextureManager() {
}

/*!
   \brief Load texture into the texture Manager
   \param name index of the texture
   \param path path to the asset
*/
void TextureManager::loadTexture(const std::string& name, const std::string& path) {
  sf::Texture texture;

  /* load the texture */
  texture.loadFromFile(path);

  /* add the texture */
  this->textures[name] = texture;
}

/*!
   \brief Return a reference on a loaded texture
   \param index name of the texture
   \return reference on texture
*/
sf::Texture& TextureManager::getRef(const std::string& index) {
  return this->textures.at(index);
}

}
