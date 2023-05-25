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
    int lineOfSight;
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

struct PortalData {
    string fromLevel;
    string fromMap;
    int fromX;
    int fromY;
    string toLevel;
    string toMap;
    int toX;
    int toY;
};

struct PokemonSkillData {
    string name;
    int category;
    int power;
    int accuracy;
    int priority;
    int maxPP;
};

struct ConfigData {
    PlayerData player;

	struct Game {
        vector<LevelData> levels;
        vector<MapData> maps;
        vector<PortalData> portals;
    }game;
    
    struct Object {
        vector<TypeData> types;
    }object;
    vector<PokemonSkillData> pokemonSkills;

    void from_json(const nlohmann::json& j);
};

