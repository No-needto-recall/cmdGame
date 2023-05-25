#pragma once

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include "PokemonDatas.h"

using std::string;
using std::vector;
using std::shared_ptr;
using std::unique_ptr;
using std::unordered_map;

//前置声明
class PokemonSkill;
class PokemonSpecies;

using AutoSkill = shared_ptr<PokemonSkill>;
using Skills = vector<AutoSkill>;

using AutoSpecies = unique_ptr<PokemonSpecies>;


class PokemonSpecies {
public:
    PokemonSpecies(const string& speciesName, 
                   const PokemonDatas & basicData, 
                   const PokemonDatas & basicPoint, 
                   const DataType& basicEmpirical,
                   const Skills & learnableSkils 
				   );

    // 获取种类名称
    string GetSpeciesName() const;

    // 获取基础属性值
    const PokemonDatas& GetBasicData()const;
    // 获取基础点数值
    const PokemonDatas& GetBasePointData()const;

    // 获取基础经验值
    DataType GetBasicEmpirical()const;

    // 获取可以学习的技能
     AutoSkill GetLearnableSkill(int index) const;

    // 其他可能的方法（例如获取进化信息）

private:
    // 宝可梦种类的各项属性值
    const string _speciesName;                //种类名称
    const PokemonDatas _basicData;            //基础属性
    const PokemonDatas _basePoint;             //基础点数
	const DataType _basicEmpirical;           //基础经验值
    Skills  _learnableSkills;           //能学习的技能表
};


