#include "mainmenu.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>
#include "gameplay.hpp"
mainmenu::mainmenu(std::shared_ptr<context> &context) : m_context(context),
                                                        m_isPlaySelected(true),
                                                        m_isplaybuttonpressed(false),
                                                        m_isexitselected(false),
                                                        m_isexitbuttonpressed(false)
{}
mainmenu::~mainmenu() {}
void mainmenu::Init() {
    m_context->m_assets->loadFont(main_font, "assets/fonts/PlaywriteAUTAS-VariableFont_wght.ttf");
    const sf::Font& font = m_context->m_assets->getFont(main_font);
    m_gametitle = std::make_unique<sf::Text>(font, "Snake Game", 48);
    m_gametitle->setFillColor(sf::Color::White);
    sf::FloatRect bounds = m_gametitle->getLocalBounds();
    m_gametitle->setOrigin({
        bounds.position.x + bounds.size.x / 2.f,
        bounds.position.y + bounds.size.y / 2.f
    });
    m_gametitle->setPosition({
        m_context->m_window->getSize().x / 2.f,
        m_context->m_window->getSize().y / 4.f
    });
    //play button
    m_playbutton = std::make_unique<sf::Text>(font, "Start game", 32);
    m_playbutton->setFillColor(sf::Color::White);
    sf::FloatRect playbounds = m_playbutton->getLocalBounds();
    m_playbutton->setOrigin({
        playbounds.position.x + playbounds.size.x / 2.f,
        playbounds.position.y + playbounds.size.y / 2.f
    });
    m_playbutton->setPosition({
        m_context->m_window->getSize().x / 2.f,
        m_context->m_window->getSize().y / 2.f
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
        m_context->m_window->getSize().y*0.65f
    });
    //background
    m_context->m_assets->loadTexture(main_bg, "assets/backgrounds/menu/huy.png");
    const sf::Texture& bgTexture = m_context->m_assets->getTexture(main_bg);
    m_background = std::make_unique<sf::Sprite>(bgTexture);
    sf::Vector2u windowSize = m_context->m_window->getSize();
    sf::Vector2u textureSize = bgTexture.getSize();
    m_background->setScale({
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
void mainmenu::processInput() {
    while (auto event = m_context->m_window->pollEvent()){
        if (event->is<sf::Event::Closed>()) {
            m_context->m_window->close();
        }
        else if(auto key=event->getIf<sf::Event::KeyReleased>()){
            if (m_inputTimer.getElapsedTime().asSeconds() < m_inputDelay)
                continue;
            m_inputTimer.restart();
            switch (key->scancode)
            case sf::Keyboard::Scancode::Up:{
                if(!m_isPlaySelected){
                    m_isPlaySelected=true;
                    m_isexitselected=false;
                }
                break;
            case sf::Keyboard::Scancode::Down:{
                if(!m_isexitselected){
                    m_isexitselected=true;
                    m_isPlaySelected=false;
                }
                break;
            }
            case sf::Keyboard::Scancode::Enter:{
                m_isplaybuttonpressed=false;
                m_isexitbuttonpressed=false;
                if(m_isPlaySelected){
                    m_isplaybuttonpressed=true;
                }
                else if(m_isexitselected){
                    m_isexitbuttonpressed=true;
                }
                break;
            }
            default:
                break;
            }
        }
    }
}
void mainmenu::update(sf::Time) {
    if(m_isPlaySelected){
        m_playbutton->setFillColor(sf::Color::Red);
        m_exitbutton->setFillColor(sf::Color::White);
        m_playbutton->setScale({1.2f,1.2f});
        m_exitbutton->setScale({1.f,1.f});
    }
    if(m_isexitselected){
        m_exitbutton->setFillColor(sf::Color::Red);
        m_playbutton->setFillColor(sf::Color::White);
        m_exitbutton->setScale({1.2f,1.2f});
        m_playbutton->setScale({1.f,1.f});
    }
    if(m_isplaybuttonpressed){
        m_context->m_states->addstate(std::make_unique<gameplay>(m_context), true);
    }
    if(m_isexitbuttonpressed){
        m_context->m_window->close();
    }
}
void mainmenu::Draw() {
    m_context->m_window->clear();
    m_context->m_window->draw(*m_background);
    m_context->m_window->draw(*m_highScoreText);
    m_context->m_window->draw(*m_gametitle);
    m_context->m_window->draw(*m_playbutton);
    m_context->m_window->draw(*m_exitbutton);   
    m_context->m_window->display();
}
