#include "PokemonDataCalculation.h"



//静态数据成员初始化
DataType PokemonDataCalculation::_defaultData = 1;

PokemonDataCalculation& PokemonDataCalculation::getInstance()
{
	static PokemonDataCalculation instance;
	return instance;
}


DataType PokemonDataCalculation::CalculatPokemonData(Pokemon* pokemon, PokemonDataType type)
{
	DataType fromSpecies = _defaultData;
	DataType fromPokemon = _defaultData;
	DataType fromPokemonBasePoint = _defaultData;
	DataType pokemonLevel = pokemon->GetLevel();
	switch (type)
	{
	case HP:
		fromSpecies = pokemon->GetBasicData().HP;
		fromPokemon = pokemon->GetCurrentData().HP;
		fromPokemonBasePoint = pokemon->GetBasePoint().HP;
		break;
	case ATTACK:
		fromSpecies = pokemon->GetBasicData().Attack;
		fromPokemon = pokemon->GetCurrentData().Attack;
		fromPokemonBasePoint = pokemon->GetBasePoint().Attack;
		break;
	case DEFENSE:
		fromSpecies = pokemon->GetBasicData().Defense;
		fromPokemon = pokemon->GetCurrentData().Defense;
		fromPokemonBasePoint = pokemon->GetBasePoint().Defense;
		break;
	case SPECIAL_ATTACK:
		fromSpecies = pokemon->GetBasicData().SpecialAttack;
		fromPokemon = pokemon->GetCurrentData().SpecialAttack;
		fromPokemonBasePoint = pokemon->GetBasePoint().SpecialAttack;
		break;
	case SPECIAL_DEFENSE:
		fromSpecies = pokemon->GetBasicData().SpecialDefense;
		fromPokemon = pokemon->GetCurrentData().SpecialDefense;
		fromPokemonBasePoint = pokemon->GetBasePoint().SpecialDefense;
		break;
	case SPEED:
		fromSpecies = pokemon->GetBasicData().Speed;
		fromPokemon = pokemon->GetCurrentData().Speed;
		fromPokemonBasePoint = pokemon->GetBasePoint().Speed;
		break;
	default:
		break;
	}
	if (type == PokemonDataType::HP) {
		return DataType(
			(((fromSpecies * 2) + fromPokemon + (fromPokemonBasePoint / 4)) * pokemonLevel) / 100
			+ 10 + pokemonLevel
		);
	}
	else {
		//没有添加性格修正
		return DataType(
			(((fromSpecies * 2) + fromPokemon + (fromPokemonBasePoint / 4)) * pokemonLevel) / 100
			+5
		);
	}

}

DataType PokemonDataCalculation::CalculatDamage(PokemonSkill* skill, Pokemon* from, Pokemon* to)
{
	DataType fromAttack = _defaultData;
	DataType toDefense= _defaultData;
	switch (skill->GetType()->GetCategory())
	{
	case PHYSICAL:
		fromAttack = from->GetCurrentData().Attack;
		toDefense = from->GetCurrentData().Defense;
		break;
	case SPECIAL:
		fromAttack = from->GetCurrentData().SpecialAttack;
		toDefense = from->GetCurrentData().SpecialDefense;
		break;
	case STATUS:
		break;
	default:
		break;
	}
	DataType fromLevel= from->GetLevel();
	DataType fromPower= skill->GetType()->GetPower();
	return (2 * fromLevel + 10) / 250 * fromAttack / toDefense * fromPower + 2;
}

DataType PokemonDataCalculation::CalculatEmpiricalMax(DataType level)
{
	DataType empirical = _defaultData;
	switch (level)
	{
	case 1:
		empirical = 6;
		break;
	case 2:
		empirical = 21;
		break;
	case 3:
		empirical = 51;
		break;
	case 4:
		empirical = 100;
		break;
	case 5:
		empirical = 172;
		break;
	case 6:
		empirical = 274;
		break;
	case 7:
		empirical = 409;
		break;
	case 8:
		empirical = 583;
		break;
	case 9:
		empirical = 800;
		break;
	case 10:
		empirical = 1064;
		break;
	default:
		break;
	}
	return empirical;
}

PokemonDataCalculation::PokemonDataCalculation()
{
}
