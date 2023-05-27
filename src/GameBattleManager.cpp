#include "GameBattleManager.h"
#include "GamePlayer.h"
#include "Log.h"

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

void GameBattleManager::InitBattle(GamePlayer* player, Pokemon* wildPokemon)
{
	if (player) {
		_player = player;
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
}

void GameBattleManager::LoadBattleControl()
{
	_Control.setButtonA(std::make_unique<Nothing>());
	_Control.setButtonD(std::make_unique<Nothing>());
	_Control.setButtonW(std::make_unique<Nothing>());
	_Control.setButtonS(std::make_unique<Nothing>());
	_Control.setButtonQ(std::make_unique<Quit>());
	_Control.setButtonJ(std::make_unique<Nothing>());
	_Control.setButtonK(std::make_unique<Nothing>());
	_Control.setNothing(std::make_unique<Nothing>());
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
