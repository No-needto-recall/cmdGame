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

PokemonDataCalculation::PokemonDataCalculation()
{
}
