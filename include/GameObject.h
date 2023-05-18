#pragma once

#include <string>

using std::string;


//位置结构体
struct Location {
    int x;
    int y;

    // 转换为字符串的函数，便于记录日志
    string ToString() const;
};

//图标类型
using Icon = char;

class GameObject {
public:
    GameObject(const Location& location, Icon icon, const string& name);

    // 获取物体的位置
    Location GetLocation() const;
    // 设置物体的位置
    void SetLocation(const Location& newLocation);

    // 获取物体的图标
    Icon GetIcon() const;
    // 设置物体的图标
    void SetIcon(Icon newIcon);

    // 获取物体的名称
    string GetName() const;
    // 设置物体的名称
    void SetName(const string& newName);

private:
    Location _location;
    Icon _icon;
    string _name;
};
