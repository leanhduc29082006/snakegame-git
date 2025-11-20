#pragma once
#include "state.hpp"
#include <memory>
#include <stack>
namespace engine{
    class statemanager{
        private:
            std::stack<std::unique_ptr<engine::state>> m_statestack;
            std::unique_ptr<engine::state> m_newstate;
            bool m_add;
            bool m_replace;
            bool m_remove;
            public:
            statemanager();
            ~statemanager();
            void addstate(std::unique_ptr<engine::state> toAdd,bool replace=false);
            void popstate();
            void processstatechanges();
            std::unique_ptr<engine::state>& getcurrentstate();

    };
}