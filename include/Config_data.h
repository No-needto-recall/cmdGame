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
            int spawnX;
            int spawnY;
            char icon;
        } player;
        struct Pokemon 
        {
            string name;
            int health;
            int mana; 
            int attack;
            int defense; 
            char icon;
        }pokemon;
    } role;
    struct Game {
        struct Map {
            int maxRows;
            int maxColumns;
        }map;
    }game;
    void from_json(const nlohmann::json& j);
};

