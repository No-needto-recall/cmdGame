#include "config_data.h"

void ConfigData::from_json(const nlohmann::json& j) {
    actor.player.name = j["actor"]["player"]["name"];
    actor.player.health = j["actor"]["player"]["health"];
    actor.player.mana = j["actor"]["player"]["mana"]; // 从JSON数据中读取法力值属性
    actor.player.attack = j["actor"]["player"]["attack"];
    actor.player.defense = j["actor"]["player"]["defense"]; // 从JSON数据中读取防御力属性
    actor.pokemon.name = j["actor"]["pokemon"]["name"];
    actor.pokemon.health = j["actor"]["pokemon"]["health"];
    actor.pokemon.mana = j["actor"]["pokemon"]["mana"]; // 从JSON数据中读取法力值属性
    actor.pokemon.attack = j["actor"]["pokemon"]["attack"];
    actor.pokemon.defense = j["actor"]["pokemon"]["defense"]; // 从JSON数据中读取防御力属性
}

