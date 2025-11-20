#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include "statemanager.hpp"
#include "assetmanager.hpp"
#include <memory>
#include <SFML/System/Time.hpp>
struct context{
    std::unique_ptr<engine::assetmanager> m_assets;
    std::unique_ptr<engine::statemanager> m_states;
    std::unique_ptr<sf::RenderWindow> m_window;
    int m_highestScore=0;
    context(){
        m_assets=std::make_unique<engine::assetmanager>();
        m_states=std::make_unique<engine::statemanager>();
        m_window=std::make_unique<sf::RenderWindow>();
    }

};
enum assetID{
    main_font,
    texture_snakehead,
    texture_food,
    main_bg,
    texture_wall,
    texture_ground,
    texture_snakebody,
    gameover_bg,
};
class game{
    private:
        std::shared_ptr<context> m_context;
        const sf::Time timeperframe=sf::seconds(1.f/60.f);
    public:
        game();
        ~game();
        void run();
};