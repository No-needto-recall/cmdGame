#include "PokemonSpecies.h"
#include "Log.h"

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

AutoSkill PokemonSpecies::GetLearnableSkill(int index) const
{
	if (index < 0 || index >= _learnableSkills.size()) {
		LOG_ERROR("尝试从种类中使用非法下标");
		return nullptr;
	}
	else
	{
		return _learnableSkills[index];
	}
}