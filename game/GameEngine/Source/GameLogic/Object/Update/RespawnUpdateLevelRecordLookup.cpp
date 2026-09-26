// cl: /O2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// ?m002A23B0@RespawnUpdate@@QAEHXZ
// Owner evidence: caller 0x000FA1B0 looks up literal RespawnUpdate at
// VA 0x01085FFC, then calls ILT 0x0001C65C -> this body on that module.
// Both finds use ILT 0x0003994B -> 0x002A1D40, the unsigned-key STL tree
// find. The exact original method and record names remain unknown.
// Sibling 0x002A22E0 has the same lookup but returns node+0x14 (default 1000).
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
	int m002A23B0();
private:
	void *vtable;
	RespawnUpdateModuleData *moduleData;
	Rva002A23B0Object *object;
};
int RespawnUpdate::m002A23B0()
{
	RespawnUpdateModuleData *data = moduleData;
	unsigned int level = object->state->level;
	Rva002A23B0Set::iterator result = data->levels.find(Rva002A23B0Record(level));
	Rva002A23B0Set::iterator end = data->levels.end();
	if (result == end) {
		result = data->levels.find(Rva002A23B0Record(1));
		if (result == end)
			return 149;
	}
	return result->unknown08 / 1000;
}
