#include "gameplay.hpp"
#include <SFML/Window/Event.hpp>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <cmath>
#include <gameover.hpp>
#include <pause.hpp>
#include <string>
#include <fstream>
gameplay::gameplay(std::shared_ptr<context> &context) : m_context(context),m_snakedirection({16.f,0.f}),m_elapsedtime(sf::Time::Zero),m_score(0)
{
    srand(time(nullptr));
}
gameplay::~gameplay(){}
void SaveHighScore(std::shared_ptr<context>& context, int newScore) {
    if (newScore > context->m_highestScore) {
        context->m_highestScore = newScore;
        std::ofstream writeFile("highscore.txt");
        if (writeFile.is_open()) {
            writeFile << context->m_highestScore;
            writeFile.close();
        }
    }
}
void gameplay::Init(){
    //snake
    m_context->m_assets->loadTexture(texture_snakehead,"assets/snake/snakebody.png");
    m_snake.Init(m_context->m_assets->getTexture(texture_snakehead));
    //food
    m_context->m_assets->loadTexture(texture_food,"assets/food/ChickenLeg.png");
    const sf::Texture& foodTexture=m_context->m_assets->getTexture(texture_food);
    m_food=std::make_unique<sf::Sprite>(foodTexture);
    unsigned int windowX = m_context->m_window->getSize().x;
    unsigned int windowY = m_context->m_window->getSize().y;
    const int cellSize = 16;
    const int minCell = 1;
    const int maxCellX = (windowX / cellSize) - 2;
    const int maxCellY = (windowY / cellSize) - 2;
    int cellX = minCell + (rand() % (maxCellX - minCell + 1));
    int cellY = minCell + (rand() % (maxCellY - minCell + 1));
    float foodX = cellX * cellSize;
    float foodY = cellY * cellSize;
    m_food->setPosition({foodX, foodY});
    //ground
    m_context->m_assets->loadTexture(texture_ground,"assets/grass/grasstop.png",true);
    const sf::Texture& groundTexture=m_context->m_assets->getTexture(texture_ground);
    m_ground=std::make_unique<sf::Sprite>(groundTexture);
    m_ground->setTextureRect(m_context->m_window->getViewport(m_context->m_window->getDefaultView()));
    //walls
    m_context->m_assets->loadTexture(texture_wall,"assets/wall/wall.png",true);
    for (auto&wall:m_wall)
    {
        const sf::Texture& wallTexture=m_context->m_assets->getTexture(texture_wall);
        wall=std::make_unique<sf::Sprite>(wallTexture);
    }
    m_wall[0]->setTextureRect(sf::IntRect({0, 0}, {m_context->m_window->getSize().x, 16}));
    m_wall[1]->setTextureRect(sf::IntRect({0, 0}, {16, m_context->m_window->getSize().y}));
    m_wall[2]->setTextureRect(sf::IntRect({0, 0}, {m_context->m_window->getSize().x, 16}));
    m_wall[2]->setPosition({0, m_context->m_window->getSize().y - 16});
    m_wall[3]->setTextureRect(sf::IntRect({0, 0}, {16, m_context->m_window->getSize().y}));
    m_wall[3]->setPosition({m_context->m_window->getSize().x - 16, 0});
    const sf::Font& scorefont=m_context->m_assets->getFont(main_font);
    m_scoretext=std::make_unique<sf::Text>(scorefont,"Score: 0",16);
    m_scoretext->setFillColor(sf::Color::White);
    m_scoretext->setPosition({10.f,10.f});
}
void gameplay::processInput(){
    while (auto event = m_context->m_window->pollEvent()){
        if (event->is<sf::Event::Closed>()) {
            m_context->m_window->close();
        }
        else if (auto key=event->getIf<sf::Event::KeyPressed>())
        {
            sf::Vector2f newDirection=m_snakedirection;
            switch (key->scancode)
            {
            case sf::Keyboard::Scancode::Up:
                if (m_snakedirection.y == 0) newDirection = {0.f, -16.f};
                break;
            case sf::Keyboard::Scancode::Down:
                if (m_snakedirection.y == 0) newDirection = {0.f, 16.f};
                break;
            case sf::Keyboard::Scancode::Left:
                if (m_snakedirection.x == 0) newDirection = {-16.f, 0.f};
                break;
            case sf::Keyboard::Scancode::Right:
                if (m_snakedirection.x == 0) newDirection = {16.f, 0.f};
                break;
            case sf::Keyboard::Scancode::Escape:
                m_context->m_states->addstate(std::make_unique<pausegame>(m_context), false);
                break;
            default:
                break;
            }
            m_snakedirection=newDirection;
        }
        
    }
}
void gameplay::update(sf::Time deltatime){
    m_elapsedtime+=deltatime;
    if(m_elapsedtime.asSeconds()>0.3f){
        bool isOnWall=false;
        for(auto& wall:m_wall){
            if(m_snake.Interact(*wall)){
                SaveHighScore(m_context, m_score);
                m_context->m_states->addstate(std::make_unique<gameover>(m_context),true);
                break;
            }
        }
        if (m_snake.Interact(*m_food)) {
            m_snake.Grow(m_snakedirection);
            unsigned int windowX = m_context->m_window->getSize().x;
            unsigned int windowY = m_context->m_window->getSize().y;
            const int cellSize = 16;
            const int minCell = 1;
            const int maxCellX = (windowX / cellSize) - 2;
            const int maxCellY = (windowY / cellSize) - 2;
            int cellX = minCell + (rand() % (maxCellX - minCell + 1));
            int cellY = minCell + (rand() % (maxCellY - minCell + 1));
            float foodX = cellX * cellSize;
            float foodY = cellY * cellSize;
            m_food->setPosition({foodX, foodY});
            m_score+=10;
            m_scoretext->setString("Score :"+std::to_string(m_score));
        }
        m_snake.Move(m_snakedirection);
        if(m_snake.isSelfIntersecting()){
            m_context->m_states->addstate(std::make_unique<gameover>(m_context),true);
        }
        m_elapsedtime=sf::Time::Zero;
    }   
}
void gameplay::Draw(){
    m_context->m_window->clear(sf::Color::Black);
    m_context->m_window->draw(*m_ground);
    for (const auto& wall : m_wall) {
        m_context->m_window->draw(*wall);
    }
    m_context->m_window->draw(*m_scoretext);
    m_context->m_window->draw(m_snake);
    m_context->m_window->draw(*m_food);
    m_context->m_window->display();
}
void gameplay::pause(){
    m_elapsedtime=sf::Time::Zero;
}
void gameplay::start(){
}