#pragma once

#include <string>
#include "../lib/nlohmann/json.hpp"

using std::string;

struct ConfigData {
    struct Role {
        struct Player {
            string name;
            int health;
            int mana;  
            int attack;
            int defense;  
        } player;
        struct Pokemon 
        {
            string name;
            int health;
            int mana; 
            int attack;
            int defense; 
        }pokemon;
    } actor;
    void from_json(const nlohmann::json& j);
};

