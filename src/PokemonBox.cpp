#include "PokemonBox.h"

PokemonBox::PokemonBox() : _nextId(0) {} // 初始化时设置下一个宝可梦的ID为0

PokemonBox::~PokemonBox() {}

bool PokemonBox::AddPokemon(AutoPokemon pokemon) {
    if (_idToPokemonMap.size() >= 1000) { // 如果存储器已满，返回false
        return false;
    }

    // 添加宝可梦到_idToPokemonMap，并设置其ID
    _idToPokemonMap[_nextId] = pokemon;

    // 在_nameToIdsMap中添加新的宝可梦
    _nameToIdsMap.insert({ pokemon->GetName(), _nextId });

    //设置宝可梦的唯一id
    pokemon->SetID(_nextId);

    // 更新下一个宝可梦的ID
    ++_nextId;

    return true;
}

bool PokemonBox::DeletePokemon(int id) {
    // 查找ID对应的宝可梦
    auto it = _idToPokemonMap.find(id);
    if (it == _idToPokemonMap.end()) { // 如果找不到，返回false
        return false;
    }

    // 从_nameToIdsMap中删除对应的宝可梦
    auto range = _nameToIdsMap.equal_range(it->second->GetName());
    for (auto i = range.first; i != range.second; ++i) {
        if (i->second == id) {
            _nameToIdsMap.erase(i);
            break;
        }
    }

    // 从_idToPokemonMap中删除宝可梦
    _idToPokemonMap.erase(it);

    // 从_battlePokemonIds中删除宝可梦
    for (auto i = _battlePokemonIds.begin(); i != _battlePokemonIds.end(); ++i) {
        if (*i == id) {
            _battlePokemonIds.erase(i);
            break;
        }
    }

    return true;
}

AutoPokemon PokemonBox::GetPokemonById(int id) const {
    // 查找ID对应的宝可梦
    auto it = _idToPokemonMap.find(id);
    if (it == _idToPokemonMap.end()) { // 如果找不到，返回nullptr
        return nullptr;
    }
    return it->second;
}

unordered_set<int> PokemonBox::GetPokemonIdsByName(const string& name) const {
    unordered_set<int> ids;
    auto range = _nameToIdsMap.equal_range(name);
    for (auto i = range.first; i != range.second; ++i) {
        ids.insert(i->second);
    }
    return ids;
}

bool PokemonBox::AddBattlePokemon(int id) {
    if (_battlePokemonIds.size() >= 6) { // 如果参战队列已满，返回false
        return false;
    }
    _battlePokemonIds.push_back(id);
    return true;
}

bool PokemonBox::RemoveBattlePokemon(int id) {
    for (auto i = _battlePokemonIds.begin(); i != _battlePokemonIds.end(); ++i) {
        if (*i == id) {
            _battlePokemonIds.erase(i);
            return true;
        }
    }
    return false;
}

bool PokemonBox::CanAddBattlePokemon() const {
    return _battlePokemonIds.size() < MAX_BATTLE_NUM;
}

vector<int> PokemonBox::GetBattlePokemonIds() const {
    return _battlePokemonIds;
}

bool PokemonBox::IsFull() const {
    return _idToPokemonMap.size() >= 1000;
}

bool PokemonBox::IsEmpty() const {
    return _idToPokemonMap.empty();
}

int PokemonBox::GetPokemonCount() const {
    return static_cast<int>(_idToPokemonMap.size());
}

unordered_map<int, AutoPokemon> PokemonBox::GetAllPokemons() const {
    return _idToPokemonMap;
}
