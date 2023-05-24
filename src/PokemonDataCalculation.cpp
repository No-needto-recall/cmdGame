#include "PokemonDataCalculation.h"

PokemonDataCalculation& PokemonDataCalculation::getInstance()
{
	static PokemonDataCalculation instance;
	return instance;
}

PokemonDataCalculation::PokemonDataCalculation()
{
}
