// cl: /O2 /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;

class ToppleUpdate
{
public:
	ToppleUpdate(Thing *, const ModuleData *);
};

inline void *operator new(unsigned int, void *where)
{
	return where;
}

class Rva00035D91ToppleUpdateThunk
{
public:
	void forward(Thing *, const ModuleData *);
};

void Rva00035D91ToppleUpdateThunk::forward(Thing *thing, const ModuleData *moduleData)
{
	__assume(this != 0);
	new (this) ToppleUpdate(thing, moduleData);
}
