#pragma once
#include "state.hpp"
#include <memory>
#include "game.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
class mainmenu: public engine::state{
    private:
        std::shared_ptr<context> m_context;
        std::unique_ptr<sf::Text> m_highScoreText;
        std::unique_ptr<sf::Text> m_gametitle;
        std::unique_ptr<sf::Text> m_playbutton;
        std::unique_ptr<sf::Text> m_exitbutton;
        std::unique_ptr<sf::Sprite> m_background;
        bool m_isPlaySelected;
        bool m_isplaybuttonpressed;
        bool m_isexitselected;
        bool m_isexitbuttonpressed;
        sf::Clock m_inputTimer;
        float m_inputDelay = 0.15f;
    public:
        mainmenu(std::shared_ptr<context> &context);
        ~mainmenu();
        void Init() override;
        void processInput() override;
        void update(sf::Time deltatime) override;
        void Draw() override;
};