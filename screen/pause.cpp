#include "mainmenu.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Color.hpp>  
#include "gameplay.hpp"
#include "pause.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
pausegame::pausegame(std::shared_ptr<context> &context) : m_context(context),
                                                        m_isContinueSelected(true),
                                                        m_isContinuePressed(false),
                                                        m_isexitbuttonselected(false),
                                                        m_isexitbuttonpressed(false)
{}
pausegame::~pausegame() {}
void pausegame::Init() {
    m_context->m_assets->loadFont(main_font, "assets/fonts/PlaywriteAUTAS-VariableFont_wght.ttf");
    const sf::Font& font = m_context->m_assets->getFont(main_font);
    //pause title
    m_pausetitle = std::make_unique<sf::Text>(font, "Game Paused", 48);
    m_pausetitle->setFillColor(sf::Color::White);
    sf::FloatRect bounds = m_pausetitle->getLocalBounds();
    m_pausetitle->setOrigin({
        bounds.position.x + bounds.size.x / 2.f,
        bounds.position.y + bounds.size.y / 2.f
    });
    m_pausetitle->setPosition({
        m_context->m_window->getSize().x / 2.f,
        m_context->m_window->getSize().y / 4.f
    });
    //continue button
    m_continuebutton = std::make_unique<sf::Text>(font, "Continue", 32);
    m_continuebutton->setFillColor(sf::Color::White);
    sf::FloatRect continuebounds = m_continuebutton->getLocalBounds();
    m_continuebutton->setOrigin({
        continuebounds.position.x + continuebounds.size.x / 2.f,
        continuebounds.position.y + continuebounds.size.y / 2.f
    });
    m_continuebutton->setPosition({
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
}
void pausegame::processInput() {
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
                if(!m_isContinueSelected){
                    m_isContinueSelected=true;
                    m_isexitbuttonselected=false;
                }
                break;
            }
            case sf::Keyboard::Scancode::Down:{
                if(!m_isexitbuttonselected){
                    m_isexitbuttonselected=true;
                    m_isContinueSelected=false;
                }
                break;
            }
            case sf::Keyboard::Scancode::Enter:{
                m_isContinuePressed=false;
                m_isexitbuttonpressed=false;
                if(m_isContinueSelected){
                    m_isContinuePressed=true;
                }
                else if(m_isexitbuttonselected){
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
void pausegame::update(sf::Time) {
    if(m_isContinueSelected){
        m_continuebutton->setFillColor(sf::Color::Red);
        m_exitbutton->setFillColor(sf::Color::White);
        m_continuebutton->setScale({1.2f,1.2f});
        m_exitbutton->setScale({1.f,1.f});
    }
    else if(m_isexitbuttonselected){
        m_exitbutton->setFillColor(sf::Color::Red);
        m_continuebutton->setFillColor(sf::Color::White);
        m_exitbutton->setScale({1.2f,1.2f});
        m_continuebutton->setScale({1.f,1.f});
    }
    if(m_isContinuePressed){
        m_isContinuePressed=false;
        m_context->m_states->popstate();
    }
    if(m_isexitbuttonpressed){
        m_isexitbuttonpressed=false;
        m_context->m_states->addstate(std::make_unique<mainmenu>(m_context),true);
    }
}
void pausegame::Draw() {
    m_context->m_window->clear();
    sf::RectangleShape overlay;
    sf::Vector2u windowSize = m_context->m_window->getSize();
    overlay.setSize(sf::Vector2f(static_cast<float>(windowSize.x),
                                 static_cast<float>(windowSize.y)));
    overlay.setFillColor(sf::Color(0, 0, 0, 150));
    m_context->m_window->draw(overlay);
    m_context->m_window->draw(*m_pausetitle);
    m_context->m_window->draw(*m_continuebutton);
    m_context->m_window->draw(*m_exitbutton);
    m_context->m_window->display();   
}
