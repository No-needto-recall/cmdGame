#pragma once

#include <Windows.h>
#include <conio.h>
#include <memory>


//前置声明
class RoleCommand;
class GameMap;
class Role;

using AutoCmd =  std::unique_ptr<RoleCommand>;
using AutoRole = std::shared_ptr<Role>;

 //命令模式

//角色命令
class RoleCommand {
public:
	virtual ~RoleCommand(){}
	virtual void execute(AutoRole actor ) = 0;
};


class leftMove :public RoleCommand {
public:
	void execute(AutoRole actor)override;
};

class rightMove :public RoleCommand {
public:
	void execute(AutoRole actor) override;
	
};

class upMove :public RoleCommand {
public:
	void execute(AutoRole actor) override;
};

class downMove :public RoleCommand {
public:
	void execute(AutoRole actor) override;
};

class Quit:public RoleCommand {
public:
	void execute(AutoRole actor) override;
};

class Nothing :public RoleCommand {
public:
	void execute(AutoRole actor)override;
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
