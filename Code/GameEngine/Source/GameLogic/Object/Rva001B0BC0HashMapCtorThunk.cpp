// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Near-twin of DamageFXStore::DamageFXStore (twin 0x00067C10,
// DamageFXStoreCtorThunk.cpp): a SubsystemInterface subclass constructing a
// hash_map<int, T>(100) member at +8 and immediately clearing it. Pairs with
// the destructor landed at 0x001B0820 (Rva001B0820HashMapDtorThunk.cpp),
// which recovers the same vtable (0x0109C838, tools/vtable_lookup.py) and the
// same 0x64-byte node size. Real class identity not recovered, so the name
// is address-derived.

#include <hash_map>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual bool loadIniFilesFromLegend();
	virtual void reset() = 0;
	virtual void update() = 0;

private:
	void *m_name;
};

struct Rva001B0BC0Value
{
	char a[0x60];
	Rva001B0BC0Value();
	Rva001B0BC0Value(const Rva001B0BC0Value &);
	~Rva001B0BC0Value();
	Rva001B0BC0Value &operator=(const Rva001B0BC0Value &);
};

bool operator==(const Rva001B0BC0Value &, const Rva001B0BC0Value &);
bool operator<(const Rva001B0BC0Value &, const Rva001B0BC0Value &);

typedef _STL::pair<const int, Rva001B0BC0Value> Rva001B0BC0MapPair;

// address-derived
class Rva001B0BC0Store : public SubsystemInterface
{
public:
	Rva001B0BC0Store();
	virtual ~Rva001B0BC0Store();
	virtual void init();
	virtual void reset();
	virtual void update();

private:
	_STL::hash_map<int, Rva001B0BC0Value, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<Rva001B0BC0MapPair> > m_map;
};

// address-derived: ?d_001b0bc0@@YAXXZ real name and identity not recovered
Rva001B0BC0Store::Rva001B0BC0Store() : m_map(100)
{
	m_map.clear();
}
