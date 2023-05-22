#pragma once
#include <tuple>
#include "GameManager.h"


using std::tuple;
using std::string;
using std::get;

using PortalKey = tuple<LevelID, MapID, Location>;
using PortalInfo= tuple<LevelID, MapID, Location>;


//键的哈希函数
struct PortalKeyHash {
    std::size_t operator() (const PortalKey& key) const;
};
struct PortalKeyEqual {
    bool operator()(const PortalKey& a, const PortalKey& b) const;
};
using PortalMap = unordered_map<PortalKey, PortalInfo,PortalKeyHash,PortalKeyEqual>;


class PortalManager {
public:
    //获取单例实例
    static PortalManager& GetInstance();

    //添加传送门，参数为传送门的位置(关卡ID、地图ID、位置）和目标传送地信息
    void AddPortal(const PortalKey& key, const PortalInfo& info);

    //移除传送门
    void RemovePortal(const PortalKey& key);

    // 获取传送门信息，如果该位置存在传送门，则返回其目标信息
      // 如果不存在，返回nullopt
    PortalInfo GetPortalInfo(const PortalKey& key);

    
    string KeyToString(const PortalKey& key);
    string InfoToString(const PortalInfo& info);
private:
	PortalManager()=default;
	PortalManager(const PortalManager&)=default;
	PortalManager& operator=(const PortalManager&) = default;

    PortalMap _portals;//用于保存所有传送门的信息
    static PortalInfo invalidPortalInfo;//无效的传送门信息
	
};
