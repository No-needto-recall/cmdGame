#pragma once

#include <string>
#include <memory>

using std::string;
using std::unique_ptr;



//前置声明
class Behavior;
class GameMap;

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
		const Location& location,
		GameMap& gameMap);


	//析构函数设为虚函数
	virtual ~Role();

	//获取属性
	const Attribute& getAttribute()const;
	Attribute& getAttribute();

	//获取行为
	const unique_ptr<Behavior>& getBehavior()const;
	//设置行为
	void setBehavior(unique_ptr<Behavior> behavior);

	//绑定地图
	void bindGameMap(GameMap& gamemap);


	//碰撞
	//双分派设计模式
	virtual void collide(Role& other) = 0;
	virtual void collideWithPlayer(Role&) = 0;
	virtual void collideWithPokemon(Role&) = 0;
public:
	GameMap& _gameMap;

protected:
	Attribute _attribute;
	unique_ptr<Behavior> _behavior;
	
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


