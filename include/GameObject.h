#pragma once
#include <string>


using std::string;

//位置结构体
struct Location {
    int x;
    int y;
};

//图标
using Icon = char;



class GameObject {
public:
    GameObject(const string& name, Location location, Icon icon);

    // Getters and Setters
    Location getLocation() const;
    void setLocation(Location newLocation);

    Icon getIcon() const;
    void setIcon(Icon newIcon);

    string getName() const;
    void setName(const string& newName);

private:
    string _name;
    Location _location;
    Icon _icon;
};

