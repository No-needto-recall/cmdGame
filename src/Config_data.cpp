#include "config_data.h"

void ConfigData::from_json(const nlohmann::json& j) {
    actor.player.name = j["actor"]["player"]["name"];
    actor.player.health = j["actor"]["player"]["health"];
    actor.player.mana = j["actor"]["player"]["mana"]; // 从JSON数据中读取法力值属性
    actor.player.attack = j["actor"]["player"]["attack"];
    actor.player.defense = j["actor"]["player"]["defense"]; // 从JSON数据中读取防御力属性
    actor.monster.name = j["actor"]["monster"]["name"];
    actor.monster.health = j["actor"]["monster"]["health"];
    actor.monster.mana = j["actor"]["monster"]["mana"]; // 从JSON数据中读取法力值属性
    actor.monster.attack = j["actor"]["monster"]["attack"];
    actor.monster.defense = j["actor"]["monster"]["defense"]; // 从JSON数据中读取防御力属性
}

