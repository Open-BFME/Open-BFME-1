// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Near-twin of FXListStoreBody::~FXListStoreBody (twin 0x0042DE50,
// FXListStoreDtorThunk.cpp): a SubsystemInterface subclass whose only member
// is a hash_map<int, T> at +8, destructed by an explicit clear() (matching
// ZH's habit of clearing before the implicit hash_map destructor runs).
// Shares vtable 0x0109C838 with 0x001B0BC0 (tools/vtable_lookup.py); real
// class identity not recovered, so the name is address-derived. Landed
// neighbour 0x001B0780 (Rva001B0780HashtableInsert.cpp) recovers the value
// type's total size as 0x64 bytes for this same hash member.

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

struct Rva001B0820Value
{
	char a[0x60];
	Rva001B0820Value();
	Rva001B0820Value(const Rva001B0820Value &);
	~Rva001B0820Value();
	Rva001B0820Value &operator=(const Rva001B0820Value &);
};

bool operator==(const Rva001B0820Value &, const Rva001B0820Value &);
bool operator<(const Rva001B0820Value &, const Rva001B0820Value &);

typedef _STL::pair<const int, Rva001B0820Value> Rva001B0820MapPair;

// address-derived
class Rva001B0820Store : public SubsystemInterface
{
public:
	Rva001B0820Store();
	virtual ~Rva001B0820Store();
	virtual void init();
	virtual void reset();
	virtual void update();

private:
	_STL::hash_map<int, Rva001B0820Value, _STL::hash<int>, _STL::equal_to<int>, _STL::allocator<Rva001B0820MapPair> > m_map;
};

// address-derived: ?d_001b0820@@YAXXZ real name and identity not recovered
Rva001B0820Store::~Rva001B0820Store()
{
	m_map.clear();
}
