// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// readable body of ?findTeamByID@TeamFactory@@QAEPAVTeam@@I@Z: Code/GameEngine/Source/Common/RTS/Team.cpp
// Open-BFME: TeamFactory::findTeamByID, retail 0x000EF060, 90 bytes.
//
// Zero Hour's body unchanged: reject the invalid id, then walk every prototype
// in the map and every team instance hanging off it until one carries the id.
//
// The two containers are the ones already established elsewhere in the tree.
// m_prototypes is TeamFactoryCtorThunk.cpp's pair-keyed STLport map at +0x0c,
// which is why the prototype comes out of the node at +0x18 -- sixteen bytes of
// links plus the eight-byte key -- and why the step is a call to the tree's
// _M_increment with the map's header re-read for end() on every turn. The team
// instance list is the one TeamPrototype_countBuildings.cpp measured: head at
// +0x274, advance through the thunk at 0x00022A70, and advance() carrying its
// own null check, which is the second test on the same register.
#define __PLACEMENT_VEC_NEW_INLINE
#include <map>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef UnsignedInt TeamID;

enum { TEAM_ID_INVALID = 0 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	TeamID getID(void) const { return m_id; }

	// Shape only: thiscall on the team, no arguments, the next team back.
	Team *_bfme_nextInInstanceList(void);				// ILT thunk at 0x00022A70

private:
	void *m_unmodelled_000[2];
	TeamID m_id;										// +0x08
};

class BfmeTeamInstanceIterator
{
public:
	BfmeTeamInstanceIterator( Team *head ) : m_cur( head ) { }

	Bool done(void) const { return m_cur == 0; }
	Team *cur(void) const { return m_cur; }
	void advance(void) { if( m_cur ) m_cur = m_cur->_bfme_nextInInstanceList(); }

private:
	Team *m_cur;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamPrototype
{
public:
	BfmeTeamInstanceIterator iterate_TeamInstanceList(void)
	{
		return BfmeTeamInstanceIterator( m_teamInstanceList );
	}

private:
	unsigned char m_unmodelled_000[0x274];
	Team *m_teamInstanceList;							// +0x274
};

// The two bases TeamFactoryCtorThunk.cpp models: a vptr and one pointer, then
// a second vptr, putting the map at +0x0c.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();

	virtual void init(void);
	virtual void reset(void);
	virtual void update(void);

private:
	void *m_name;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	Snapshot() {}
	virtual ~Snapshot() {}

	virtual void crc(void);
	virtual void xfer(void);
	virtual void loadPostProcess(void);
};

typedef std::pair<int, int> BfmeTeamPrototypeKey;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class TeamFactory : public SubsystemInterface, public Snapshot
{
public:
	TeamFactory();
	virtual ~TeamFactory();

	virtual void init(void);
	virtual void reset(void);
	virtual void update(void);

	Team *findTeamByID( TeamID id );

protected:
	virtual void crc(void);
	virtual void xfer(void);
	virtual void loadPostProcess(void);

private:
	std::map<BfmeTeamPrototypeKey, TeamPrototype *, std::less<BfmeTeamPrototypeKey> > m_prototypes;
	Int m_uniqueTeamPrototypeID;
	Int m_uniqueTeamID;
};

// ?findTeamByID@TeamFactory@@QAEPAVTeam@@I@Z
Team *TeamFactory::findTeamByID( TeamID id )
{
	if( id == TEAM_ID_INVALID )
		return NULL;

	for( std::map<BfmeTeamPrototypeKey, TeamPrototype *, std::less<BfmeTeamPrototypeKey> >::iterator it = m_prototypes.begin(); it != m_prototypes.end(); ++it )
	{
		TeamPrototype *proto = (*it).second;
		for( BfmeTeamInstanceIterator iter = proto->iterate_TeamInstanceList(); !iter.done(); iter.advance() )
		{
			Team *team = iter.cur();
			if( team->getID() == id )
				return team;
		}
	}

	return NULL;
}
