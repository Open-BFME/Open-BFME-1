// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/objectdlink /ICode/Libraries/Source/WWVegas/WWLib
// Retail 0x000F6490, Team::killTeam(), 636 bytes.
// Identity: the matched ScriptActions::doTeamKill (0x002F3B60) calls it
// through the ILT 0x000341D0; Player::killPlayer is the other caller.
// Zero Hour twin: Team::killTeam in GeneralsMD Team.cpp. BFME splits the
// members into two lists and treats status 0x20000000 members through their
// container.
// stlport

#define _STLP_NO_EXCEPTIONS 1

#include <list>
#include "ascii_string.h"

typedef bool Bool;
typedef unsigned int UnsignedInt;

// Canonical GameLogic/Damage.h types; the retail Object::kill decoration and
// the observed pushes are DamageType(8), DeathType(0).
enum DamageType { DAMAGE_UNRESISTABLE = 8 };
enum DeathType { DEATH_NORMAL = 0 };

class Object;
class Team;

class BfmeObjectVirtualTail { public: unsigned char m_vt[4]; };

class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};

class BfmeObjectVtbl
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18();
};

class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList(void) const;
};

class Overridable
{
public:
	const Overridable *getFinalOverride(void) const
	{
		if (m_nextOverride)
			return m_nextOverride->getFinalOverride();
		return this;
	}

	void *m_vtable;
	Overridable *m_nextOverride;
	Bool m_isOverride;
};

class ThingTemplate : public Overridable
{
public:
	Bool isEquivalentTo(const ThingTemplate *) const;
};

template <class T>
class OVERRIDE
{
public:
	const T *operator->(void) const
	{
		if (!m_overridable)
			return 0;
		return static_cast<const T *>(m_overridable->getFinalOverride());
	}

private:
	const T *m_overridable;
};

// The old pad is the physical Object +0x04 region.  Giving its first word
// the canonical member name lets Object use the native OVERRIDE accessor
// without changing the dlink/vbptr carrier geometry.
class BfmeObjectDlinkPad
{
public:
	OVERRIDE<ThingTemplate> m_template;
	unsigned char m_pad[0x64 - 4];
};

class PlayerTemplate
{
public:
	unsigned char m_unmodelled_000[0xe4];
	AsciiString m_beaconTemplate;
};

class Player
{
public:
	unsigned char m_unmodelled_000[4];
	PlayerTemplate *m_playerTemplate;

	PlayerTemplate *getPlayerTemplate(void) const { return m_playerTemplate; }
};

class TeamPrototype
{
public:
	unsigned char m_unmodelled_000[8];
	Player *m_owningPlayer;
};

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	void kill(DamageType damageType, DeathType deathType);

	const ThingTemplate *getTemplate(void) const
	{
		return m_template.operator->();
	}

	Bool isDestroyed(void) const
	{
		return (*reinterpret_cast<const unsigned char *>(
			reinterpret_cast<const unsigned char *>(this) + 0x90) & 1) != 0;
	}

	Bool isEffectivelyDead(void) const
	{
		return (*reinterpret_cast<const unsigned char *>(
			reinterpret_cast<const unsigned char *>(this) + 0x344) & 1) != 0;
	}

	UnsignedInt status(void) const
	{
		return *reinterpret_cast<const UnsignedInt *>(
			reinterpret_cast<const unsigned char *>(this) + 0x94);
	}

	Object *getContainedBy(void) const
	{
		return *reinterpret_cast<Object *const *>(
			reinterpret_cast<const unsigned char *>(this) + 0x214);
	}

	Team *getTeam(void) const
	{
		return *reinterpret_cast<Team *const *>(
			reinterpret_cast<const unsigned char *>(this) + 0x23c);
	}
};

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
};

extern ThingFactory *TheThingFactory;

class Team
{
public:
	void killTeam(void);
	void evacuateTeam(void);

	Player *getControllingPlayer(void) const
	{
		TeamPrototype *prototype = *reinterpret_cast<TeamPrototype *const *>(
			reinterpret_cast<const unsigned char *>(this) + 4);
		if (prototype == 0)
			return 0;
		return prototype->m_owningPlayer;
	}

	void *m_vptr;
	TeamPrototype *m_prototype;
	void *m_id;
	Object *m_memberHead;
};

#define callMemberFunction(object, ptrToMember) ((object).*(ptrToMember))

template <class OBJCLASS>
class BfmeTeamMemberIterator
{
public:
	typedef OBJCLASS *(OBJCLASS::*GetNextFunc)(void) const;

	BfmeTeamMemberIterator(OBJCLASS *current, GetNextFunc getNext) :
		m_current(current),
		m_getNext(getNext)
	{
	}

	void advance(void)
	{
		if (m_current != 0)
			m_current = callMemberFunction(*m_current, m_getNext)();
	}

	Bool done(void) const { return m_current == 0; }
	OBJCLASS *cur(void) const { return m_current; }

private:
	OBJCLASS *m_current;
	GetNextFunc m_getNext;
};

class TeamMembers
{
public:
	static BfmeTeamMemberIterator<Object> iterate(const Team *team)
	{
		return BfmeTeamMemberIterator<Object>(team->m_memberHead,
			Object::dlink_next_TeamMemberList);
	}
};

void Team::killTeam(void)
{
	std::list<Object *> objectsToKill;
	std::list<Object *> objectsWithStatus;

	evacuateTeam();

	Player *owner = getControllingPlayer();
	PlayerTemplate *playerTemplate = owner->getPlayerTemplate();
	const ThingTemplate *beaconTemplate = TheThingFactory->findTemplate(
		*reinterpret_cast<const AsciiString *>(
			reinterpret_cast<const unsigned char *>(playerTemplate) + 0xe4));

	for (BfmeTeamMemberIterator<Object> iter = TeamMembers::iterate(this);
		!iter.done(); iter.advance())
	{
		Object *object = iter.cur();
		if (object == 0 || object->isDestroyed())
			continue;

		if (object->isEffectivelyDead())
		{
			const ThingTemplate *objectTemplate = object->getTemplate();
			if (!objectTemplate->isEquivalentTo(beaconTemplate))
				continue;
		}

		Team *objectTeam = object->getTeam();
		if ((object->status() & 0x20000000U) != 0)
			objectsWithStatus.push_back(object);
		else if (objectTeam == this)
			objectsToKill.push_back(object);
	}

	for (std::list<Object *>::iterator node = objectsToKill.begin();
		node != objectsToKill.end(); ++node)
	{
		(*node)->kill(DAMAGE_UNRESISTABLE, DEATH_NORMAL);
	}

	for (std::list<Object *>::iterator node = objectsWithStatus.begin();
		node != objectsWithStatus.end(); ++node)
	{
		Object *containedBy = (*node)->getContainedBy();
		if (containedBy != 0 && (*reinterpret_cast<const UnsignedInt *>(
			reinterpret_cast<const unsigned char *>(containedBy->getTemplate()) + 0xd4) & 0x1000U) != 0)
			containedBy->slot18();
		else
			(*node)->slot18();
	}

	objectsToKill.clear();
	objectsWithStatus.clear();
}
