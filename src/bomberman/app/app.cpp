#include "app.hpp"

namespace Bomber
{

    ///
    /// \brief Constructor of the application.
    ///
    App::App()
        : m_window(sf::VideoMode(RES_X, RES_Y, BPP), "Bomberman")
    {

        while (m_window.isOpen())
        {
            processInput();
            update();
            render();
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
    ///
    void App::update()
    {}

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
