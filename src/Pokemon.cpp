#include "Pokemon.h"
#include "PokemonSpecies.h"
#include "PokemonSkill.h"
#include "PokemonDataCalculation.h"
#include "Log.h"





bool Pokemon::CanBattle() const
{
	return _currentData.HP>0;
}

void Pokemon::RefreshCapability()
{
	_currentData.Attack = CALCULATION.CalculatPokemonData(this, ATTACK);
	_currentData.Defense= CALCULATION.CalculatPokemonData(this, DEFENSE);
	_currentData.SpecialAttack= CALCULATION.CalculatPokemonData(this, SPECIAL_ATTACK);
	_currentData.SpecialDefense= CALCULATION.CalculatPokemonData(this, SPECIAL_DEFENSE);
	_currentData.Speed= CALCULATION.CalculatPokemonData(this, SPEED);
}

const PokemonSpecies* Pokemon::GetSpecies() const
{
	return _species;
}

const PokemonDatas& Pokemon::GetBasicData() const
{
	return _species->GetBasicData();
}

const PokemonDatas& Pokemon::GetCurrentData() const
{
	return _currentData;
}

const PokemonDatas& Pokemon::GetBasePoint() const
{
	return _basePoint;
}

DataType Pokemon::GetLevel() const
{
	return _level;
}

const DataType& Pokemon::GetMaxHp() const
{
	return _maxHp;
}

string Pokemon::GetName() const
{
	return _name;
}

void Pokemon::LevelUp()
{
	++_level;
	RefreshCapability();
}

bool Pokemon::IsDefeated() const
{
	return _currentData.HP <=0 ;
}

void Pokemon::TakeDamage(DataType amount)
{
	if (amount > 0) {
		if (amount >= _currentData.HP)
		{
			_currentData.HP = 0;
		}
		else {
			_currentData.HP -= amount;
		}
	}
}

void Pokemon::RecoverHP(DataType amount)
{
	if (amount > 0) {
		if (amount + _currentData.HP >= _maxHp) {
			_currentData.HP = _maxHp;
		}
		else {
			_currentData.HP += amount;
		}
	}
}

void Pokemon::UseSkill(int index, Pokemon* target)
{
	_skills.at(index)->Use(this, target);
}

bool Pokemon::AddSkill(AutoSkill newSkill)
{
	if (_skills.size() == 4) {
		return false;
	}
	else {
		_skills.push_back(newSkill);
		return true;
	}
}

bool Pokemon::Delete(int index)
{
	if (index<0 || index >= _skills.size()) {
		LOG_ERROR("尝试删除非法索引的技能");
		return false;
	}
	else {
		_skills.erase(_skills.begin()+index);
		return true;
	}
}

bool Pokemon::ReplaceSkill(int index, AutoSkill newSkill)
{
	if (index<0 || index >= _skills.size()) {
		LOG_ERROR("尝试替换非法索引的技能");
		return false;
	}
	else {
		_skills[index] = newSkill;
		return true;
	}
}

