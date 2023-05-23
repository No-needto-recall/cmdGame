#pragma once

#include <string>
#include <vector>
#include "PokemonSkill.h"

class PokemonSpecies;

class Pokemon {
public:
    // 构造函数，初始化宝可梦的属性
    Pokemon(const PokemonSpecies* species, int level);

    // 获取宝可梦的名称
    std::string GetName() const;

    // 获取宝可梦的等级
    int GetLevel() const;

    // 宝可梦升级
    void LevelUp();

    // 宝可梦是否被击败
    bool IsDefeated() const;

    // 宝可梦受到伤害
    void TakeDamage(int amount);

    // 宝可梦恢复生命值
    void RecoverHP(int amount);

    // 宝可梦使用技能
    void UseSkill(int index, Pokemon* target);

    // 宝可梦学习新的技能
    bool LearnSkill(PokemonSkill* newSkill);

    // 检查宝可梦是否可以战斗
    bool CanBattle() const;

    // 战斗结束，恢复战前的属性值
    void EndBattle();

    // 获取宝可梦的生命值、攻击力、防御力等属性值
    int GetCurrentHP() const;
    int GetCurrentAttack() const;
    int GetCurrentDefense() const;
    int GetCurrentSpecialAttack() const;
    int GetCurrentSpecialDefense() const;
    int GetCurrentSpeed() const;

private:
    const PokemonSpecies* _species; // 宝可梦的种类
    int _level;                     // 宝可梦的等级

    // 宝可梦的各项属性值
    int _maxHP;                     // 宝可梦的最大生命值
    int _currentHP;                 // 宝可梦的当前生命值
    int _baseAttack;                // 宝可梦的基础攻击力
    int _currentAttack;             // 宝可梦的当前攻击力
    int _baseDefense;               // 宝可梦的基础防御力
    int _currentDefense;            // 宝可梦的当前防御力
    int _baseSpecialAttack;         // 宝可梦的基础特殊攻击力
    int _currentSpecialAttack;      // 宝可梦的当前特殊攻击力
    int _baseSpecialDefense;        // 宝可梦的基础特殊防御力
    int _currentSpecialDefense;     // 宝可梦的当前特殊防御力
    int _baseSpeed;                 // 宝可梦的基础速度
    int _currentSpeed;              // 宝可梦的当前速度

    std::vector<PokemonSkill*> _skills; // 宝可梦的技能列表
};
