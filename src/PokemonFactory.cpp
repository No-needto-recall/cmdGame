#include "PokemonFactory.h"
#include "PokemonSkill.h"
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

AutoPokemon PokemonFactory::createFromConf(int index)
{
	auto conf = CONFIG_DATA.pokemonSpecies[index];
	Skills skills;
	skills.reserve(4);
	for (auto& name : conf.learnableSkills) {
		skills.push_back(
			SKILL_FACTORY.createWithName(name)
		);
	}
	return create(
	conf.name,
	conf.baseHP,
	conf.baseAttack,
	conf.baseDefence,
	conf.baseSpecialAttack,
	conf.baseSpecialDefence,
	conf.baseSpeed,
	conf.HpPoint,
	conf.AttackPoint,
	conf.DefencePoint,
	conf.SpecialAttackPoint,
	conf.SpecialDefencePoint,
	conf.SpeedPoint,
	conf.basicEmpirical,
		skills
	);
}

PokemonFactory::PokemonFactory()
{
}
