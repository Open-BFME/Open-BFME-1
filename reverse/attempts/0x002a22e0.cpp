// ?d_002a22e0@@YAXXZ
// partial score=0.884 date=2026-09-24
// Retail 0x002A22E0 is an anonymous thiscall, ret 0, returning a 32-bit
// integer. The receiver contains a module-data pointer at +4 and an object
// pointer at +8. The former's map at +0xA0 is witnessed by the matched
// ParticleUplinkCannonUpdateModuleData constructor; the owning receiver is
// NOT proven to be that class, so it remains address-qualified here.
// The two retail calls reach STLport unsigned-key tree find at 0x002A1D40.
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#include <map>
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct Rva002A22E0Key
{
	unsigned int id;
	unsigned int zero4;
	unsigned int zero8;
	float oneC;
	unsigned char zero10;
	unsigned char pad11[3];
	Rva002A22E0Key(unsigned int k)
		: id(k), zero4(0), zero8(0), oneC(1.0f), zero10(0) {}
	operator const unsigned int &() const { return id; }
};

struct Rva002A22E0Value { unsigned int words[4]; };
typedef std::map<unsigned int, Rva002A22E0Value> Rva002A22E0Map;

struct Rva002A22E0Data
{
	char pad[0xa0];
	Rva002A22E0Map map;
};

struct Rva002A22E0Linked
{
	char pad[0x28];
	unsigned int id;
};

struct Rva002A22E0Object
{
	char pad[0x210];
	Rva002A22E0Linked *linked;
};

class Rva002A22E0Owner
{
public:
	int query();
private:
	void *opaque0;
	Rva002A22E0Data *data;
	Rva002A22E0Object *object;
};

int Rva002A22E0Owner::query()
{
	Rva002A22E0Data *localData = data;
	Rva002A22E0Object *localObject = object;
	unsigned int keyId = localObject->linked->id;
	_ReadWriteBarrier();
	Rva002A22E0Map &map = localData->map;
	Rva002A22E0Map::iterator it = map.find(Rva002A22E0Key(keyId));
	if (it == map.end()) {
		it = map.find(Rva002A22E0Key(1));
		if (it == map.end())
			return 1000;
	}
	return it->second.words[0];
}
