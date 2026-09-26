// cl: /O2 /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;

class SpawnPointProductionExitUpdate
{
public:
	SpawnPointProductionExitUpdate(Thing *, const ModuleData *);
};

inline void *operator new(unsigned int, void *where)
{
	return where;
}

class Rva00023858SpawnPointProductionExitUpdateThunk
{
public:
	void forward(Thing *, const ModuleData *);
};

void Rva00023858SpawnPointProductionExitUpdateThunk::forward(
	Thing *thing, const ModuleData *moduleData)
{
	__assume(this != 0);
	new (this) SpawnPointProductionExitUpdate(thing, moduleData);
}
