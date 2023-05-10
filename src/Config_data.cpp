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

	role.player.name = utf8_to_local(j["role"]["player"]["name"].get<string>());
	role.player.health = j["role"]["player"]["health"];
	role.player.mana = j["role"]["player"]["mana"];
	role.player.attack = j["role"]["player"]["attack"];
	role.player.defense = j["role"]["player"]["defense"];
	role.player.spawnX = j["role"]["player"]["spawnX"];
	role.player.spawnY = j["role"]["player"]["spawnY"];
	role.player.icon = static_cast<char>(j["role"]["player"]["icon"].get<int>());

	role.pokemon.name = utf8_to_local(j["role"]["pokemon"]["name"].get<string>());
	role.pokemon.health = j["role"]["pokemon"]["health"];
	role.pokemon.mana = j["role"]["pokemon"]["mana"];
	role.pokemon.attack = j["role"]["pokemon"]["attack"];
	role.pokemon.defense = j["role"]["pokemon"]["defense"];
	role.pokemon.icon = static_cast<char>(j["role"]["pokemon"]["icon"].get<int>());

	game.map.maxRows = j["game"]["map"]["maxRows"];
	game.map.maxColumns = j["game"]["map"]["maxColumns"];
}

