#include "statemanager.hpp"
using namespace engine;
statemanager::statemanager():m_add(false),m_replace(false),m_remove(false){}
statemanager::~statemanager(){}
void statemanager::addstate(std::unique_ptr<engine::state> toAdd,bool replace){
    m_add=true;
    m_replace=replace;
    m_newstate=std::move(toAdd);
}
void statemanager::popstate(){
    m_remove=true;
}
void statemanager::processstatechanges(){
    if(m_remove &&!m_statestack.empty()){
        m_statestack.pop();
        if(!m_statestack.empty()){
            m_statestack.top()->start();
        }
    }
    m_remove=false;
    if(m_add){
        if(m_replace&&!m_statestack.empty()){
            m_statestack.pop();
            m_replace=false;
        }
        if(!m_statestack.empty()){
            m_statestack.top()->pause();
        }
        m_statestack.push(std::move(m_newstate));
        m_statestack.top()->Init();
        m_statestack.top()->start();
        m_add=false;

    }
}
std::unique_ptr<engine::state>& statemanager::getcurrentstate(){
    return m_statestack.top();
}