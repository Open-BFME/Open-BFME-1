// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: CaveContain::changeTeamOnAllConnectedCaves, retail 0x00219E80, 225 bytes.
// Ghidra/gen-dump listed 222 and omitted the trailing ret 8 (C2 08 00).
// ZH twin: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Contain/CaveContain.cpp
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>
#include <list>

typedef int ObjectID;
typedef bool Bool;

class Object;
class Team;

typedef _STL::hash_map<ObjectID, Object *, _STL::hash<ObjectID>, _STL::equal_to<ObjectID> > ObjectPtrHash;

class CaveInterface
{
public:
	virtual void tryToSetCaveIndex(int newIndex) = 0;
	virtual void setOriginalTeam(Team *oldTeam) = 0;
};

class BehaviorModuleIface
{
public:
	virtual void pad00() = 0;
	virtual void pad01() = 0;
	virtual void pad02() = 0;
	virtual void pad03() = 0;
	virtual void pad04() = 0;
	virtual void pad05() = 0;
	virtual void pad06() = 0;
	virtual void pad07() = 0;
	virtual void pad08() = 0;
	virtual void pad09() = 0;
	virtual void pad10() = 0;
	virtual void pad11() = 0;
	virtual void pad12() = 0;
	virtual void pad13() = 0;
	virtual void pad14() = 0;
	virtual CaveInterface *getCaveInterface() = 0;
};

class BehaviorModuleBase
{
public:
	virtual void padBase() = 0;

private:
	char m_pad[8];
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleIface
{
};

class Object
{
public:
	BehaviorModule **getBehaviorModules()
	{
		return m_modules;
	}

	Team *getTeam()
	{
		return m_team;
	}

	void defect(Team *newTeam, unsigned int detectionTime);

private:
	char m_pad0[0x1F0];
	BehaviorModule **m_modules;
	char m_pad1[0x23C - 0x1F4];
	Team *m_team;
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id)
	{
		if (id == 0)
			return 0;
		ObjectPtrHash::iterator it = m_objHash.find(id);
		if (it == m_objHash.end())
			return 0;
		return (*it).second;
	}

private:
	char m_slice_pad[0xB0];
	ObjectPtrHash m_objHash;
};

extern GameLogic *TheBfmeGameLogic;

class BfmeK1101
{
public:
	const _STL::list<ObjectID> *getContainerList() const
	{
		return &m_tunnelIDs;
	}

private:
	void *m_vtable;
	_STL::list<ObjectID> m_tunnelIDs;
};

class BfmeJ1101
{
public:
	BfmeK1101 *bfmeFind1101(int key);
};

extern BfmeJ1101 *g_bfmeJ1101;

class CaveContain
{
public:
	void changeTeamOnAllConnectedCaves(Team *newTeam, Bool setOriginalTeams);

private:
	char m_pad[0xDC];
	int m_caveIndex;
};

// ?changeTeamOnAllConnectedCaves@CaveContain@@QAEXPAVTeam@@_N@Z
void CaveContain::changeTeamOnAllConnectedCaves(Team *newTeam, Bool setOriginalTeams)
{
	BfmeK1101 *myTracker = g_bfmeJ1101->bfmeFind1101(m_caveIndex);
	const _STL::list<ObjectID> *allCaves = myTracker->getContainerList();
	for (_STL::list<ObjectID>::const_iterator iter = allCaves->begin(); iter != allCaves->end(); ++iter)
	{
		Object *currentCave = TheBfmeGameLogic->findObjectByID(*iter);
		if (currentCave)
		{
			CaveInterface *caveModule = 0;
			for (BehaviorModule **i = currentCave->getBehaviorModules(); *i; ++i)
			{
				CaveInterface *c = (*i)->getCaveInterface();
				if (c != 0)
				{
					caveModule = c;
					break;
				}
			}
			if (caveModule == 0)
				continue;
			if (setOriginalTeams)
				caveModule->setOriginalTeam(currentCave->getTeam());
			else
				caveModule->setOriginalTeam(0);
			currentCave->defect(newTeam, 0);
		}
	}
}
