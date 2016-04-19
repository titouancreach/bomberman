#pragma once

#include <memory>

#include <SFML/System.hpp>

namespace bomber {

typedef unsigned int uint;

template<typename T>
class QuadTree {

public:
  static const uint kCapacity = 4;

  std::vector<sf::Vector2<uint>> points;

  std::shared_ptr<QuadTree> northWest;
  std::shared_ptr<QuadTree> northEast;
  std::shared_ptr<QuadTree> southWest;
  std::shared_ptr<QuadTree> southEast;

  bool Insert(const sf::Vector2<uint>& p);
  void Subdivide();

private:
  T datas_;

};

}

#include "quadtree.inl"
