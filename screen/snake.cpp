#include "snake.hpp"
#include <cmath>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
snake::snake(){
};
snake::~snake(){
};
void snake::Init(const sf::Texture& texture){
    float startX=16.f;
    m_body.clear();
    for(int i=0;i<4;i++){
        sf::Sprite piece(texture);
        piece.setPosition({startX,16.f});
        startX+=16.f;
        m_body.push_back(piece); 
    }
    m_head=--m_body.end();
    m_tail=m_body.begin();
}
void snake::Move(const sf::Vector2f& direction){
    m_tail->setPosition(m_head->getPosition()+direction);
    m_head=m_tail;
    m_tail++;
    if(m_tail==m_body.end()){
        m_tail=m_body.begin();
    }
}
bool snake::isSelfIntersecting() const{
    bool flag=false;
    for(auto piece=m_body.begin();piece!=m_body.end();++piece){
        if(m_head!=piece){
            flag=Interact(*piece);
            if(flag){
                break;
            }
        }
    }
    return flag;
}
bool snake::Interact(const sf::Sprite& other) const{
    return m_head->getGlobalBounds().findIntersection(other.getGlobalBounds()).has_value();
}
void snake::Grow(const sf::Vector2f& direction) {
    sf::Sprite newPiece = *m_tail;
    auto newTailIterator = m_body.insert(m_tail, newPiece);
    m_tail = newTailIterator;
}
void snake::draw(sf::RenderTarget& target,sf::RenderStates state) const{
    for(const auto& piece : m_body){
        target.draw(piece,state);
    }
}