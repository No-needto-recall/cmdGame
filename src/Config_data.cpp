#include <Windows.h>
#include "config_data.h"


//用于解决Visual Studio 默认使用 UTF-16 编码存储字符串，
//而 nlohmann::json 则使用 UTF-8 编码。
//因此，可能需要在将字符串从 nlohmann::json 对象转换到 
//Visual Studio 使用的 std::string 时进行编码转换。
std::string utf8_to_local(const std::string& utf8_str) {
	std::wstring wide_str;
	int wide_len = MultiByteToWideChar(CP_UTF8, 0, utf8_str.c_str(), -1, nullptr, 0);
	wide_str.resize(wide_len - 1);
	MultiByteToWideChar(CP_UTF8, 0, utf8_str.c_str(), -1, &wide_str[0], wide_len);

	std::string local_str;
	int local_len = WideCharToMultiByte(CP_ACP, 0, wide_str.c_str(), -1, nullptr, 0, nullptr, nullptr);
	local_str.resize(local_len - 1);
	WideCharToMultiByte(CP_ACP, 0, wide_str.c_str(), -1, &local_str[0], local_len, nullptr, nullptr);

	return local_str;
}


void ConfigData::from_json(const nlohmann::json& j) {
	player.name = utf8_to_local(j["player"]["name"].get<string>());
	player.levelID = utf8_to_local(j["player"]["levelID"].get<string>());
	player.mapID = utf8_to_local(j["player"]["mapID"].get<string>());
	player.x = j["player"]["x"];
	player.y = j["player"]["y"];
	player.lineOfSight = j["player"]["lineOfSight"];

	game.screen.width = j["game"]["screen"]["width"];
	game.screen.height= j["game"]["screen"]["height"];

	for (auto& mapJson : j["game"]["levels"]) {
		game.levels.push_back({
			utf8_to_local(mapJson["levelid"].get<string>()),
			});
	}

	for (auto& mapJson : j["game"]["maps"]) {
		game.maps.push_back({
			utf8_to_local(mapJson["mapid"].get<string>()),
			mapJson["maxRows"],
			mapJson["maxColumns"]
			});
	}

	for (auto& mapJson : j["game"]["portals"]) {
		game.portals.push_back({
			utf8_to_local(mapJson["fromLevel"].get<string>()),
			utf8_to_local(mapJson["fromMap"].get<string>()),
			mapJson["fromX"],
			mapJson["fromY"],
			utf8_to_local(mapJson["toLevel"].get<string>()),
			utf8_to_local(mapJson["toMap"].get<string>()),
			mapJson["toX"],
			mapJson["toY"],
			});

	}

	for (auto& mapJson : j["object"]["types"]) {
		object.types.push_back({
			utf8_to_local(mapJson["name"].get<string>()),
			static_cast<char>(mapJson["icon"].get<int>())
			});
	}

	for (auto& mapJson : j["pokemonSkills"]) {
		pokemonSkills.push_back({
			utf8_to_local(mapJson["name"].get<string>()),
			mapJson["category"],
			mapJson["power"],
			mapJson["accuracy"],
			mapJson["priority"],
			mapJson["maxPP"]
			});
	}


	for (auto& mapJson : j["pokemonSpecies"]) {

		pokemonSpecies.push_back({
			utf8_to_local(mapJson["name"].get<string>()),
			mapJson["baseHP"],
			mapJson["baseAttack"],
			mapJson["baseDefence"],
			mapJson["baseSpecialAttack"],
			mapJson["baseSpecialDefence"],
			mapJson["baseSpeed"],
			mapJson["HpPoint"],
			mapJson["AttackPoint"],
			mapJson["DefencePoint"],
			mapJson["SpecialAttackPoint"],
			mapJson["SpecialDefencePoint"],
			mapJson["SpeedPoint"],
			mapJson["basicEmpirical"],
			});
		for (auto& json : mapJson["learnableSkills"]) {
			pokemonSpecies.back().learnableSkills.push_back(
				utf8_to_local(json.get<string>())
			);
		}
	}

}

