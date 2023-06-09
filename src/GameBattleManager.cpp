#include "GameBattleManager.h"
#include "GamePlayer.h"
#include "Log.h"
#include "Config.h"

GameBattleManager& GameBattleManager::getInstance()
{
	static GameBattleManager instance;
	return instance;
}

void GameBattleManager::BattleLoop()
{
	while (InBattle()) {
		//玩家选择操作
		DoBattleRound();
	}
	EndBattle();
}

void GameBattleManager::InitBattle(AutoGamePlayer player, Pokemon* wildPokemon)
{
	if (player) {
		_player=player;
	}
	else {
		LOG_ERROR("尝试初始化战斗的player为nullptr");
	}
	if (wildPokemon) {
		_pokemon = wildPokemon;
	}
	else {
		LOG_ERROR("尝试初始化战斗的pokemon为nullptr");
	}
}

void GameBattleManager::DoBattleRound()
{

}

void GameBattleManager::EndBattle()
{

}

void GameBattleManager::EscapeBattle()
{
}

void GameBattleManager::CatchPokemon()
{
}

void GameBattleManager::PokemonFainted()
{
}

bool GameBattleManager::InBattle() const
{
	return _inBattle;
}

void GameBattleManager::LoadBattleUI()
{
	int sight = CONFIG_DATA.player.lineOfSight;
	_windows.emplace_back(sight/4,sight/2,sight,sight/2);
	_windows.emplace_back(sight/4+2*sight,sight/2,sight,sight/2);
	_windows.emplace_back(sight/4,sight/2+sight,sight,sight/2);
	_windows.emplace_back(sight/4+2*sight,sight/2+sight,sight,sight/2);
}


void GameBattleManager::SelectWindow()
{
	while (1) {
	}
}

void GameBattleManager::DetermineBattleOutcome()
{
}

void GameBattleManager::HandleVictory()
{
}

void GameBattleManager::HandleDefeat()
{
}

void GameBattleManager::SetInBattle(bool inBattle)
{
}

GameBattleManager::GameBattleManager()
	:_player(nullptr)
	,_playerPokemon(nullptr)
	,_pokemon(nullptr)
	,_inBattle(true)
{
}
