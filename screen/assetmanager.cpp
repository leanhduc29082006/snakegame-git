#include "assetmanager.hpp"
using namespace engine;
assetmanager::assetmanager(){}
assetmanager::~assetmanager(){}
void assetmanager::loadTexture(int id,const std::string& filepath,bool isRepeated){
    auto texture=std::make_unique<sf::Texture>();
    if(texture->loadFromFile(filepath)){
        texture->setRepeated(isRepeated);
        m_textures[id]=std::move(texture);
    }
}
void assetmanager::loadFont(int id,const std::string& filepath){
    auto font=std::make_unique<sf::Font>();
   if(font->openFromFile(filepath)){
        m_fonts[id]=std::move(font);
    }
}
const sf::Texture& assetmanager::getTexture(int id) const{
    return *(m_textures.at(id).get());
}
const sf::Font& assetmanager::getFont(int id) const{
    return *(m_fonts.at(id).get());
}