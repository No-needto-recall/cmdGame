#pragma once

#include <string>
#include <vector>
#include "PokemonDatas.h"

using std::string;
using std::vector;

//前置声明
class PokemonSkill;

using Skills = vector<PokemonSkill*>;
using DataType = int;



class PokemonSpecies {
public:
    PokemonSpecies(const string& speciesName, const DataType& baseHP, 
                   const DataType& baseAttack, const DataType& baseDefense,
				   const DataType& baseSpecialAttack, const DataType& baseSpecialDefense, 
				   const DataType& baseSpeed);

    // 获取种类名称
    string GetSpeciesName() const;

    // 获取基础属性值
    const PokemonDatas& GetBasicData()const;

    // 获取基础经验值
    DataType GetBasicEmpirical()const;

    // 获取可以学习的技能
     const PokemonSkill* GetLearnableSkill(int index) const;

    // 其他可能的方法（例如获取进化信息）

private:
    // 宝可梦种类的各项属性值
    PokemonDatas _basicData;            //基础属性
    string _speciesName;                //种类名称
	DataType _basicEmpirical;           //基础经验值
    Skills  _learnableSkills;           //能学习的技能表
};

