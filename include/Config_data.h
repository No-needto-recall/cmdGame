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

struct TypeData 
{
    string name;
    char icon;
};

struct ConfigData {
	struct Game {
        vector<MapData> maps;
    }game;
    
    struct Object {
        vector<TypeData> types;
    }object;

    void from_json(const nlohmann::json& j);
};

