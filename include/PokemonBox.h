#pragma once

#include <unordered_map>
#include <unordered_set>
#include <string>
#include <vector>
#include <memory>
#include "Pokemon.h"

using std::string;
using std::unordered_map;
using std::unordered_multimap;
using std::unordered_set;
using std::vector;
using std::shared_ptr;

//注释
//测试
using AutoPokemon = shared_ptr<Pokemon>;

class PokemonBox {
public:
    PokemonBox();
    ~PokemonBox();

    //添加宝可梦到存储器
    bool AddPokemon(AutoPokemon pokemon);

    //从存储器中删除宝可梦
    bool DeletePokemon(int id);

    //通过ID获取宝可梦
    AutoPokemon GetPokemonById(int id) const;

    //通过名称获取宝可梦的ID列表
    unordered_set<int> GetPokemonIdsByName(const string& name) const;

    // 添加参战宝可梦
    bool AddBattlePokemon(int id);

    // 从参战队列中删除宝可梦
    bool RemoveBattlePokemon(int id);

    // 检查是否可以添加更多的参战宝可梦
    bool CanAddBattlePokemon() const;

    // 获取当前参战的宝可梦id集合
    vector<int> GetBattlePokemonIds() const;

    // 检查存储器是否已满
    bool IsFull() const;

    // 检查存储器是否为空
    bool IsEmpty() const;

    // 获取存储器中的宝可梦数量
    int GetPokemonCount() const;

    // 获取所有宝可梦的信息
    unordered_map<int, AutoPokemon> GetAllPokemons() const;

private:
    unordered_map<int, AutoPokemon> _idToPokemonMap;    //ID到宝可梦的映射
    unordered_multimap<string, int> _nameToIdsMap;              //名称到ID的映射
    vector<int> _battlePokemonIds;                //当前参战的宝可梦队列
    int _nextId;    //下一个宝可梦的ID
};



#define MAX_BATTLE_NUM 6

