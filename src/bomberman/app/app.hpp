#pragma once

#include <SFML/Graphics.hpp>

namespace Bomber {

    class App
    {
    public:
        static const unsigned int RES_X = 1920;
        static const unsigned int RES_Y = 1080;
        static const unsigned int MAX_FPS = 130;
        static const unsigned int BPP = 64;

        std::vector<sf::Drawable>& getEntities();

        App();
        virtual ~App();

    private:

        void processInput();
        void update();
        void render();

        sf::RenderWindow m_window;
        std::vector<sf::Drawable> m_entities;

    };
}
