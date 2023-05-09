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
			_mapData[tmpLocation._y][tmpLocation._x]=role->getBehavior()->icon();

			LOG_INFO("添加:" + role->getAttribute()._name + "到: " +
				tmpLocation.toString()
			);
		}
	}
}

#if 0 
void GameMap::fight(Role& lhs, Role& rhs) {
	LOG_INFO("发生战斗");

	while (1) {
		lhs.getBehavior()->attack(rhs);
		if (rhs.getAttribute().isAlive()) {
			rhs.getBehavior()->attack(lhs);
			if (lhs.getAttribute().isAlive()) {
				continue;
			}
			else {
				deleteRole(&lhs);
				break;
			}
		}
		else {
			deleteRole(&rhs);
			break;
		}
	}
	LOG_INFO("战斗结束");
}

#endif

void GameMap::deleteRole(Role& role) {
	LOG_INFO(role.getAttribute()._name + "死亡,将被删除");

	role.getBehavior()->death();

	_mapData[role.getLocation()._y][role.getLocation()._x] = DEFAULT_MAP;
	_mapRoles.erase(role.getLocation().toString());
}


void GameMap::moveRole(Role& role, const Location& newLocation) {
	if ((newLocation._x, newLocation._y)) {
		if (isRole(newLocation))
		{
			//fight(*role, *(newX,newY).get());
			//存在主角死亡的情况
			roleCollide(role, *getRole(newLocation));
		}
		LOG_INFO(role->getName() + " 从 " + role->getPosition() + "->" + locationToStringKey(newX, newY));
		_mapData[role->getY()][role->getX()] = DEFAULT_MAP;
		role->setX(newX);
		role->setY(newY);
		_mapData[role->getY()][role->getX()] = typeTomap(role->getType());
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
		auto search = _mapRoles.find(locationToStringKey(tmpX, tmpY));
		if (search != _mapRoles.end()) {
			tmpX = randomNum(0, _maxColumns - 1);
			tmpY = randomNum(0, _maxRows - 1);
		}
		else {
			break;
		}
	}

	Autorole mo1(new Monster(10, 2, 20, 2, tmpX, tmpY, Type::MONSTER, "怪物"));
	this->addRole(mo1);
	LOG_INFO("生成怪物完成");
}

void GameMap::roleCollide(Role& lhs, Role& rhs)
{
	lhs.getBehavior()->collide(rhs);
}


