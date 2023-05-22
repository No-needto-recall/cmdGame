#include "PortalManager.h"
#include "Log.h"
#include "config.h"

//静态数据成员初始化
PortalInfo PortalManager::invalidPortalInfo = { "","",{-1,-1} };


inline bool PortalKeyEqual::operator()(const PortalKey& a, const PortalKey& b) const {
	return get<0>(a) == get<0>(b) &&
		get<1>(a) == get<1>(b) &&
		get<2>(a).x == get<2>(b).x &&
		get<2>(a).y == get<2>(b).y;
}

inline std::size_t PortalKeyHash::operator()(const PortalKey& key) const
{
	std::size_t level_hash = std::hash<std::string>{}(std::get<0>(key));
	std::size_t map_hash = std::hash<std::string>{}(std::get<1>(key));
	std::size_t location_hash = std::hash<string>{}(std::get<2>(key).ToString());
	return level_hash ^ (map_hash << 1) ^ (location_hash << 2);
}

PortalManager& PortalManager::GetInstance()
{
	static PortalManager instance;
	return instance;
}

void PortalManager::AddPortal(const PortalKey& key, const PortalInfo& info)
{
	if (_portals.insert({ key,info }).second) {
		LOG_INFO("添加传送点"+KeyToString(key) + "to" + InfoToString(info));
	}
	else {
		LOG_ERROR("传送点已存在:"+KeyToString(key));
	}
}

void PortalManager::RemovePortal(const PortalKey& key)
{
	if (!_portals.erase(key)) {
		LOG_ERROR("移除不存在的传送点:"+KeyToString(key));
	}
}

PortalInfo PortalManager::GetPortalInfo(const PortalKey& key)
{
	auto find = _portals.find(key);
	if (find != _portals.end()) {
		return find->second;
	}
	else {
		LOG_ERROR("查找不存在的传送点:"+KeyToString(key));
		return invalidPortalInfo;
	}
}

string PortalManager::KeyToString(const PortalKey& key)
{
	return string(get<0>(key)+":" + get<1>(key) +":" + get<2>(key).ToString());
}

string PortalManager::InfoToString(const PortalInfo& info)
{
	return string(get<0>(info)+":" + get<1>(info) +":" + get<2>(info).ToString());
}
