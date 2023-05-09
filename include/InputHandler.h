#pragma once

#include <Windows.h>
#include <conio.h>
#include <memory>


//前置声明
class Command;
class GameMap;
class Role;

using AutoCmd =  std::unique_ptr<Command>;
//命令模式
class Command {
public:
	virtual ~Command(){}
	virtual void execute(Role* actor,GameMap* gameMap) = 0;
};


class leftMove :public Command {
public:
	void execute(Role* actor, GameMap* gameMap)override;
};

class rightMove :public Command {
public:
	void execute(Role* actor, GameMap* gameMap) override;
	
};

class upMove :public Command {
public:
	void execute(Role* actor, GameMap* gameMap) override;
};

class downMove :public Command {
public:
	void execute(Role* actor, GameMap* gameMap) override;
};

class Quit:public Command {
public:
	void execute(Role* actor, GameMap* gameMap) override;
};

class Nothing :public Command {
public:
	void execute(Role* actor, GameMap* gameMap)override;
};

class InputHandler {

public:
	AutoCmd& handleInput();
	void setButtonA(AutoCmd cmd);
	void setButtonD(AutoCmd cmd);
	void setButtonW(AutoCmd cmd);
	void setButtonS(AutoCmd cmd);
	void setButtonQ(AutoCmd cmd);
	void setNothing(AutoCmd cmd);

private:
	AutoCmd _buttonA;
	AutoCmd _buttonD;
	AutoCmd _buttonW;
	AutoCmd _buttonS;
	AutoCmd _buttonQ;
	AutoCmd _nothing;


};
