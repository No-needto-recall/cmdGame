#pragma once

class Role;
class GameMap;
class PlayerBehavior;
class PokemonBehavior;

//行为类
class Behavior {
public:
	virtual ~Behavior() = default;

	//移动
	virtual void upMove(GameMap& gameMap) = 0;
	virtual void downMove(GameMap& gameMap) = 0;
	virtual void leftMove(GameMap& gameMap) = 0;
	virtual void rightMove(GameMap& gameMap) = 0;

	//攻击
	virtual void attack(Role&) = 0;

	//死亡
	virtual void death() = 0;
	virtual void death(GameMap& gameMap) = 0;


	//碰撞
	//双分派设计模式
	virtual void collide(Behavior& )=0;
	virtual void collideWithPlayer(PlayerBehavior&) = 0;
	virtual void collideWithPokemon(PokemonBehavior&) = 0;
};


//玩家行为
class PlayerBehavior :public Behavior {

	//移动
	virtual void upMove(GameMap& gameMap)override;
	virtual void downMove(GameMap& gameMap)override;
	virtual void leftMove(GameMap& gameMap)override;
	virtual void rightMove(GameMap& gameMap)override;

	//攻击
	virtual void attack(Role&)override;

	//死亡
	virtual void death(GameMap& gameMap)override;


	//碰撞
	virtual void collide(Behavior&)override;
	virtual void collideWithPlayer(PlayerBehavior&)override;
	virtual void collideWithPokemon(PokemonBehavior&)override;
};


//宝可梦行为
class PokemonBehavior :public Behavior {
	//移动
	virtual void upMove(GameMap& gameMap)override;
	virtual void downMove(GameMap& gameMap)override;
	virtual void leftMove(GameMap& gameMap)override;
	virtual void rightMove(GameMap& gameMap)override;

	//攻击
	virtual void attack(Role&)override;

	//死亡
	virtual void death(GameMap& gameMap)override;

	
	//碰撞
	virtual void collide(Behavior&)override;
	virtual void collideWithPlayer(PlayerBehavior&)override;
	virtual void collideWithPokemon(PokemonBehavior&)override;

};
