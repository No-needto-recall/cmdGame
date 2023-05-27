#pragma once

#include <vector>
#include "ScreenWindow.h"
#include "Game.h"

class Pokemon;

enum OptionType :int {
	
};

//游戏战斗管理
class GameBattleManager {

public:
	//获取句柄
	static GameBattleManager& getInstance();
	//战斗循环	
	void BattleLoop();
	// 初始化战斗，参数为游戏玩家和遭遇的野生宝可梦
	void InitBattle(AutoGamePlayer player, Pokemon* wildPokemon);

	// 执行一个战斗回合，根据当前的战斗状态更新玩家和宝可梦的状态
	void DoBattleRound();

	// 结束战斗，根据战斗结果更新玩家的状态（如经验值、背包中的宝可梦等）
	void EndBattle();

	// 玩家逃跑，结束战斗并更新玩家的状态
	void EscapeBattle();

	// 使用精灵球捕获宝可梦，如果成功则结束战斗并更新玩家的状态（如背包中的宝可梦等）
	void CatchPokemon();

	// 当宝可梦血量过低或战斗无法继续时调用，结束战斗并更新玩家的状态
	void PokemonFainted();

	// 返回当前是否在战斗中
	bool InBattle() const;

private:
	
	AutoGamePlayer _player;    //玩家指针
	Pokemon* _playerPokemon;//玩家目前使用的宝可梦
	Pokemon* _pokemon;//与玩家对战的宝可梦
	bool _inBattle; // 表示是否在战斗中
	vector<ScreenWindow> _windows;//窗口管理

	//初始化战斗UI界面
	void LoadBattleUI();
	//选择窗口
	void SelectWindow();

	// 判断战斗结果
	void DetermineBattleOutcome();

	// 处理战斗胜利的情况，如更新玩家的状态（如经验值等）
	void HandleVictory();

	// 处理战斗失败的情况，如更新玩家的状态（如血量、背包中的宝可梦等）
	void HandleDefeat();

	// 设置战斗状态，用于在特定条件下结束战斗
	void SetInBattle(bool inBattle);

	//单例模式，构造私有，禁用赋值语句
	GameBattleManager(const GameBattleManager&) = delete;
	void operator =(const GameBattleManager&) = delete;
	GameBattleManager();
};
