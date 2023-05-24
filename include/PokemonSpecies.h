#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

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
    DataType GetBaseHP() const;
    DataType GetBaseAttack() const;
    DataType GetBaseDefense() const;
    DataType GetBaseSpecialAttack() const;
    DataType GetBaseSpecialDefense() const;
    DataType GetBaseSpeed() const;

    // 获取可以学习的技能
     const PokemonSkill* GetLearnableSkill(int index) const;

    // 其他可能的方法（例如获取进化信息）

private:
    // 宝可梦种类的各项属性值
    string _speciesName;                //种类名称
    DataType _baseHP;                   //基础生命值
    DataType _baseAttack;               //基础攻击力
    DataType _baseDefense;              //基础防御力
    DataType _baseSpecialAttack;        //基础特殊攻击力
    DataType _baseSpecialDefense;       //基础特殊防御力
    DataType _baseSpeed;                //基础速度
	DataType _basicEmpirical;           //基础经验值
    Skills  _learnableSkills;           //能学习的技能表
};

