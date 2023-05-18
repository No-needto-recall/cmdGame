#include <memory>
#include "GameMap.h"
#include "Log.h"

GameMap::GameMap(const MapID& id, int rows, int cols)
	:_id(id)
	,_rows(rows)
	,_cols(cols)
{
	LOG_INFO("创建地图:" + _id + "(" + to_string(_rows) + "*" + to_string(_cols) + ")");
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
		if (_grid[y][x] != nullptr) {
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
		return _grid[location.y][location.x];
	}
	else {
		LOG_ERROR("尝试获取不存在的GameObject");
		return nullptr;
	}
}

void GameMap::MoveGameObject(const Location& from, const Location& to)
{
	AutoGameObject target = GetGameObject(from);
	//判断尝试移动的位置是否存在对象
	if (target) {
		//判断新位置是否存在对象	
		if (HasGameObject(to)) {
			//二次检测碰撞
			LOG_ERROR(to.ToString() + "已有GameObject");
		}
		else {
			//更新
			target->SetLocation(to);
		}
	}
}


