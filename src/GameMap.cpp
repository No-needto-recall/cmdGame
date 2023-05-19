#include <memory>
#include "GameMap.h"
#include "Log.h"
#include "Config.h"
#include "ScreenDrawer.h"

GameMap::GameMap(const MapID& id, int rows, int cols,AutoMapInit init)
	:_id(id)
	,_rows(rows)
	,_cols(cols)
	,_initFunc(std::move(init))
{
	_grid.resize(_rows);
	for (auto& row : _grid) {
		row.resize(_cols);
	}
	LOG_INFO("创建地图:" + _id + "(" + to_string(_rows) + "*" + to_string(_cols) + ")");
	initMap();
}

void GameMap::initMap()
{
	_initFunc->initialize(*this);
}

const MapID& GameMap::GetID() const
{
	return _id;
}

int GameMap::GetRows() const
{
	return _rows;
}

int GameMap::GetCols() const
{
	return _cols;
}

bool GameMap::HasGameObject(const Location& location) const
{
	int x = location.x;
	int y = location.y;
	if (InGameMap(location)) {
		if (!(_grid[y][x].IsEmpty())) {
			return true;
		}
	}
	return false;
}

bool GameMap::InGameMap(const Location& location) const
{
	return location.x>=0 
		&& location.x<_cols 
		&& location.y>=0
		&& location.y<_rows;
}

AutoGameObject GameMap::GetGameObject(const Location& location) const
{
	if (HasGameObject(location)) {
		return _grid[location.y][location.x].Top();
	}
	else {
		LOG_ERROR("尝试获取不存在的GameObject");
		return nullptr;
	}
}


void GameMap::MoveGameObject(const Location& from, const Location& to)
{
	if (HasGameObject(from)) {
		AddGameObject(GetGameObject(from), to);
		RemoveGameObject(from);
	}
	else {
		LOG_ERROR("尝试移动不存在的GameObject");
	}
}

void GameMap::RemoveGameObject(const Location& location)
{
	if (HasGameObject(location)) {
		_grid[location.y][location.x].Pop();
	}
	else {
		LOG_ERROR("尝试删除不存在的GameObject");
	}
}

void GameMap::AddGameObject(AutoGameObject object, const Location& location)
{
	if (InGameMap(location)) {
		_grid[location.y][location.x].Push(object);
		object->SetLocation(location);
	}
	else {
		LOG_ERROR("尝试在非法坐标"+location.ToString() + "添加GameObject");
	}
}

void GameMap::ReplaceGameObject(AutoGameObject object, const Location& location)
{
	if (HasGameObject(location)) {
		_grid[location.y][location.x].Pop();
	}
	else {
		LOG_ERROR("替换位置:" + location.ToString() + "没有object,已改为添加");
	}
	object->SetLocation(location);
	_grid[location.y][location.x].Push(object);
}

void GameMap::Print() const
{
	for (auto row : _grid) {
		for (auto stack: row) {
			ScreenDrawer::getInstance().drawCharacter(
			stack.Top()->GetLocation().x,
			stack.Top()->GetLocation().y,
			stack.Top()->GetIcon()
			);
		}
	}
}

const GameMapGrid& GameMap::GetMapGrid() const
{
	return _grid;
}

void GameObjectStack::Push(AutoGameObject obj)
{
	_stack.push(obj);
}

void GameObjectStack::Pop()
{
	_stack.pop();
}

AutoGameObject GameObjectStack::Top() const
{
	return _stack.top();
}

bool GameObjectStack::IsEmpty() const
{
	return _stack.empty();
}

GameMapFactory& GameMapFactory::getInstance()
{
	static GameMapFactory instance;
	return instance;
}

AutoGameMap GameMapFactory::Create(const MapID& id, int rows, int cols,AutoMapInit init)
{
	return AutoGameMap(new GameMap(id,rows,cols,std::move(init)));
}

AutoGameMap GameMapFactory::createFromConf()
{
	return AutoGameMap(new GameMap(
		Config::instance().getConfigData().game.maps[0].mapid,
		Config::instance().getConfigData().game.maps[0].maxRows,
		Config::instance().getConfigData().game.maps[0].maxColumns,
		std::move(AutoMapInit(new DefaultMapInitializer()))
	));
}

GameMapFactory::GameMapFactory()
{
}




void DefaultMapInitializer::initialize(GameMap& map)
{
	for (int y = 0; y < map.GetRows(); ++y) {
		for (int x = 0; x < map.GetCols(); ++x) {
			map.AddGameObject(
				GameObjectFactory::getInstance().createGroundFromConf({ x,y }),
				{x,y}
			);
		}
	}
}
