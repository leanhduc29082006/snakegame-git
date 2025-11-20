#pragma once
#include "state.hpp"
#include <memory>
#include "game.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
class gameover:public engine::state{
    private:
        std::shared_ptr<context> m_context;
        std::unique_ptr<sf::Sprite>  m_gameover_bg;
        std::unique_ptr<sf::Text> m_mainmenuButton;
        std::unique_ptr<sf::Text> m_exitbutton;
        std::unique_ptr<sf::Text> m_gameovertitle;
        std::unique_ptr<sf::Text> m_retryButton;
        std::unique_ptr<sf::Text> m_highScoreText;
        bool m_isMainmenuButtonSelected;
        bool m_isMainmenuButtonPressed;
        bool m_isRetryButtonSelected;
        bool m_isRetryButtonPressed;
        bool m_isExitButtonSelected;
        bool m_isExitButtonPressed;
        sf::Clock m_inputTimer;
        float m_inputDelay = 0.15f;
    public:
        gameover(std::shared_ptr<context> &context);
        ~gameover();
        void Init() override;
        void processInput() override;
        void update(sf::Time deltatime) override;
        void Draw() override;
};