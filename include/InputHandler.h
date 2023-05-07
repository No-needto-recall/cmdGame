#pragma once

#include <Windows.h>
#include <conio.h>
#include <memory>
#include "GameMap.h"
#include "Player.h"


class Command;
using AutoCmd =  std::unique_ptr<Command>;

//命令模式
class Command {
public:
	virtual ~Command(){}
	virtual void execute(Actor& Gmap) = 0;
};


class leftMove :public Command {
public:
	void execute(Actor& actor)override {
		actor.left();
	}
};

class rightMove :public Command {
public:
	void execute(Actor& actor) override{
		actor.right();
	}
};

class upMove :public Command {
public:
	void execute(Actor& actor) override{
		actor.up();
	}
};

class downMove :public Command {
public:
	void execute(Actor& actor) override{
		actor.down();
	}
};

class Quit:public Command {
public:
	void execute(Actor& actor) override{
		LOG_INFO("主动退出游戏");
		actor.getMap()->setQuit(false);
	}
};

class Nothing :public Command {
public:
	void execute(Actor& actor)override {

	}
};

class InputHandler {

public:
	AutoCmd& handleInput();
	void setButtonA(AutoCmd cmd) { _buttonA = move(cmd); }
	void setButtonD(AutoCmd cmd) { _buttonD = move(cmd); }
	void setButtonW(AutoCmd cmd) { _buttonW = move(cmd); }
	void setButtonS(AutoCmd cmd) { _buttonS = move(cmd); }
	void setButtonQ(AutoCmd cmd) { _buttonQ = move(cmd); }
	void setNothing(AutoCmd cmd) { _nothing= move(cmd); }

private:
	AutoCmd _buttonA;
	AutoCmd _buttonD;
	AutoCmd _buttonW;
	AutoCmd _buttonS;
	AutoCmd _buttonQ;
	AutoCmd _nothing;


};
