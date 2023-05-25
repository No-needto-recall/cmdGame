#pragma once

#include <string>
#include <vector>
#include "PokemonSkill.h"

using std::string;

class PokemonSpecies;

using DataType = int;

struct PokemonDatas
{
    DataType HP;                 // 宝可梦的生命值
    DataType Attack;             // 宝可梦的攻击力
    DataType Defense;            // 宝可梦的防御力
    DataType SpecialAttack;      // 宝可梦的特殊攻击力
    DataType SpecialDefense;     // 宝可梦的特殊防御力
    DataType Speed;              // 宝可梦的速度
};


class Pokemon {
public:
    // 构造函数，初始化宝可梦的属性
    Pokemon(const PokemonSpecies* species, DataType level);

    // 获取宝可梦的名称
    string GetName() const;

    // 宝可梦升级
    void LevelUp();

    // 宝可梦是否被击败
    bool IsDefeated() const;

    // 宝可梦受到伤害
    void TakeDamage(DataType amount);

    // 宝可梦恢复生命值
    void RecoverHP(DataType amount);

    // 宝可梦使用技能
    void UseSkill(int index, Pokemon* target);

    // 宝可梦学习新的技能
    bool LearnSkill(PokemonSkill* newSkill);

    // 检查宝可梦是否可以战斗
    bool CanBattle() const;

    // 战斗结束，恢复战前的属性值
    void EndBattle();

    //获取宝可梦的种类信息
    const PokemonSpecies* GetSpecies() const;
    const PokemonDatas& GetBasicData()const;

    //获取宝可梦当前属性
    const PokemonDatas& GetCurrentData()const;
    //获取宝可梦的基础点数
    const PokemonDatas& GetBasePoint()const;

    // 获取宝可梦的等级
    DataType GetLevel() const;
    // 获取宝可梦的最大生命值
    const DataType& GetMaxHp()const;

private:
    const PokemonSpecies* _species; // 宝可梦的种类
    PokemonDatas _individual;            // 宝可梦的个体值
    PokemonDatas _currentData;           //宝可梦的当前属性
    PokemonDatas _basePoint;             //宝可梦的基础点数
    // 宝可梦的属性值
    DataType _level;                     // 等级
    DataType _currentEmpirical;          // 当前经验值
    DataType _maxEmpirical;              // 升级所需经验值


    std::vector<PokemonSkill*> _skills; // 宝可梦的技能列表
};
