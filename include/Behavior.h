#pragma once

#include <memory>

class Role;
class GameMap;
class PlayerBehavior;
class PokemonBehavior;

using std::weak_ptr;

using AutoWeakRole = weak_ptr<Role>;

//行为类
class Behavior {
public:
	Behavior(AutoWeakRole myself);
	virtual ~Behavior() = default;

	//移动
	virtual void upMove(GameMap& gameMap) = 0;
	virtual void downMove(GameMap& gameMap) = 0;
	virtual void leftMove(GameMap& gameMap) = 0;
	virtual void rightMove(GameMap& gameMap) = 0;

	//攻击
	virtual void attack(Role&) = 0;

	//死亡
	virtual void death(GameMap& gameMap) = 0;

	//绑定的对象是否存在
	bool isExist()const;
protected:
	AutoWeakRole _mySelf;
};


//玩家行为
class PlayerBehavior :public Behavior {
	using Behavior::Behavior;

	//移动
	virtual void upMove(GameMap& gameMap)override;
	virtual void downMove(GameMap& gameMap)override;
	virtual void leftMove(GameMap& gameMap)override;
	virtual void rightMove(GameMap& gameMap)override;

	//攻击
	virtual void attack(Role&)override;

	//死亡
	virtual void death(GameMap& gameMap)override;

};


//宝可梦行为
class PokemonBehavior :public Behavior {
	using Behavior::Behavior;

	//移动
	virtual void upMove(GameMap& gameMap)override;
	virtual void downMove(GameMap& gameMap)override;
	virtual void leftMove(GameMap& gameMap)override;
	virtual void rightMove(GameMap& gameMap)override;

	//攻击
	virtual void attack(Role&)override;

	//死亡
	virtual void death(GameMap& gameMap)override;
	
};
