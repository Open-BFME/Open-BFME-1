// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define __PLACEMENT_VEC_NEW_INLINE
#include <map>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef UnsignedInt TeamID;

enum { TEAM_ID_INVALID = 0 };

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
class Team
{
public:
	virtual ~Team();
	void removeOverrideTeamRelationship(TeamID teamID);
	Team *_bfme_nextInInstanceList(void);
	TeamID getID(void) const { return m_id; }

private:
	void *m_unmodelled;
	TeamID m_id;
};

class TeamPrototype
{
public:
	unsigned char m_unmodelled[0x274];
	Team *m_teamInstanceList;

	class InstanceIterator
	{
	public:
		InstanceIterator(Team *head) : m_cur(head) {}
		bool done(void) const { return m_cur == 0; }
		Team *cur(void) const { return m_cur; }
		void advance(void)
		{
			if (m_cur)
				m_cur = m_cur->_bfme_nextInInstanceList();
		}

	private:
		Team *m_cur;
	};

	InstanceIterator iterate_TeamInstanceList(void)
	{
		return InstanceIterator(m_teamInstanceList);
	}
	void teamAboutToBeDeleted(Team *team);
};

typedef std::pair<Int, Int> BfmeTeamPrototypeKey;

class PlayerList
{
public:
	void teamAboutToBeDeleted(Team *team);
};

extern PlayerList *ThePlayerList;

// The BFME TeamFactory map is the pair-keyed STLport tree at +0x0c.
class TeamFactory : public SubsystemInterface, public Snapshot
{
public:
	void teamAboutToBeDeleted(Team *team);

private:
	std::map<BfmeTeamPrototypeKey, TeamPrototype *, std::less<BfmeTeamPrototypeKey> > m_prototypes;
};

extern TeamFactory *TheTeamFactory;

// ?teamAboutToBeDeleted@TeamPrototype@@QAEXPAVTeam@@@Z
void TeamPrototype::teamAboutToBeDeleted(Team *team)
{
	for (InstanceIterator iter = iterate_TeamInstanceList(); !iter.done(); iter.advance())
	{
		iter.cur()->removeOverrideTeamRelationship(
			team ? team->getID() : TEAM_ID_INVALID);
	}
}

// ?teamAboutToBeDeleted@TeamFactory@@QAEXPAVTeam@@@Z
void TeamFactory::teamAboutToBeDeleted(Team *team)
{
	for (std::map<BfmeTeamPrototypeKey, TeamPrototype *, std::less<BfmeTeamPrototypeKey> >::iterator it = m_prototypes.begin(); it != m_prototypes.end(); ++it)
	{
		it->second->teamAboutToBeDeleted(team);
	}
	if (ThePlayerList)
		ThePlayerList->teamAboutToBeDeleted(team);
}

void deleteTeamCallback(Team *team)
{
	if (team)
	{
		TheTeamFactory->teamAboutToBeDeleted(team);
		delete team;
	}
}
