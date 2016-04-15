#pragma once

#include <SFML/Graphics.hpp>

#include "../map/map.hpp"

namespace Bomber {

    class App
    {
    public:
        static const unsigned int RES_X = 1280;
        static const unsigned int RES_Y = 720;
        static const unsigned int MAX_FPS = 144;
        static const unsigned int BPP = 64;

        std::vector<sf::Drawable>& getEntities();

        App();
        virtual ~App();

    private:

        void processInput();
        void update(const sf::Time& delta);
        void render();

        sf::RenderWindow m_window;
        std::vector<sf::Drawable> m_entities;

        Map map_;

    };
}
