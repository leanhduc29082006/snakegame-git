#pragma once
#include "state.hpp"
#include <memory>
#include "game.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
class pausegame: public engine::state{
    private:
        std::shared_ptr<context> m_context;
        std::unique_ptr<sf::Text> m_pausetitle;
        std::unique_ptr<sf::Text> m_continuebutton;
        std::unique_ptr<sf::Text> m_exitbutton;
        std::unique_ptr<sf::Sprite> m_background;
        bool m_isContinueSelected;
        bool m_isContinuePressed;
        bool m_isexitbuttonselected;
        bool m_isexitbuttonpressed;
        sf::Clock m_inputTimer;
        float m_inputDelay = 0.15f;
    public:
        pausegame(std::shared_ptr<context> &context);
        ~pausegame();
        void Init() override;
        void processInput() override;
        void update(sf::Time deltatime) override;
        void Draw() override;
};