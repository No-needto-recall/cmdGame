#pragma once


//位置信息
struct Location
{
	int _x;
	int _y;
};


//基类角色类

class BasicRole {
public:

	BasicRole(const  Location&& location);
	virtual ~BasicRole();
	//获取位置
	const Location& getLocation()const;
	Location& getLocation();

protected:
	Location _location;
};
