#pragma once
#include <string>

//前置声明
class Pokemon;
// 技能分类
enum SkillCategory { PHYSICAL, SPECIAL, STATUS };

// 技能类型对象，用于表示技能的通用属性
class PokemonSkillType {
public:
    // 构造函数，初始化技能的属性
    PokemonSkillType(const std::string& name, const std::string& type, SkillCategory category,
        int power, int accuracy, int priority);

    // 获取技能的名称
    std::string GetName() const;

    // 获取技能的类型
    std::string GetType() const;

    // 获取技能的分类
    SkillCategory GetCategory() const;

    // 获取技能的威力
    int GetPower() const;

    // 获取技能的命中率
    int GetAccuracy() const;

    // 获取技能的优先度
    int GetPriority() const;

    // 其他可能的方法，例如设定/获取附加效果

private:
    std::string _name;       // 技能的名称
    std::string _type;       // 技能的类型
    SkillCategory _category; // 技能的分类
    int _power;              // 技能的威力
    int _accuracy;           // 技能的命中率
    int _priority;           // 技能的优先度

    // 附加效果
};

// 具体技能实例，用于表示具体的技能
class PokemonSkill {
public:
    // 构造函数，初始化技能实例
    PokemonSkill(PokemonSkillType* type, int pp);

    // 使用技能，这是一个虚函数，派生类可以覆写它
    virtual void Use(Pokemon* user, Pokemon* target) = 0;

    // 获取技能的类型
    PokemonSkillType* GetType() const;

    // 降低技能的PP值
    void DecreasePP(int amount);

    // 增加技能的PP值
    void IncreasePP(int amount);

    // 完全恢复技能的PP值
    void RestorePP();

    // 检查技能是否还有剩余的PP
    bool HasPP() const;

private:
    PokemonSkillType* _type; // 技能的类型
    int _currentPP;          // 技能当前的PP值
};

//物理类技能
class PokemonPhysicalSkill :public PokemonSkill {
public:
    using PokemonSkill::PokemonSkill;
    virtual void Use(Pokemon* user, Pokemon* target) override;
};

//特殊类技能
class PokemonSpecialSkill :public PokemonSkill {
public:
    using PokemonSkill::PokemonSkill;
    virtual void Use(Pokemon* user, Pokemon* target) override;
};

//状态类技能
class PokemonStatusSkill :public PokemonSkill {
public:
    using PokemonSkill::PokemonSkill;
    virtual void Use(Pokemon* user, Pokemon* target) override;
};
