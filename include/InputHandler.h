#pragma once

#include <Windows.h>
#include <conio.h>
#include <memory>


//前置声明
class Command;
class GameMap;
class GamePlayer;

using AutoCmd =  std::unique_ptr<Command>;
using AutoGamePlayer= std::shared_ptr<GamePlayer>;

 //命令模式

//角色命令
class Command {
public:
	virtual ~Command(){}
	virtual void execute(AutoGamePlayer actor ) = 0;
};


class leftMove :public Command {
public:
	void execute(AutoGamePlayer actor)override;
};

class rightMove :public Command {
public:
	void execute(AutoGamePlayer actor) override;
	
};

class upMove :public Command {
public:
	void execute(AutoGamePlayer actor) override;
};

class downMove :public Command {
public:
	void execute(AutoGamePlayer actor) override;
};

class Quit:public Command {
public:
	void execute(AutoGamePlayer actor) override;
};

class Nothing :public Command {
public:
	void execute(AutoGamePlayer actor)override;
};

class Confirm :public Command {
public:
	void execute(AutoGamePlayer actor)override;
};

class Back:public Command {
public:
	void execute(AutoGamePlayer actor)override;
};

class InputHandler {

public:
	AutoCmd& handleInput();
	void setButtonA(AutoCmd cmd);
	void setButtonD(AutoCmd cmd);
	void setButtonW(AutoCmd cmd);
	void setButtonS(AutoCmd cmd);
	void setButtonQ(AutoCmd cmd);
	void setButtonJ(AutoCmd cmd);
	void setButtonK(AutoCmd cmd);
	void setNothing(AutoCmd cmd);

private:
	AutoCmd _buttonA;
	AutoCmd _buttonD;
	AutoCmd _buttonW;
	AutoCmd _buttonS;
	AutoCmd _buttonQ;
	AutoCmd _buttonJ;
	AutoCmd _buttonK;
	AutoCmd _nothing;


};
