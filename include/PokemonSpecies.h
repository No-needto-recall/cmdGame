#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

class Skill;

using Skills = vector<Skill>;

class PokemonSpecies {
public:
    PokemonSpecies(const string& speciesName, const int& baseHP, const int& baseAttack, const int& baseDefense,
        const int& baseSpecialAttack, const int& baseSpecialDefense, const int& baseSpeed);

    // 获取种类名称
    string GetSpeciesName() const;

    // 获取基础属性值
    int GetBaseHP() const;
    int GetBaseAttack() const;
    int GetBaseDefense() const;
    int GetBaseSpecialAttack() const;
    int GetBaseSpecialDefense() const;
    int GetBaseSpeed() const;

    // 获取可以学习的技能
     const Skill* GetLearnableSkill(int index) const;

    // 其他可能的方法（例如获取进化信息）

private:
    std::string _speciesName;
    int _baseHP;
    int _baseAttack;
    int _baseDefense;
    int _baseSpecialAttack;
    int _baseSpecialDefense;
    int _baseSpeed;
    Skills  _learnableSkills;
};

