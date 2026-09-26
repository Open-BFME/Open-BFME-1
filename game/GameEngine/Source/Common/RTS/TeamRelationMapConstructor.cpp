// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// readable body of ??0TeamRelationMap@@QAE@XZ: game/GameEngine/Source/Common/RTS/Team.cpp
//
// TeamRelationHashTable below is NOT legacy cruft standing in for a container
// nobody got round to using, and it must not be replaced by the real
// _STL::hash_map that TeamRelationMapDestructor.cpp models the same member
// with. That was tried, and here is what it measures:
//
//   Rebuilt against the real hash_map, this constructor's body comes out
//   BYTE-IDENTICAL to retail except for one call displacement --
//   `e8 2f f3 f1 ff` becomes `e8 00 00 00 00` -- with even the `6a 64` that
//   pushes 100 intact.
//
// One displacement and nothing else is the whole result. The hand-written table
// is not reproducing the container's code; the real header reproduces that
// perfectly well. What it is doing is giving the bucket-initialisation call a
// PINNED NAME: targets/game/reverse/symbols.csv carries
// ?initializeBuckets@TeamRelationHashTable@@AAEXI@Z at 0x00016A59, noted as the
// ILT that retail's REL32 at 0x000F7726 targets. Under the real header the same
// call goes to an unpinned STLport symbol and cannot resolve.
//
// So this constructor and the destructor need mutually exclusive models of one
// member, and cannot share a translation unit however alike their flag lines
// look. That is a third instance of one class of constraint worth naming:
//
//   FILE BOUNDARIES DECIDED BY SYMBOL RESOLUTION RATHER THAN BY SUBJECT.
//
//   * ScoreKeeperCounters.cpp: a body big enough to SPILL an inline accessor
//     forces that accessor onto the class whose symbol the spill needs --
//     getTemplate had to be declared on Thing, not Object.
//   * ProductionPrerequisiteThunks.cpp / ...Shims.cpp: a body small enough to
//     be nothing but a jump forces its callee OUT of the file, because a
//     visible definition is an invitation the compiler accepts.
//   * here: a member's model is chosen so that a call lands on a pinned name.
//
// Three different mechanisms, one consequence -- which file a thing lives in is
// decided by what symbol has to come out, not by what the code is about.

#include <vector>

class Xfer;

class TeamRelationPoolObject
{
public:
	TeamRelationPoolObject() {}
	virtual ~TeamRelationPoolObject();
};

class TeamRelationHashTable
{
public:
	__forceinline TeamRelationHashTable()
		: m_size(0)
	{
		initializeBuckets(100);
	}
	~TeamRelationHashTable();

private:
	void initializeBuckets(unsigned int count);

	unsigned int m_hashState;
	_STL::vector<void *> m_buckets;
	unsigned int m_size;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamRelationMap : public TeamRelationPoolObject
{
public:
	TeamRelationMap();
	virtual ~TeamRelationMap();

protected:
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();

private:
	TeamRelationHashTable m_map;
};

// BFME uses one polymorphic base here, unlike the later Zero Hour layout.
TeamRelationMap::TeamRelationMap()
{
}
