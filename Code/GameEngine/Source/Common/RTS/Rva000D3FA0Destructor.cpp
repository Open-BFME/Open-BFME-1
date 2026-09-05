// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Byte-twin of ??1TeamRelationMap@@UAE@XZ at 0x000F21C0
// (Code/GameEngine/Source/Common/RTS/TeamRelationMapDestructor.cpp): identical
// 89 bytes once relocations are masked, itself the ZH-twin of
// ??1DisplayString@@MAE@XZ (m_map.clear(); the compiler inlines the empty
// Snapshot destructor). The installed derived vtable (0x01083E94) differs
// from TeamRelationMap's own, matching the sibling class installed by the
// constructor twin Rva000DA590Constructor.cpp (0x000DA590); no name is
// provable, so this is claimed address-derived.

#include <hash_map>

class Xfer;

class Rva000D3FA0PoolObject
{
public:
	virtual ~Rva000D3FA0PoolObject() {}

protected:
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();
};

typedef unsigned int TeamID;
enum Rva000D3FA0Relationship
{
	Rva000D3FA0_NEUTRAL = 0
};

typedef _STL::pair<const TeamID, Rva000D3FA0Relationship> Rva000D3FA0MapPair;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Rva000D3FA0Map : public Rva000D3FA0PoolObject
{
public:
	virtual ~Rva000D3FA0Map();

protected:
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();

private:
	_STL::hash_map<TeamID, Rva000D3FA0Relationship, _STL::hash<TeamID>, _STL::equal_to<TeamID>, _STL::allocator<Rva000D3FA0MapPair> > m_map;
};

// ??1Rva000D3FA0Map@@UAE@XZ
Rva000D3FA0Map::~Rva000D3FA0Map()
{
	m_map.clear();
}
