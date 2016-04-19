#include <gtest/gtest.h>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "quadtree.h"

/*!
 * Test is the constructor can be instanciate
 */
TEST(QuadTreeTest, Constructor) {
  bomber::QuadTree<sf::Rect<uint>> tree;
}

/*!
 * Test if we can insert 4 kCapacity elements
 */
TEST(QuadTreeTest, Insert) {
  bomber::QuadTree<sf::Rect<uint>> tree;

  ASSERT_EQ(tree.Insert({10, 10}), true);
  ASSERT_EQ(tree.Insert({20, 10}), true);
  ASSERT_EQ(tree.Insert({30, 10}), true);
  ASSERT_EQ(tree.Insert({40, 10}), true);
}
