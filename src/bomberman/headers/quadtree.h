#pragma once

#include <memory>

#include <SFML/System.hpp>

namespace bomber {

typedef unsigned int uint;

template<typename T>
class QuadTree {

public:
  static const uint kCapacity = 4;

  std::array<sf::Vector2<uint>, kCapacity> points;

  std::shared_ptr<QuadTree> northWest;
  std::shared_ptr<QuadTree> northEast;
  std::shared_ptr<QuadTree> southWest;
  std::shared_ptr<QuadTree> southEast;

  bool Insert(const sf::Vector2<uint>& p);
  void Subdivide();

private:
  T datas_;

};


template<typename T>
bool QuadTree<T>::Insert(const sf::Vector2<uint>& p) {
  if (datas_.contains(p))
    return false;

  if (points.size() < points.max_size())
    points[points.size()] = p;

  if (northWest.get() == nullptr) {
    this->Subdivide();
  }

  if (northWest->Insert(p))
    return true;
  if (northEast->Insert(p))
    return true;
  if (southWest->Insert(p))
    return true;
  if (southEast->Insert(p))
    return true;

   return false;
}

template<typename T>
void QuadTree<T>::Subdivide() {
}


}
