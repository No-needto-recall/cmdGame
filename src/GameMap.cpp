#include "GameMap.h"
#include "Log.h"
#include "Role.h"
#include "Config.h"
#include "ScreenDrawer.h"
#include "Behavior.h"

GameMap::GameMap(int maxRows,int maxColumns)
	:_maxRows(maxRows),_maxColumns(maxColumns)
{
}

GameMap::~GameMap() {

}

int GameMap::getMaxRows()const {
	return _maxRows;
}

int GameMap::getMaxColumns()const {
	return _maxColumns;
}

void GameMap::initMap() {
	LOG_INFO("初始化地图 "+to_string(_maxColumns)+" x "+ to_string(_maxRows));
	_mapData.resize(_maxRows);
	for (auto& rv : _mapData) {
		rv.resize(_maxColumns,DEFAULT_MAP);
	}
	LOG_INFO("初始化完成");
}


void GameMap::display() {
	for (int y = 0; y < _maxRows; ++y) {
		for (int x = 0; x < _maxColumns; ++x) {
			ScreenDrawer::getInstance().drawCharacter(
				x, y, _mapData[y][x]
			);
		}
	}
}

bool GameMap::isInMap(const Location & location)const {
	return location._x >= 0 && location._x < _maxColumns &&
		location._y >= 0 && location._y < _maxRows;
}


bool GameMap::isRole(const Location & location){
	return _mapRoles.count(location.toString()) > 0;
}

AutoRole& GameMap::getRole(const Location & location) {
	auto search = _mapRoles.find(location.toString());
	if (search != _mapRoles.end()) {
		return search->second;
	}
	else {
		LOG_ERROR("获取了错误的对象");
		exit(1);
	}
}


void GameMap::addRole(AutoRole& role ) {
	Location tmpLocation= role->getLocation();
	if (isRole(tmpLocation)) {
		LOG_ERROR(tmpLocation.toString() + "已有对象");
	}
	else {
		if (!isInMap(tmpLocation)) {
			LOG_ERROR(tmpLocation.toString() + "超出地图");
		}
		else {
			_mapRoles.insert({
				tmpLocation.toString()
				,role});
			//添加图标
			char icon = role->getAttribute()._icon;
			_mapData[tmpLocation._y][tmpLocation._x]=icon;

			LOG_INFO("添加:" + role->getAttribute()._name + "到: " +
				tmpLocation.toString()
			);
		}
	}
}


void GameMap::deleteRole(Role& role) {
	//依赖倒置
	LOG_INFO(role.getAttribute()._name + "将被删除");
	_mapData[role.getLocation()._y][role.getLocation()._x] = DEFAULT_MAP;
	_mapRoles.erase(role.getLocation().toString());
}


void GameMap::moveRole(Role& role, const Location& newLocation) {
	if (isInMap(newLocation)) {
		if (isRole(newLocation))
		{
			roleCollide(role, *getRole(newLocation));
		}
		LOG_INFO(role.getAttribute()._name + " 从 " + 
				role.getLocation().toString() + " 到 "+
				newLocation.toString());
		_mapData[role.getLocation()._y][role.getLocation()._x] = DEFAULT_MAP;
		role.getLocation() = newLocation;
		_mapData[role.getLocation()._y][role.getLocation()._x] = role.getAttribute()._icon;
	}
}




int GameMap::randomNum(int a, int b) {
	::srand(std::random_device()());
	return a + ::rand() % (b - a + 1);
}


void GameMap::randomCreatRole() {
	LOG_INFO("将在随机位置生成怪物");
	int tmpX = randomNum(0, _maxColumns - 1);
	int tmpY = randomNum(0, _maxRows - 1);
	while (1) {
		auto search = _mapRoles.find(Location{ tmpX,tmpY }.toString());
		if (search != _mapRoles.end()) {
			tmpX = randomNum(0, _maxColumns - 1);
			tmpY = randomNum(0, _maxRows - 1);
		}
		else {
			break;
		}
	}
	Location tmpLocation = { tmpX,tmpY };

	Attribute tmpAttribute = {
		Config::instance().getConfigData().role.pokemon.name,
		Config::instance().getConfigData().role.pokemon.health,
		Config::instance().getConfigData().role.pokemon.mana,
		Config::instance().getConfigData().role.pokemon.attack,
		Config::instance().getConfigData().role.pokemon.defense,
		Config::instance().getConfigData().role.pokemon.icon
	};
	AutoRole tmpPokemon(new PokemonRole(tmpAttribute, tmpLocation,*this));
	std::unique_ptr<PokemonBehavior> tmpPokemonBehavior(
		new PokemonBehavior(*tmpPokemon)
	);
	//设定行为
	tmpPokemon->setBehavior(std::move(tmpPokemonBehavior));
	this->addRole(tmpPokemon);
	LOG_INFO("生成怪物完成");
}

void GameMap::roleCollide(Role& lhs, Role& rhs)
{
	lhs.collide(rhs);
}


