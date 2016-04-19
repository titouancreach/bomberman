namespace bomber {

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
