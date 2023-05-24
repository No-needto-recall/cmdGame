#pragma once

#include <string>
#include <vector>
#include "PokemonSkill.h"

using std::string;

class PokemonSpecies;

using DataType = int;

class Pokemon {
public:
    // 构造函数，初始化宝可梦的属性
    Pokemon(const PokemonSpecies* species, DataType level);

    // 获取宝可梦的名称
    string GetName() const;

    // 获取宝可梦的等级
    DataType GetLevel() const;

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

    // 获取宝可梦的生命值、攻击力、防御力等属性值
    DataType GetCurrentHP() const;
    DataType GetCurrentAttack() const;
    DataType GetCurrentDefense() const;
    DataType GetCurrentSpecialAttack() const;
    DataType GetCurrentSpecialDefense() const;
    DataType GetCurrentSpeed() const;

private:
    const PokemonSpecies* _species; // 宝可梦的种类
    DataType _level;                     // 宝可梦的等级
    DataType _individual;                // 宝可梦的个体值
    DataType _individual;                // 宝可梦的个体值

    // 宝可梦的各项属性值
    DataType _maxHP;                     // 宝可梦的最大生命值
    DataType _currentHP;                 // 宝可梦的当前生命值
    DataType _currentAttack;             // 宝可梦的当前攻击力
    DataType _currentDefense;            // 宝可梦的当前防御力
    DataType _currentSpecialAttack;      // 宝可梦的当前特殊攻击力
    DataType _currentSpecialDefense;     // 宝可梦的当前特殊防御力
    DataType _currentSpeed;              // 宝可梦的当前速度

    std::vector<PokemonSkill*> _skills; // 宝可梦的技能列表
};
