#pragma once
#include "state.hpp"
#include <memory>
#include "game.hpp"
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <array>
#include "snake.hpp"
#include <time.h>
class gameplay:public engine::state
{
private:
    std::shared_ptr<context> m_context;
    std::unique_ptr<sf::Text> m_scoretext;
    int score_font;
    int m_score;
    std::unique_ptr<sf::Sprite> m_ground;
    std::array<std::unique_ptr<sf::Sprite>, 4> m_wall;
    std::unique_ptr<sf::Sprite> m_food;
    snake m_snake;
    sf::Vector2f m_snakedirection;
    sf::Time m_elapsedtime;
public:
    gameplay(std::shared_ptr<context> &context);
    ~gameplay();
    void Init() override;
    void processInput() override;
    void update(sf::Time deltatime) override;
    void Draw() override;
    void pause() override;
    void start() override;
};