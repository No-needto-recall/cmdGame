#include "Role.h"
#include "Behavior.h"


BasicRole::BasicRole(const Location & location)
	:_location(location)
{}

BasicRole::~BasicRole()
{}

const Location& BasicRole::getLocation()const {
	return _location;
}

Location& BasicRole::getLocation() {
	return _location;
}

Role::Role(const Attribute& attribute,
		   const Location& location)
	:BasicRole(location),_attribute(attribute)
{}

Role::Role(const Attribute& attribute, const Location& location, unique_ptr<Behavior> behavior)
	:BasicRole(location),_attribute(attribute)
	,_behavior(std::move(behavior))
{
}

Role::~Role()
{}

const Attribute& Role::getAttribute() const
{
	return _attribute;
}

Attribute& Role::getAttribute()
{
	return _attribute;
}

const unique_ptr<Behavior>& Role::getBehavior() const
{
	return _behavior;
}

void Role::setBehavior(unique_ptr<Behavior> behavior)
{
	_behavior = std::move(behavior);
}

bool Attribute::isAlive() const
{
	return _health>0;
}

bool Attribute::isDeath() const
{
	return _health<=0;
}

string Location::toString() const
{
	string tmp = "(" + 
				std::to_string(_x) + 
				"," +
				std::to_string(_y) +
				")";
	return tmp;
}
