#pragma once

#include <string>
#include <memory>

using std::string;
using std::unique_ptr;
using std::shared_ptr;



//前置声明
class Behavior;
class GameMap;
class Role;

using AutoGameMap = shared_ptr<GameMap>;
using AutoBehavior = unique_ptr<Behavior>;
using AutoRole = shared_ptr<Role>;

//位置信息
struct Location
{
	int _x;
	int _y;
	string toString()const;
};

//属性信息
struct Attribute
{
	string _name;
	int _health;
	int _mana;
	int _attack;
	int _defense;
	char _icon;//图标

	bool isAlive()const;
	bool isDeath()const;
};


//基类角色类
class BasicRole {
public:

	BasicRole(const  Location& location);
	virtual ~BasicRole();
	//获取位置
	const Location& getLocation()const;
	Location& getLocation();

protected:
	Location _location;
};


//角色
class Role:public BasicRole{
public:
	Role(const Attribute& attribute,
		const Location& location);

	Role(const Attribute& attribute,
		const Location& location,
		AutoBehavior behavior);
	Role(const Attribute& attribute,
		const Location& location,
		AutoGameMap gamemap);

	Role(const Attribute& attribute,
		const Location& location,
		AutoBehavior behavior,AutoGameMap gamemap);

	//析构函数设为虚函数
	virtual ~Role();

	//获取属性
	const Attribute& getAttribute()const;
	Attribute& getAttribute();
	//属性接口
	bool isAlive()const;
	bool isDeath()const;


	//设置行为
	void setBehavior(AutoBehavior  behavior);
	//行为接口
	void upMove();
	void downMove();
	void leftMove();
	void rightMove();
	void death();
	void attack(Role& target);


	//绑定地图
	void setGameMap(AutoGameMap gamemap);
	//获取地图
	AutoGameMap& getGameMap();


	//碰撞
	//双分派设计模式
	virtual void collide(Role& other) = 0;
	virtual void collideWithPlayer(Role&) = 0;
	virtual void collideWithPokemon(Role&) = 0;

protected:
	Attribute _attribute;
	AutoBehavior _behavior;
	AutoGameMap _gameMap;
	
};

//玩家角色
class PlayerRole :public Role {
public:
	using Role::Role;

	//碰撞
	//双分派设计模式
	virtual void collide(Role& other) override;
	virtual void collideWithPlayer(Role&)  override;
	virtual void collideWithPokemon(Role&) override;
};

//玩家角色
class PokemonRole:public Role {
public:
	using Role::Role;

	//碰撞
	//双分派设计模式
	virtual void collide(Role& other) override;
	virtual void collideWithPlayer(Role&)  override;
	virtual void collideWithPokemon(Role&) override;
};




