// cl: /O2 /DNDEBUG /MD /EHsc
// The carved 5-byte ILT at 0x00036A0C routes to the matched
// StealthDetectorUpdate constructor at 0x002AB4A0.

class Thing;
class ModuleData;

class StealthDetectorUpdate
{
public:
	StealthDetectorUpdate(Thing *, const ModuleData *);
};

inline void *operator new(unsigned int, void *where)
{
	return where;
}

class Rva00036A0CStealthDetectorUpdateConstructorThunk
{
public:
	void forward(Thing *, const ModuleData *);
};

void Rva00036A0CStealthDetectorUpdateConstructorThunk::forward(
	Thing *thing, const ModuleData *moduleData)
{
	__assume(this != 0);
	new (this) StealthDetectorUpdate(thing, moduleData);
}
