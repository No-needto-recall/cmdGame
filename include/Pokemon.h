#pragma once

#include <string>
#include <vector>
#include <memory>
#include "PokemonDatas.h"

using std::string;
using std::shared_ptr;
using std::vector;

class PokemonSpecies;
class PokemonSkill;

using AutoSkill = shared_ptr<PokemonSkill>;
using Skills = vector<AutoSkill>;

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

    // 宝可梦添加新的技能
    bool AddSkill(AutoSkill  newSkill);
    // 宝可梦删除持有的技能
    bool Delete(int index);

    //宝可梦替换新的技能
    bool ReplaceSkill(int index, AutoSkill newSkill);

    // 检查宝可梦是否可以战斗
    bool CanBattle() const;

    // 刷新宝可梦的能力值
    void RefreshCapability();

    //获取宝可梦的种类信息
    const PokemonSpecies* GetSpecies() const;
    //获取宝可梦种类的基础信息
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
    string _name;                            //宝可梦的名字

    const PokemonSpecies* _species;      // 宝可梦的种类
    const PokemonDatas _individual;      // 宝可梦的个体值
    PokemonDatas _currentData;           //宝可梦的当前能力值
    PokemonDatas _basePoint;             //宝可梦的基础点数
    // 宝可梦的属性值
    DataType _level;                     // 等级
    DataType _currentEmpirical;          // 当前经验值
    DataType _maxEmpirical;              // 升级所需经验值
    DataType _maxHp;                     // 最大生命值

    Skills _skills;                 // 宝可梦的技能列表
};
