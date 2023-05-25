#pragma once
#include "Pokemon.h"
#include "PokemonSpecies.h"

using AutoPokemon = shared_ptr<Pokemon>;

//创建宝可梦种族的单例简单工厂
class PokemonFactory {
public:
    //获取句柄
    static PokemonFactory& getInstance();
    //创建
    AutoPokemon create(const string& speciesName,const DataType& baseHP,
                       const DataType& baseAttack,const DataType& baseDefence,
                       const DataType& baseSpecialAttack,const DataType& baseSpecialDefence,
                       const DataType& baseSpeed,
                       const DataType& HpPoint,
                       const DataType& AttackPoint,const DataType& DefencePoint,
                       const DataType& SpecialAttackPoint,const DataType& SpecialDefencePoint,
                       const DataType& SpeedPoint,
                       const DataType& basicEmpirical,
                       const Skills& learnableSkills 
        );
    AutoPokemon createFromConf();
private:
    //类型对象，享元模式
    unordered_map<string, AutoSpecies> _species;

    //单例模式，构造私有，禁止赋值语句
    PokemonFactory(const PokemonFactory&) = delete;
    void operator = (const PokemonFactory&) = delete;
    PokemonFactory();
};

