#include "PokemonSpecies.h"

string PokemonSpecies::GetSpeciesName() const
{
	return _speciesName;
}

const PokemonDatas& PokemonSpecies::GetBasicData() const
{
	return _basicData;
}

DataType PokemonSpecies::GetBasicEmpirical() const
{
	return _basicEmpirical;
}
