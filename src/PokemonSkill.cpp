#include "PokemonSkill.h"
#include "PokemonDataCalculation.h"
#include "Pokemon.h"
#include "Log.h"
#include "Config.h"

PokemonSkillType::PokemonSkillType(const string& name, SkillCategory category, int power, int accuracy, int priority, int maxPP)
	:_name(name)
	,_category(category)
	,_power(power)
	,_accuracy(accuracy)
	,_priority(priority)
	,_maxPP(maxPP)
{
}

string PokemonSkillType::GetName() const
{
	return _name;
}

SkillCategory PokemonSkillType::GetCategory() const
{
	return _category;
}

int PokemonSkillType::GetPower() const
{
	return _power;
}

int PokemonSkillType::GetAccuracy() const
{
	return _accuracy;
}

int PokemonSkillType::GetPriority() const
{
	return _priority;
}

int PokemonSkillType::GetMaxPP() const
{
	return _maxPP;
}

PokemonSkill::PokemonSkill(PokemonSkillType* type)
	:_type(type)
	,_currentPP(type->GetMaxPP())
{
}

const PokemonSkillType* PokemonSkill::GetType() const
{
	return _type;
}

void PokemonSkill::DecreasePP(int amount)
{
	if (amount > 0) {
		if (_currentPP - amount <= 0) {
			_currentPP = 0;
		}
		else {
			_currentPP -= amount;
		}
	}
}

void PokemonSkill::IncreasePP(int amount)
{
	if (amount > 0) {
		if (amount + _currentPP >= _type->GetMaxPP()) {
			_currentPP = _type->GetMaxPP();
		}
		else {
			_currentPP += amount;
		}
	}
}

void PokemonSkill::RestorePP()
{
	_currentPP = _type->GetMaxPP();
}

bool PokemonSkill::HasPP() const
{
	return _currentPP>0;
}

void PokemonPhysicalSkill::Use(Pokemon* user, Pokemon* target)
{
	DecreasePP(1);
	DataType val = CALCULATION.CalculatDamage(this, user, target);
	if (val >= 0) {
		target->TakeDamage(val);
	}
}

void PokemonSpecialSkill::Use(Pokemon* user, Pokemon* target)
{
	DecreasePP(1);
	DataType val = CALCULATION.CalculatDamage(this, user, target);
	if (val >= 0) {
		target->TakeDamage(val);
	}
}

void PokemonStatusSkill::Use(Pokemon* user, Pokemon* target)
{
}

PokemonSkillTypeFactory& PokemonSkillTypeFactory::getInstance()
{
	static PokemonSkillTypeFactory instance;
	return instance;
}

AutoSkill PokemonSkillTypeFactory::create(const string& name, SkillCategory category, int power, int accuracy, int priority, int maxPP)
{
	if (_types.count(name) == 0)
	{
		_types[name].reset(new PokemonSkillType(name, category, power, accuracy, priority, maxPP));
	}
	switch (category)
	{
	case PHYSICAL:
		return AutoSkill(new PokemonPhysicalSkill(_types[name].get()));
		break;
	case SPECIAL:
		return AutoSkill(new PokemonSpecialSkill(_types[name].get()));
		break;
	case STATUS:
		return AutoSkill(new PokemonStatusSkill(_types[name].get()));
		break;
	default:
		LOG_ERROR("不存在该类型的技能");
		return nullptr;
		break;
	}
}

AutoSkill PokemonSkillTypeFactory::createWithConfig(int index)
{
	auto& data = CONFIG_DATA.pokemonSkills[index];
	return create(
		data.name,
		static_cast<SkillCategory>(data.category),
		data.power,
		data.accuracy,
		data.priority,
		data.maxPP
	);
}

AutoSkill PokemonSkillTypeFactory::createWithName(string name)
{
	if (_types.count(name) == 0) {
		LOG_ERROR("不存在该技能:"+name);
		return nullptr;
	}
	else {
		switch (_types[name]->GetCategory())
		{
		case PHYSICAL:
			return AutoSkill(new PokemonPhysicalSkill(_types[name].get()));
			break;
		case SPECIAL:
			return AutoSkill(new PokemonSpecialSkill(_types[name].get()));
			break;
		case STATUS:
			return AutoSkill(new PokemonStatusSkill(_types[name].get()));
			break;
		default:
			LOG_ERROR("不存在该类型的技能");
			return nullptr;
			break;
		}
	}
}

PokemonSkillTypeFactory::PokemonSkillTypeFactory()
{
}
