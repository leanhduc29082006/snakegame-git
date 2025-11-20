#include "gameover.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>
#include "gameplay.hpp"
#include "mainmenu.hpp"
gameover::gameover(std::shared_ptr<context> &context) : m_context(context),
                                                        m_isRetryButtonPressed(false),
                                                        m_isRetryButtonSelected(true),
                                                        m_isMainmenuButtonPressed(false),
                                                        m_isMainmenuButtonSelected(false),
                                                        m_isExitButtonPressed(false),
                                                        m_isExitButtonSelected(false)
{}
gameover::~gameover(){}
void gameover::Init() {
    m_context->m_assets->loadFont(main_font, "assets/fonts/PlaywriteAUTAS-VariableFont_wght.ttf");
    //gameover title
    const sf::Font& font = m_context->m_assets->getFont(main_font);
    m_gameovertitle = std::make_unique<sf::Text>(font, "Game Over!", 48);
    m_gameovertitle->setFillColor(sf::Color::White);
    sf::FloatRect bounds = m_gameovertitle->getLocalBounds();
    m_gameovertitle->setOrigin({
        bounds.position.x + bounds.size.x / 2.f,
        bounds.position.y + bounds.size.y / 2.f
    });
    m_gameovertitle->setPosition({
        m_context->m_window->getSize().x / 2.f,
        m_context->m_window->getSize().y / 4.f
    });
    //retry button
    m_retryButton = std::make_unique<sf::Text>(font, "Retry", 32);
    m_retryButton->setFillColor(sf::Color::White);
    sf::FloatRect playbounds = m_retryButton->getLocalBounds();
    m_retryButton->setOrigin({
        playbounds.position.x + playbounds.size.x / 2.f,
        playbounds.position.y + playbounds.size.y / 2.f
    });
    m_retryButton->setPosition({
        m_context->m_window->getSize().x / 2.f,
        m_context->m_window->getSize().y / 2.f
    });
    //mainmenu button
    m_mainmenuButton = std::make_unique<sf::Text>(font, "Main menu", 32);
    m_mainmenuButton->setFillColor(sf::Color::White);
    sf::FloatRect mainmenubounds = m_mainmenuButton->getLocalBounds();
    m_mainmenuButton->setOrigin({
        mainmenubounds.position.x + mainmenubounds.size.x / 2.f,
        mainmenubounds.position.y + mainmenubounds.size.y / 2.f
    });
    m_mainmenuButton->setPosition({
        m_context->m_window->getSize().x / 2.f,
        m_context->m_window->getSize().y*0.65f
    });
    //exit button
    m_exitbutton = std::make_unique<sf::Text>(font, "Exit", 32);
    m_exitbutton->setFillColor(sf::Color::White);
    sf::FloatRect exitbounds = m_exitbutton->getLocalBounds();
    m_exitbutton->setOrigin({
        exitbounds.position.x + exitbounds.size.x / 2.f,
        exitbounds.position.y + exitbounds.size.y / 2.f
    });
    m_exitbutton->setPosition({
        m_context->m_window->getSize().x / 2.f,
        m_context->m_window->getSize().y*0.80f
    });
    //gameover background
    m_context->m_assets->loadTexture(gameover_bg, "assets/backgrounds/gameover/hieu.png");
    const sf::Texture& bgTexture = m_context->m_assets->getTexture(gameover_bg);
    m_gameover_bg = std::make_unique<sf::Sprite>(bgTexture);
    sf::Vector2u windowSize = m_context->m_window->getSize();
    sf::Vector2u textureSize = bgTexture.getSize();
    m_gameover_bg->setScale({
        static_cast<float>(windowSize.x) / textureSize.x,
        static_cast<float>(windowSize.y) / textureSize.y
    });
    //highscore
    m_highScoreText = std::make_unique<sf::Text>(font, "High Score: " + std::to_string(m_context->m_highestScore), 20);
    m_highScoreText->setFillColor(sf::Color::Yellow);
    sf::FloatRect hsBounds = m_highScoreText->getLocalBounds();
    m_highScoreText->setOrigin({hsBounds.position.x + hsBounds.size.x / 2.f, hsBounds.position.y});
    m_highScoreText->setPosition({m_context->m_window->getSize().x / 2.f, 10.f});
}
void gameover::processInput() {
    while (auto event = m_context->m_window->pollEvent()){
        if (event->is<sf::Event::Closed>()) {
            m_context->m_window->close();
        }
        else if(auto key=event->getIf<sf::Event::KeyReleased>()){
             if (m_inputTimer.getElapsedTime().asSeconds() < m_inputDelay)
                continue;
                m_inputTimer.restart(); 
            switch (key->scancode)
            {
            case sf::Keyboard::Scancode::Up:{
                if (m_isExitButtonSelected){
                    m_isRetryButtonSelected = false;
                    m_isMainmenuButtonSelected = true;
                    m_isExitButtonSelected = false;
                }
                else if (m_isMainmenuButtonSelected){
                    m_isRetryButtonSelected = true;
                    m_isMainmenuButtonSelected = false;
                    m_isExitButtonSelected = false;
                }
                break;
            }
            case sf::Keyboard::Scancode::Down:{
                if(m_isRetryButtonSelected){
                    m_isExitButtonSelected=m_isRetryButtonSelected=false;
                    m_isMainmenuButtonSelected=true;
                }
                else if(m_isMainmenuButtonSelected){
                    m_isExitButtonSelected=true;
                    m_isMainmenuButtonSelected=m_isRetryButtonSelected=false;
                }
                break;
            }
            case sf::Keyboard::Scancode::Enter:{
                m_isRetryButtonPressed=false;
                m_isExitButtonPressed=false;
                m_isMainmenuButtonPressed=false;
                if(m_isRetryButtonSelected){
                    m_isRetryButtonPressed=true;
                }
                else if(m_isExitButtonSelected){
                    m_isExitButtonPressed=true;
                }
                else if(m_isMainmenuButtonSelected){
                    m_isMainmenuButtonPressed=true;
                }
                break;
            }
            default:
                break;
            }
        }
    }
}
void gameover::update(sf::Time) {
    if(m_isRetryButtonSelected){
        m_retryButton->setFillColor(sf::Color::Red);
        m_mainmenuButton->setFillColor(sf::Color::White);
        m_exitbutton->setFillColor(sf::Color::White);
        m_retryButton->setScale({1.2f,1.2f});
        m_mainmenuButton->setScale({1.f,1.f});
        m_exitbutton->setScale({1.f,1.f});
    }
    if(m_isMainmenuButtonSelected){
        m_mainmenuButton->setFillColor(sf::Color::Red);
        m_retryButton->setFillColor(sf::Color::White);
        m_exitbutton->setFillColor(sf::Color::White);
        m_exitbutton->setScale({1.f,1.f});
        m_mainmenuButton->setScale({1.2f,1.2f});
        m_retryButton->setScale({1.f,1.f});
    }
    if(m_isExitButtonSelected){
        m_exitbutton->setFillColor(sf::Color::Red);
        m_retryButton->setFillColor(sf::Color::White);
        m_mainmenuButton->setFillColor(sf::Color::White);
        m_exitbutton->setScale({1.2f,1.2f});
        m_mainmenuButton->setScale({1.f,1.f});
        m_retryButton->setScale({1.f,1.f});
    }
    if(m_isRetryButtonPressed){
        m_isRetryButtonPressed=false;
        m_context->m_states->addstate(std::make_unique<gameplay>(m_context), true);
    }
    if(m_isMainmenuButtonPressed){
        m_isMainmenuButtonPressed=false;
        m_context->m_states->addstate(std::make_unique<mainmenu>(m_context), true);
    }
    if(m_isExitButtonPressed){
        m_isExitButtonPressed=false;
        m_context->m_window->close();
    }
}
void gameover::Draw() {
    m_context->m_window->clear();
    m_context->m_window->draw(*m_gameover_bg);
    m_context->m_window->draw(*m_highScoreText);
    m_context->m_window->draw(*m_gameovertitle);
    m_context->m_window->draw(*m_retryButton);
    m_context->m_window->draw(*m_exitbutton);   
    m_context->m_window->draw(*m_mainmenuButton);
    m_context->m_window->display();
}

