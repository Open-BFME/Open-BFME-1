// cl: /O2

class Thing;
class ModuleData;

inline void *operator new(unsigned int, void *where)
{
	return where;
}

class ModelConditionUpgrade
{
public:
	ModelConditionUpgrade(Thing *thing, const ModuleData *moduleData);
};

class Rva00025810ModelConditionUpgrade
{
public:
	void forwardModelConditionUpgrade(
		Thing *thing, const ModuleData *moduleData);
};

void Rva00025810ModelConditionUpgrade::forwardModelConditionUpgrade(
	Thing *thing, const ModuleData *moduleData)
{
	__assume(this != 0);
	new (this) ModelConditionUpgrade(thing, moduleData);
}
