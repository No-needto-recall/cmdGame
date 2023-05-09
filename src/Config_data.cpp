#include "config_data.h"

void ConfigData::from_json(const nlohmann::json& j) {
    role.player.name = j["role"]["player"]["name"];
    role.player.health = j["role"]["player"]["health"];
    role.player.mana = j["role"]["player"]["mana"]; 
    role.player.attack = j["role"]["player"]["attack"];
    role.player.defense = j["role"]["player"]["defense"];
    role.player.icon= j["role"]["player"]["icon"]; 
    role.player.spawnX= j["role"]["player"]["spawnX"]; 
    role.player.spawnY= j["role"]["player"]["spawnY"]; 

    role.pokemon.name = j["role"]["pokemon"]["name"];
    role.pokemon.health = j["role"]["pokemon"]["health"];
    role.pokemon.mana = j["role"]["pokemon"]["mana"]; 
    role.pokemon.attack = j["role"]["pokemon"]["attack"];
    role.pokemon.defense = j["role"]["pokemon"]["defense"]; 
    role.pokemon.icon= j["role"]["pokemon"]["icon"]; 

    game.map.maxRows= j["game"]["map"]["maxRows"];
    game.map.maxColumns = j["game"]["map"]["maxColumns"];
}

