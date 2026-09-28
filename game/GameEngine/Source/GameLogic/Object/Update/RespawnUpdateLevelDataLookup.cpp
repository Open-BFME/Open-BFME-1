// cl: /O2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// ?m002A22E0@RespawnUpdate@@QAEHXZ
// Sibling of the landed ?m002A23B0@RespawnUpdate@@QAEHXZ
// (RespawnUpdateLevelRecordLookup.cpp): identical unsigned-key STLport set
// lookup over the module-data +0xA0 level set keyed by object+0x210 level,
// with fallback key 1. Differs only in the tail: this body returns the
// record's +0x14 word directly and defaults to 1000, while the sibling
// returns +0x08/1000 with default 149. Owner RespawnUpdate is proven the
// same way: the 0x000FA1B0 caller looks up literal RespawnUpdate and calls
// this body on that module through ILT 0x00004345 (module->rva002A22E0),
// and the neighbouring getSpawnTemplate 0x002A1B20 is a matched
// RespawnUpdate method on the same module-data + object layout.
#include <set>

struct Rva002A23B0Record
{
	unsigned int level;
	int unknown04;
	int unknown08;
	float unknown0c;
	bool unknown10;
	Rva002A23B0Record(unsigned int value) : level(value), unknown04(0),
		unknown08(0), unknown0c(1.0f), unknown10(false) {}
	bool operator<(const Rva002A23B0Record &other) const
	{ return level < other.level; }
};
typedef _STL::set<Rva002A23B0Record> Rva002A23B0Set;
struct RespawnUpdateModuleData
{
	unsigned char unknown00[0xa0];
	Rva002A23B0Set levels;
};
struct Rva002A23B0State
{
	unsigned char unknown00[0x28];
	unsigned int level;
};
struct Rva002A23B0Object
{
	unsigned char unknown00[0x210];
	Rva002A23B0State *state;
};
class RespawnUpdate
{
public:
	int m002A22E0();
private:
	void *vtable;
	RespawnUpdateModuleData *moduleData;
	Rva002A23B0Object *object;
};
int RespawnUpdate::m002A22E0()
{
	RespawnUpdateModuleData *data = moduleData;
	unsigned int level = object->state->level;
	Rva002A23B0Set::iterator result = data->levels.find(Rva002A23B0Record(level));
	Rva002A23B0Set::iterator end = data->levels.end();
	if (result == end) {
		result = data->levels.find(Rva002A23B0Record(1));
		if (result == end)
			return 1000;
	}
	return result->unknown04;
}
