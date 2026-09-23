// ?d_001cf9f0@@YAXXZ
// partial score=0.89 date=2026-09-24
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Reconstructs the BFME Object visibility query from its retail call graph.

#include <list>

typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef int Int;

enum Relationship
{
	REL_ENEMIES = 0,
	REL_NEUTRAL = 1,
	REL_ALLIES = 2
};

enum KindOfType
{
	KINDOF_DISGUISER = 0x57
};

typedef int NameKeyType;

class Object;
class Team;
class Player;
class Module;
class Overridable;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Team
{
public:
	Player *getControllingPlayer() const;
};

class Player
{
public:
	Relationship getRelationship(const Team *team) const;

	char m_pad000[0x230];
	Team *m_defaultTeam;
};

class PlayerList
{
public:
	Player *getNthPlayer(Int index);
};

extern PlayerList *ThePlayerList;

class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	Overridable *m_nextOverride;
	char m_pad008[0xd4 - 8];
	UnsignedInt m_flags;
};

class Thing
{
public:
	virtual void objectAnchor();
	Overridable *m_template;
	Bool isKindOf(KindOfType kind) const;
};

class MemberListView;
typedef _STL::list<Object *> ObjectList;

class ContainModuleInterface
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0;
	virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0;
	virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual Player *getApparentControllingPlayer(Object *viewer) const = 0;
	virtual void slot16() = 0; virtual void slot17() = 0;
	virtual void slot18() = 0; virtual void slot19() = 0;
	virtual void slot20() = 0; virtual void slot21() = 0;
	virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual MemberListView *getMemberView() = 0;
	virtual void slot26() = 0; virtual void slot27() = 0;
	virtual void slot28() = 0; virtual void slot29() = 0;
	virtual void slot30() = 0; virtual void slot31() = 0;
	virtual void slot32() = 0; virtual void slot33() = 0;
	virtual void slot34() = 0; virtual void slot35() = 0;
	virtual void slot36() = 0; virtual void slot37() = 0;
	virtual void slot38() = 0; virtual void slot39() = 0;
	virtual void slot40() = 0; virtual void slot41() = 0;
	virtual void slot42() = 0; virtual void slot43() = 0;
	virtual void slot44() = 0; virtual void slot45() = 0;
	virtual void slot46() = 0; virtual void slot47() = 0;
	virtual void slot48() = 0; virtual void slot49() = 0;
	virtual void slot50() = 0; virtual void slot51() = 0;
	virtual void slot52() = 0; virtual void slot53() = 0;
	virtual void slot54() = 0; virtual void slot55() = 0;
	virtual void slot56() = 0; virtual void slot57() = 0;
	virtual void slot58() = 0; virtual void slot59() = 0;
	virtual void slot60() = 0; virtual void slot61() = 0;
	virtual void slot62() = 0; virtual void slot63() = 0;
	virtual UnsignedInt getContainCount(Bool countRiders) const = 0;
	virtual const ObjectList *getContainedItemsList() const = 0;
	virtual void slot66() = 0; virtual void slot67() = 0;
	virtual UnsignedInt getStealthUnitsContained() const = 0;
};

class MemberListView
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0;
	virtual void slot02() = 0; virtual void slot03() = 0;
	virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0;
	virtual void slot08() = 0; virtual void slot09() = 0;
	virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0;
	virtual void slot14() = 0; virtual void slot15() = 0;
	virtual void slot16() = 0; virtual void slot17() = 0;
	virtual void slot18() = 0; virtual void slot19() = 0;
	virtual void slot20() = 0; virtual void slot21() = 0;
	virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0;
	virtual void slot26() = 0; virtual void slot27() = 0;
	virtual void slot28() = 0; virtual void slot29() = 0;
	virtual void slot30() = 0; virtual void slot31() = 0;
	virtual void slot32() = 0; virtual void slot33() = 0;
	virtual void slot34() = 0; virtual void slot35() = 0;
	virtual void slot36() = 0; virtual void slot37() = 0;
	virtual void slot38() = 0; virtual void slot39() = 0;
	virtual void slot40() = 0; virtual void slot41() = 0;
	virtual void slot42() = 0; virtual void slot43() = 0;
	virtual void slot44() = 0; virtual void slot45() = 0;
	virtual void slot46() = 0; virtual void slot47() = 0;
	virtual void slot48() = 0; virtual void slot49() = 0;
	virtual void slot50() = 0; virtual void slot51() = 0;
	virtual void slot52() = 0; virtual void slot53() = 0;
	virtual void slot54() = 0; virtual void slot55() = 0;
	virtual void slot56() = 0; virtual void slot57() = 0;
	virtual void slot58() = 0;
	virtual const ObjectList &getMemberList() const = 0;
};

