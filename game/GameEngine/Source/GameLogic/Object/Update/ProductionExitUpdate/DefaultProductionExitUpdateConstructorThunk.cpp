// cl: /O2 /MD /EHsc

class Thing;
class ModuleData;

inline void *operator new(unsigned int, void *where)
{
	return where;
}

class DefaultProductionExitUpdate
{
public:
	DefaultProductionExitUpdate(Thing *, const ModuleData *);
};

class Rva00025581DefaultProductionExitUpdateThunk
{
public:
	void forward(Thing *, const ModuleData *);
};

void Rva00025581DefaultProductionExitUpdateThunk::forward(
	Thing *thing, const ModuleData *moduleData)
{
	__assume(this != 0);
	new (this) DefaultProductionExitUpdate(thing, moduleData);
}
