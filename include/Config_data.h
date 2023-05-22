#pragma once

#include <string>
#include <vector>
#include "../lib/nlohmann/json.hpp"

using std::string;
using std::vector;

struct PlayerData
{
    string name;
    string levelID;
    string mapID;
    int x;
    int y;
};


struct LevelData
{
    string levelid;
};


struct MapData {
    string mapid;
	int maxRows;
	int maxColumns;
};

struct TypeData 
{
    string name;
    char icon;
};

struct ConfigData {
    PlayerData player;

	struct Game {
        vector<LevelData> levels;
        vector<MapData> maps;
    }game;
    
    struct Object {
        vector<TypeData> types;
    }object;

    void from_json(const nlohmann::json& j);
};

