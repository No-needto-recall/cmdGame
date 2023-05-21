#pragma once

#include <string>
#include <memory>
#include <unordered_map>

using std::string;
using std::unique_ptr;
using std::shared_ptr;
using std::unordered_map;

//前置声明
class GameObjectType;
class GameObject;


//类型别名
using AutoGameObjectType = unique_ptr<GameObjectType>;
using AutoGameObject = shared_ptr<GameObject>;
using TypeName = string;
//图标类型
using Icon = char;
//位置结构体
struct Location {
    int x;
    int y;

    // 转换为字符串的函数，便于记录日志
    string ToString() const;
};


//枚举
namespace ObjectType{
    enum Type
    {
		PLAYER = 0, GROUND, WALL, PORTAL, GRASS
    };

}//end of ObjectType
//类型对象
class GameObjectType {
public:
    GameObjectType(const string& name, const char& icon);
    const string& getName()const;
    const char& getIcon()const;
    const ObjectType::Type getType()const;

private:
    TypeName _name;
    char _icon;
};


//游戏中的基础实体
class GameObject {
public:
    GameObject(const Location& location, GameObjectType* type);

    // 获取物体的位置
    const Location& GetLocation()const;
    // 设置物体的位置
    void SetLocation(const Location& newLocation);
    //获取位置的字符串形式
    string LocationToString()const;


    //获取类别
    ObjectType::Type GetType()const;
    // 获取物体的图标
    const Icon& GetIcon() const;
    // 获取物体的名称
    const string& GetName() const;


private:
    Location _location;
    GameObjectType* _type;
};




//单例工厂
class GameObjectFactory {
public:
    //获取句柄
    static GameObjectFactory& getInstance();
    //创建
    AutoGameObject create(const TypeName& name, const char icon, const Location& location);

    //根据配置文件创建
    AutoGameObject createFromConf(ObjectType::Type index, const Location& location);
    AutoGameObject createPlayerFromConf(const Location& location);
    AutoGameObject createGroundFromConf(const Location& location);
    AutoGameObject createWallFromConf(const Location& location);
    AutoGameObject createPortalFromConf(const Location& location);
    AutoGameObject createGrassFromConf(const Location& location);
private:
    //存在类型对象,保障享元模式
    unordered_map<TypeName, AutoGameObjectType> _types;
   
    //单例模式，构造私有，禁止赋值语句
    GameObjectFactory(const GameObjectFactory&) = delete;
    void operator = (const GameObjectFactory&) = delete;
    GameObjectFactory();
};