class Module
{
public:
	void *m_vtable;
	char m_pad004[0x34 - 4];
	Int m_disguiseAsPlayerIndex;
	void *m_disguiseAsTemplate;
};

class Object : public Thing
{
public:
	Bool query(Object *viewer, Int extra);
	Module *findModule(NameKeyType key) const;
	Bool testStatus(Int status) const;

	char m_pad008[0x90 - 8];
	UnsignedInt m_status;
	char m_pad094[0x1fc - 0x94];
	ContainModuleInterface *m_contain;
	char m_pad200[0x23c - 0x200];
	Team *m_team;
};

class StatusQueryObject
{
};

#pragma comment(linker, "/alternatename:?testStatus@Object@@QBE_NH@Z=?j_000016a4@@YAXXZ")

Bool Object::query(Object *viewer, Int extra)
{
	if (extra == 1)
	{
		Team *team = m_team;
		if (team != 0)
		{
			Player *controller = team->getControllingPlayer();
			if (controller != 0 && ((Player *)viewer)->getRelationship(controller->m_defaultTeam) == REL_ALLIES)
				return false;
		}
	}

	UnsignedInt status = m_status;
	if ((status & 0x8000) != 0 && (status & 0x20000) == 0)
	{
		if (!isKindOf(KINDOF_DISGUISER))
			return false;

		static NameKeyType key_StealthUpdate = TheNameKeyGenerator->nameToKey("StealthUpdate");
		Module *module = findModule(key_StealthUpdate);
		if (module != 0 && module->m_disguiseAsTemplate != 0)
		{
			Player *disguisedPlayer = ThePlayerList->getNthPlayer(module->m_disguiseAsPlayerIndex);
			if (viewer != 0 && disguisedPlayer != 0)
			{
				return !((Player *)viewer)->getRelationship(disguisedPlayer->m_defaultTeam);
			}
		}

		if (extra != 1)
			goto query_success;
		Team *team = m_team;
		if (team == 0)
			return false;
		Player *controller = team->getControllingPlayer();
		if (controller == 0)
			return false;
		if (((Player *)viewer)->getRelationship(controller->m_defaultTeam) != 0)
			return false;
		goto query_success;
	}

	if (extra == 1)
	{
		Team *team = m_team;
		if (team == 0)
				return false;
		Player *controller = team->getControllingPlayer();
		if (controller == 0)
				return false;
		if (((Player *)viewer)->getRelationship(controller->m_defaultTeam) != 0)
				return false;
	}

	Overridable *thingTemplate = m_template;
	if (thingTemplate != 0 && thingTemplate->m_nextOverride != 0)
		thingTemplate = (Overridable *)thingTemplate->m_nextOverride->getFinalOverride();

	if ((thingTemplate->m_flags & 0x1000) != 0)
	{
		ContainModuleInterface *contain = m_contain;
		if (contain != 0)
		{
			MemberListView *view = contain->getMemberView();
			if (view != 0)
			{
				ObjectList members(view->getMemberList());
				Bool memberFound = false;
				for (ObjectList::iterator it = members.begin(); it != members.end(); ++it)
				{
					Object *member = *it;
					if (member == 0)
						continue;
					UnsignedInt memberStatus = member->m_status;
					if ((memberStatus & 0x8000) == 0 || (memberStatus & 0x20000) != 0)
						break;
					memberFound = true;
				}
				if (memberFound)
					return false;
				goto query_success;
			}
		}
	}

	ContainModuleInterface *contain = m_contain;
	if (contain == 0)
		goto query_success;
	Player *apparentController = contain->getApparentControllingPlayer(viewer);
	register UnsignedInt containCount = contain->getContainCount(false);
	if (contain->getStealthUnitsContained() != containCount)
		goto query_success;
	const ObjectList *members = contain->getContainedItemsList();
	ObjectList::const_iterator it = members->begin();
	if (it == members->end())
		goto query_success;
	Object *member = *it;
	if (member == 0)
		goto query_success;
	if (member->testStatus(0x11))
		goto query_success;
	if (viewer == 0)
		goto query_success;
	if (((Player *)viewer)->getRelationship(apparentController->m_defaultTeam) == 0)
		return false;

query_success:
	return true;
}
