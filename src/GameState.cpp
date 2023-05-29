#include "GameState.h"

using std::move;

GameState::GameState()
	:_stateNow(GameStateType::EXPLORE)
{
	LoadExploreControl();
	LoadBattleControl();
	LoadPausedControl();
}

GameState::~GameState()
{
}

void GameState::SetState(GameStateType state)
{
	_stateNow = state;
}

GameStateType GameState::GetState() const
{
	return _stateNow;
}

const AutoInputHandler& GameState::GetNowControl()
{
	return _Control[static_cast<int>(_stateNow)];
}

void GameState::LoadExploreControl()
{
	AutoInputHandler handler(new InputHandler());
	handler->setButtonA(move(AutoCmd(new leftMove())));
	handler->setButtonD(move(AutoCmd(new rightMove())));
	handler->setButtonW(move(AutoCmd(new upMove())));
	handler->setButtonS(move(AutoCmd(new downMove())));
	handler->setButtonQ(move(AutoCmd(new Quit())));
	handler->setButtonJ(move(AutoCmd(new Nothing())));
	handler->setButtonK(move(AutoCmd(new Nothing())));
	handler->setNothing(move(AutoCmd(new Nothing())));
	_Control.push_back(move(handler));
}

void GameState::LoadBattleControl()
{
	AutoInputHandler handler(new InputHandler());
	handler->setButtonA(move(AutoCmd(new Nothing())));
	handler->setButtonD(move(AutoCmd(new Nothing())));
	handler->setButtonW(move(AutoCmd(new Nothing())));
	handler->setButtonS(move(AutoCmd(new Nothing())));
	handler->setButtonQ(move(AutoCmd(new Quit())));
	handler->setButtonJ(move(AutoCmd(new Nothing())));
	handler->setButtonK(move(AutoCmd(new Nothing())));
	handler->setNothing(move(AutoCmd(new Nothing())));
	_Control.push_back(move(handler));
}

void GameState::LoadPausedControl()
{
	AutoInputHandler handler(new InputHandler());
	handler->setButtonA(move(AutoCmd(new Nothing())));
	handler->setButtonD(move(AutoCmd(new Nothing())));
	handler->setButtonW(move(AutoCmd(new Nothing())));
	handler->setButtonS(move(AutoCmd(new Nothing())));
	handler->setButtonQ(move(AutoCmd(new Quit())));
	handler->setButtonJ(move(AutoCmd(new Nothing())));
	handler->setButtonK(move(AutoCmd(new Nothing())));
	handler->setNothing(move(AutoCmd(new Nothing())));
	_Control.push_back(move(handler));
}
