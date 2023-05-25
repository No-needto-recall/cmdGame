#include "Pokemon.h"
#include "PokemonSpecies.h"




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
