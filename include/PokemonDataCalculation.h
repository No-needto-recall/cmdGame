#pragma once


//宝可梦数值计算器
class PokemonDataCalculation {
public:
	//获取instance
	static PokemonDataCalculation& getInstance();
	//根据宝可梦，计算它的当前攻击力
	
private:
	PokemonDataCalculation();
	PokemonDataCalculation(const PokemonDataCalculation&) = delete;
	void operator = (const PokemonDataCalculation&) = delete;
};

