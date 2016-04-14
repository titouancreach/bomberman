#include <iostream>

#include "app.hpp"

namespace Bomber
{

    ///
    /// \brief Constructor of the application.
    ///
    App::App()
        : m_window(sf::VideoMode(RES_X, RES_Y, BPP), "Bomberman")
    {
        sf::Clock clock;
        sf::Time accumulator = sf::Time::Zero;
        sf::Time ups = sf::seconds(1.f / static_cast<float>(MAX_FPS));

        while (m_window.isOpen())
        {

            processInput();

            while (accumulator > ups)
            {
                accumulator -= ups;
                update(ups);
            }

            render();
            accumulator += clock.restart();
        }
    }

    ///
    /// \brief Process user input.
    ///
    void App::processInput()
    {
        sf::Event event;

        while (m_window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                m_window.close();
    }

    ///
    /// \brief Update the application
    /// \description each annimation or move must be
    /// multiplied by delta to avoid lag.
    /// \param delta Ellapsed time since the last frame
    ///
    void App::update(const sf::Time& delta)
    {
        std::cout << delta.asMilliseconds() << std::endl;
    }

    ///
    /// \brief Render the application.
    ///
    void App::render()
    {
        m_window.clear();

        for (auto& i: m_entities)
            m_window.draw(i);

        m_window.display();
    }

    ///
    /// \brief Get drawable entities.
    /// \return vector of the drawabale entities.
    ///
    std::vector<sf::Drawable>& App::getEntities()
    {
        return m_entities;
    }

    ///
    /// \brief Constructor of the application.
    ///
    App::~App()
    {}
}
