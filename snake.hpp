#pragma once
#include <list>
#include <memory>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
class snake: public sf::Drawable{
    private:
        std::list<sf::Sprite> m_body;
        std::list<sf::Sprite>::iterator m_head;
        std::list<sf::Sprite>::iterator m_tail;
        const sf::Texture *m_headtexture;
        const sf::Texture *m_tailtexture;

    public:
        snake();
        ~snake();
        void Init(const sf::Texture& texture);
        void Move(const sf::Vector2f& direction);
        bool Interact(const sf::Sprite& other) const;
        void Grow(const sf::Vector2f& direction);
        bool isSelfIntersecting() const;
        void draw(sf::RenderTarget& target,sf::RenderStates state) const override;
};