// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// TeamRelationMap destructor. Zero Hour's body is m_map.clear(); the compiler
// then destroys the hash_map and inlines the empty Snapshot destructor.
//
// BFME uses one polymorphic base (Snapshot / pool object) rather than ZH's
// MemoryPoolObject + Snapshot pair. Constructor twin:
// Code/GameEngine/Source/Common/RTS/TeamRelationMapConstructor.cpp

#include <hash_map>

class Xfer;

class TeamRelationPoolObject
{
public:
	virtual ~TeamRelationPoolObject() {}

protected:
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();
};

typedef unsigned int TeamID;
enum Relationship
{
	NEUTRAL = 0
};

typedef _STL::pair<const TeamID, Relationship> TeamRelationMapPair;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamRelationMap : public TeamRelationPoolObject
{
public:
	virtual ~TeamRelationMap();

protected:
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();

private:
	_STL::hash_map<TeamID, Relationship, _STL::hash<TeamID>, _STL::equal_to<TeamID>, _STL::allocator<TeamRelationMapPair> > m_map;
};

// ??1TeamRelationMap@@UAE@XZ
TeamRelationMap::~TeamRelationMap()
{
	m_map.clear();
}
