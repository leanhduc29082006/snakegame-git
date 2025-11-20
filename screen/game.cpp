#include "game.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Color.hpp>
#include "mainmenu.hpp"
#include <fstream>
void LoadHighScore(std::shared_ptr<context>& context) {
    std::ifstream readFile("highscore.txt");
    if (readFile.is_open()) {
        readFile >> context->m_highestScore;
        readFile.close();
    } else {
        context->m_highestScore = 0;
    }
}
game::game() : m_context(std::make_shared<context>()) {
    m_context->m_window->create(sf::VideoMode({640, 352}), "Snake Game", sf::Style::Titlebar | sf::Style::Close);
    m_context->m_window->setFramerateLimit(60);
    LoadHighScore(m_context);
    m_context->m_window->setVerticalSyncEnabled(true);
    m_context->m_states->addstate(std::make_unique<mainmenu>(m_context));
}
game::~game() {}


void game::run(){
    sf::Time timeSinceLastframe=sf::Time::Zero;
    sf::Clock clock;
    while(m_context->m_window->isOpen()){
        timeSinceLastframe+=clock.restart();
        if(timeSinceLastframe>=timeperframe){
            timeSinceLastframe-=timeperframe;
            m_context->m_states->processstatechanges();
            m_context->m_states->getcurrentstate()->processInput();
            m_context->m_states->getcurrentstate()->update(timeperframe);
            m_context->m_states->getcurrentstate()->Draw();
            ;
        }
    }
}
