#pragma once

#include <string>
#include <vector>
#include "../lib/nlohmann/json.hpp"

using std::string;
using std::vector;

struct MapData {
    string mapid;
	int maxRows;
	int maxColumns;
};

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
        vector<MapData> maps;
    }game;
    void from_json(const nlohmann::json& j);
};

