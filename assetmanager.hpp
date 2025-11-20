#pragma once
#include <map>
#include <memory>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <string>
namespace engine{
    class assetmanager{
        private:
            std::map<int,std::unique_ptr<sf::Texture>> m_textures;
            std::map<int,std::unique_ptr<sf::Font>> m_fonts;
        public:
            assetmanager();
            ~assetmanager();
            void loadTexture(int id,const std::string& filepath,bool isRepeated=false);
            void loadFont(int id,const std::string& filepath);
            const sf::Texture& getTexture(int id) const;
            const sf::Font& getFont(int id) const;
    };
}