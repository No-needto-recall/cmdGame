#pragma once

#include "Pokemon.h"
#include "PokemonSkill.h"

enum PokemonDataType :int
{
	HP =0,
	ATTACK ,
	DEFENSE,
	SPECIAL_ATTACK,
	SPECIAL_DEFENSE,
	SPEED
};

//宝可梦数值计算器
class PokemonDataCalculation {
public:
	//获取instance
	static PokemonDataCalculation& getInstance();
	//根据宝可梦，计算能力值
	//HP:(种族值*2+个体值+基础点数/4）*等级/100+5
	//Other:(种族值*2+个体值+基础点数/4）*等级/100+10+等级
	DataType CalculatPokemonData(Pokemon* pokemon,PokemonDataType type);
	DataType CalculatDamage(PokemonSkill* skill, Pokemon* from, Pokemon* to);
private:
	PokemonDataCalculation();
	PokemonDataCalculation(const PokemonDataCalculation&) = delete;
	void operator = (const PokemonDataCalculation&) = delete;
	static DataType _defaultData;
};


#define CALCULATION PokemonDataCalculation::getInstance()

