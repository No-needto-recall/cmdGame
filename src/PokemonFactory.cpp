#include "PokemonFactory.h"
#include "Log.h"
#include "Config.h"

PokemonFactory& PokemonFactory::getInstance()
{
	static PokemonFactory instance;
	return instance;
}

AutoPokemon PokemonFactory::create(const string& speciesName, const DataType& baseHP, const DataType& baseAttack, const DataType& baseDefence, const DataType& baseSpecialAttack, const DataType& baseSpecialDefence, const DataType& baseSpeed, const DataType& HpPoint, const DataType& AttackPoint, const DataType& DefencePoint, const DataType& SpecialAttackPoint, const DataType& SpecialDefencePoint, const DataType& SpeedPoint, const DataType& basicEmpirical, const Skills& learnableSkills)
{
	if (_species.count(speciesName) == 0) {
		_species[speciesName].reset(new PokemonSpecies(
			speciesName,
			{
				baseHP,
				baseAttack,
				baseDefence,
				baseSpecialAttack,
				baseSpecialDefence,
				baseSpeed
			},
			{
				HpPoint,
				AttackPoint,
				DefencePoint,
				SpecialAttackPoint,
				SpecialDefencePoint,
				SpeedPoint
			},
			basicEmpirical,
			learnableSkills
		));
	}
	return AutoPokemon(new Pokemon(_species[speciesName].get(), 1));
}

AutoPokemon PokemonFactory::createFromConf()
{
	return AutoPokemon();
}

PokemonFactory::PokemonFactory()
{
}
