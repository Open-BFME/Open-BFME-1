// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
// COUNT lane near-twin: the assigned twin
// ??1ElvenWoodSpecialPowerModuleData@@UAE@XZ (0x0025CC80) gave the base shape,
// but the actual callee/offset evidence matches a sibling of the already-landed
// ??1NameKeyGenerator@@UAE@XZ (0x00168710, 79B,
// Code/GameEngine/Source/Common/NameKeyGenerator.cpp) far better: same
// SubsystemInterface base, same pinned "freeSockets"-shaped call at 0x000226E7
// on 'this' directly, same this+0x2bf48 aux-map storage/destroy thunk
// (0x00032B19). NameKeyGenerator.h's own comment records that the landed 79B
// body is deliberately modeled as raw storage "because a real hash_map member
// would force the compiler to emit an implicit ~hash_map() call ... and grow
// the dtor past 79B" -- i.e. this 95B body is the shape that extra call would
// have produced. Two different sizes can't share one mangled name, so this is
// address-derived; the pinned callees are reused directly via address casts
// rather than reusing the NameKeyGenerator class name. Vtable 0x0107F984 (per
// tools/vtable_lookup.py) belongs to a single non-virtual-multiple-inheritance
// base, matching this class's single SubsystemInterface base.

#include "Common/SubsystemInterface.h"

class Rva0008FE00AuxMap
{
public:
	~Rva0008FE00AuxMap();
private:
	unsigned int m_storage[5];
};

class Rva0008FE00Owner : public SubsystemInterface
{
public:
	virtual ~Rva0008FE00Owner();
	virtual void init() { }
	virtual void update() { }
	virtual void reset() { }

private:
	void freeSockets();

	enum { SOCKET_COUNT = 45007 };
	void *m_sockets[SOCKET_COUNT];
	unsigned int m_nextID;
	Rva0008FE00AuxMap m_keyToBucketStorage;
};

Rva0008FE00Owner::~Rva0008FE00Owner()
{
	freeSockets();
}
