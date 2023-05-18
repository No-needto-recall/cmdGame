#include "GameObject.h"
#include "Config.h"

using std::to_string;

string Location::ToString() const
{
	return "(" + to_string(x) + "," + to_string(y)+")";
}

GameObject::GameObject(const Location& location,GameObjectType* type)
	:_location(location)
	,_type(type)
{
}

const Location& GameObject::GetLocation() const
{
	return _location;
}

void GameObject::SetLocation(const Location& newLocation)
{
	_location = newLocation;
}

string GameObject::LocationToString() const
{
	return _location.ToString();
}

ObjectType::Type GameObject::GetType() const
{
	return _type->getType();
}

const Icon& GameObject::GetIcon() const
{
	return _type->getIcon();
}


const string& GameObject::GetName() const
{
	return _type->getName();
}


GameObjectType::GameObjectType(const string& name, const char& icon)
	:_name(name)
	,_icon(icon)
{
}

const string& GameObjectType::getName() const
{
	return _name;
}

const char& GameObjectType::getIcon() const
{
	return _icon;
}

const ObjectType::Type GameObjectType::getType() const
{
	ObjectType::Type ret = ObjectType::WALL;
	if (_name == Config::instance().getConfigData().object.types[ObjectType::PLAYER].name) {
		ret = ObjectType::PLAYER;
	}
	else if (_name == Config::instance().getConfigData().object.types[ObjectType::GROUND].name) {
		ret = ObjectType::GROUND;
	}
	else if (_name == Config::instance().getConfigData().object.types[ObjectType::WALL].name) {
		ret = ObjectType::WALL;
	}
	else if (_name == Config::instance().getConfigData().object.types[ObjectType::PORTAL].name) {
		ret = ObjectType::PORTAL;
	}
	else if (_name == Config::instance().getConfigData().object.types[ObjectType::GRASS].name) {
		ret = ObjectType::GRASS;
	}
	return ret;
}

GameObjectFactory& GameObjectFactory::getInstance()
{
	static GameObjectFactory instance;
	return instance;
}

AutoGameObject GameObjectFactory::create(const TypeName& name, const char icon, const Location& location)
{
	if (_types.count(name) == 0) {
		_types[name].reset(new GameObjectType(name, icon));
	}
	return AutoGameObject(new GameObject(location, _types[name].get()));
}

AutoGameObject GameObjectFactory::createFromConf(ObjectType::Type index,const Location& location)
{
	return create(
		Config::instance().getConfigData().object.types[index].name,
		Config::instance().getConfigData().object.types[index].icon,
		location
		);
}

AutoGameObject GameObjectFactory::createPlayerFromConf(const Location& location)
{
	return createFromConf(ObjectType::PLAYER,location);
}

AutoGameObject GameObjectFactory::createGroundFromConf(const Location& location)
{
	return createFromConf(ObjectType::GROUND,location);
}

AutoGameObject GameObjectFactory::createWallFromConf(const Location& location)
{
	return createFromConf(ObjectType::WALL,location);
}

AutoGameObject GameObjectFactory::createGrassFromConf(const Location& location)
{
	return createFromConf(ObjectType::GRASS,location);
}

AutoGameObject GameObjectFactory::createPortalFromConf(const Location& location)
{
	return createFromConf(ObjectType::PORTAL,location);
}

GameObjectFactory::GameObjectFactory()
{
}

