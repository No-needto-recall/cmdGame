#include "GameMap.h"
#include "Monster.h"

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

bool GameMap::isInMap(int x, int y)const {
	return x >= 0 && x < _maxColumns &&
		y >= 0 && y < _maxRows;
}


bool GameMap::isActor(int x, int y){

	auto search = _actors.find(to_string(x)+","+to_string(y));
	if (search != _actors.end()) {
		return true;
	}
	else {
		return false;
	}
}

AutoActor& GameMap::getActor(int x, int y) {
	auto search = _actors.find(to_string(x)+","+to_string(y));
	if (search != _actors.end()) {
		return search->second;
	}
	else {
		LOG_ERROR("获取了错误的对象");
		exit(1);
	}
}


void GameMap::addActor(AutoActor& Auto) {

	auto actor = Auto.get();
	int x = actor->getX();
	int y = actor->getY();

	if (isActor(x,y)) {
		LOG_ERROR(actor->getPosition() + "已有对象");
	}
	else {
		if (!isInMap(x,y)) {
			LOG_ERROR(actor->getPosition() + "超出地图");
		}
		else {
			_actors.insert({
				actor->getPosition()
				,Auto});
			
			_mapData[y][x]=typeTomap(actor->getType());
			actor->bindMap(this);
			LOG_INFO("添加:" + actor->getName() + "到: " +
				actor->getPosition()
			);
		}
	}
}



char GameMap::typeTomap(Type ty) {
	if (ty == Type::PLAYER) {
		return PLAYER_MAP;
	}
	else if (ty == Type::MONSTER) {
		return MONSTER_MAP;
	}
	else {
		return DEFAULT_MAP;
	}
}

void GameMap::fight(Actor& lhs, Actor& rhs) {
	LOG_INFO("发生战斗");
	ScreenDrawer::getInstance().drawString(_maxColumns+2,0,"strat fight");
	while (1) {
		lhs.AD_attack(rhs);
		if (rhs.isAlive()) {
			rhs.AD_attack(lhs);
			if (lhs.isAlive()) {
				continue;
			}
			else {
				deleteActor(&lhs);
				break;
			}
		}
		else {
			deleteActor(&rhs);
			break;
		}
	}
	LOG_INFO("战斗结束");
}

void GameMap::moveActor(Actor* actor, int newX, int newY) {
	if (isInMap(newX, newY)) {
		if (isActor(newX,newY))
		{
			fight(*actor, *getActor(newX,newY).get());
			//存在主角死亡的情况
		}
		LOG_INFO(actor->getName() + " 从 " + actor->getPosition() + "->" + positionToString(newX, newY));
		_mapData[actor->getY()][actor->getX()] = DEFAULT_MAP;
		actor->setX(newX);
		actor->setY(newY);
		_mapData[actor->getY()][actor->getX()] = typeTomap(actor->getType());
	}
}

void GameMap::deleteActor(Actor* actor) {
	LOG_INFO(actor->getName() + "死亡,将被删除");
	if (actor->getType() == Type::MONSTER) {
		ScreenDrawer::getInstance().drawString(0, _maxColumns, "The monster dies.\nMonster generation");
		randomMonster();
	}
	else if (actor->getType() == Type::PLAYER) {
		ScreenDrawer::getInstance().drawString(0, _maxColumns, "Player death.\n Game over.");
		//尚未处理玩家死亡
		_isQuit = false;
		return;
	}
	_mapData[actor->getY()][actor->getX()] = DEFAULT_MAP;
	_actors.erase(actor->getPosition());
}


int GameMap::randomNum(int a, int b) {
	::srand(std::random_device()());
	return a + ::rand() % (b - a + 1);
}

string GameMap::positionToString(int x, int y) {
	return to_string(x) + "," + to_string(y);
}

void GameMap::randomMonster() {
	LOG_INFO("将在随机位置生成怪物");
	int tmpX = randomNum(0, _maxColumns - 1);
	int tmpY = randomNum(0, _maxRows - 1);
	while (1) {
		auto search = _actors.find(positionToString(tmpX, tmpY));
		if (search != _actors.end()) {
			tmpX = randomNum(0, _maxColumns - 1);
			tmpY = randomNum(0, _maxRows - 1);
		}
		else {
			break;
		}
	}

	AutoActor mo1(new Monster(10, 2, 20, 2, tmpX, tmpY, Type::MONSTER, "怪物"));
	this->addActor(mo1);
	LOG_INFO("生成怪物完成");
}


bool GameMap::getQuit()const {
	return _isQuit;
}

void GameMap::setQuit(bool bl) {
	_isQuit = bl;
}
