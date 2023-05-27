#pragma once

#include <vector>
#include <memory>
#include "InputHandler.h"

using std::vector;
using std::unique_ptr;

using AutoInputHandler = unique_ptr<InputHandler>;

enum GameStateType :int {
	EXPLORE=0,
	BATTLE=1,
	PAUSED=2
};

//当前游戏状态
class GameState {
public:
	GameState();
	~GameState();

	//设置状态
	void SetState(GameStateType state);
	//获取状态
	GameStateType GetState()const;

	//获取当前状态的按键处理
	const AutoInputHandler& GetNowControl();
private:
	//加载按键处理
	void LoadExploreControl();
	void LoadBattleControl();
	void LoadPausedControl();

	GameStateType _stateNow;//当前的状态
	vector<AutoInputHandler> _Control;//按键处理
};
