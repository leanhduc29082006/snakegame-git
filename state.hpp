#pragma once
#include <SFML/System/Time.hpp>
namespace engine{
    class state{
        public:
            state(){};
            virtual ~state(){};
            virtual void Init()=0;
            virtual void processInput()=0;
            virtual void update(sf::Time deltatime){};
            virtual void Draw()=0;
            virtual void pause(){};
            virtual void start(){}
    };
}