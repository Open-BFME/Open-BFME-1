// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/stringinline
// Open-BFME: ScriptActions::doMergeTeamIntoTeam, retail RVA 0x002FD790, 457 bytes.
//
// Zero Hour twin: ScriptActions::doMergeTeamIntoTeam. BFME looks the
// destination up with the second getTeamNamed flag set instead of falling
// back to TheTeamFactory, refuses to merge a team into itself, hands the
// source team to the destination's controller first, leaves members whose
// container has kind-of bit 12 of the second mask word set, and retries the
// walk up to three times before deleting the emptied source team.
//
// updateTeamAndPlayerStuff is the static helper retail keeps out of line at
// 0x002ED760 (bfmeHelper760); it is inlined into the member loop and called
// for the trailing member, so the loop carries a copy of its body.

#include "StringInline.h"

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

class Player;
class Object;

class Drawable
{
public:
	void setIndicatorColor(Int color);			// ILT 0x00028C09

	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void teamIndicatorChanged() = 0;	// +0x34
};

class BfmeOverridable
{
public:
	BfmeOverridable *friend_getFinalOverride();	// ILT 0x000022BB

	void *m_vptr;
	BfmeOverridable *m_nextOverride;			// +0x04
};

class ThingTemplate : public BfmeOverridable
{
public:
	unsigned char m_unmodelled_08[0xcc];
	UnsignedInt m_kindOfWord1;					// +0xD4
};

class Team;

class BfmeObjectVtbl
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual Drawable *getDrawable() = 0;		// +0x28
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void setTeam(Team *team) = 0;		// +0x50
};

// Sits at +4: the template pointer, and the DLINK getter retail reaches as
// the {0x00401140, -100, 0} member pointer.
class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList(void) const;

	ThingTemplate *m_template;					// +0x04
};

class BfmeObjectDlinkPad
{
public:
	unsigned char m_pad[0x60];
};

class BfmeObjectVirtualTail
{
public:
	unsigned char m_vt[4];
};

class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	const ThingTemplate *getTemplate() const
	{
		BfmeOverridable *t = m_template;
		if (t && t->m_nextOverride)
			t = t->m_nextOverride->friend_getFinalOverride();
		return (const ThingTemplate *)t;
	}

	Object *getContainedBy() const { return m_containedBy; }

	void updateUpgradeModules();				// ILT 0x00027FCF
	Int getNightIndicatorColor() const;			// ILT 0x0001D18D
	Int getIndicatorColor() const;				// ILT 0x00009CA0

	unsigned char m_unmodelled_70[0x1a4];
	Object *m_containedBy;						// +0x214
};

template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS *(OBJCLASS::*GetNextFunc)(void) const;

private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;

public:
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc)
		: m_cur(cur), m_getNextFunc(getNextFunc) {}

	void advance()
	{
		if (m_cur)
			m_cur = (m_cur->*m_getNextFunc)();
	}

	Bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

class Team
{
public:
	Player *getControllingPlayer() const;		// ILT 0x0002369B
	void setControllingPlayer(Player *newController);	// ILT 0x00030A21
	void deleteTeam(Bool ignoreDead);			// ILT 0x00028105
	Object *getFirstItemIn_TeamMemberList() const;	// ILT 0x0003FD41

	void setActive()
	{
		if (!m_active)
		{
			m_created = true;
			m_active = true;
		}
	}

	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_head,
			Object::dlink_next_TeamMemberList);
	}

private:
	void *m_vptr;
	void *m_proto;
	void *m_id;
	Object *m_head;								// +0x0C
	unsigned char m_unmodelled_10[0x21];
	Bool m_active;								// +0x31
	Bool m_created;								// +0x32
};

class ScriptEngine
{
public:
	virtual void _slot00() = 0;
	virtual void _slot01() = 0;
	virtual void _slot02() = 0;
	virtual void _slot03() = 0;
	virtual void _slot04() = 0;
	virtual void _slot05() = 0;
	virtual void _slot06() = 0;
	virtual void _slot07() = 0;
	virtual void _slot08() = 0;
	virtual void _slot09() = 0;
	virtual void _slot10() = 0;
	virtual void _slot11() = 0;
	virtual void _slot12() = 0;
	virtual void _slot13() = 0;
	virtual void _slot14() = 0;
	virtual void _slot15() = 0;
	virtual void _slot16() = 0;
	virtual Team *getTeamNamed(AsciiString name, Bool exact) = 0;	// +0x44
};

class Radar
{
public:
	void refreshObjectColor(void *object);		// ILT 0x00011383
};

class GlobalData
{
public:
	unsigned char m_pad00[0x218];
	Int m_timeOfDay;							// +0x218
};

enum { TIME_OF_DAY_NIGHT = 4 };

extern ScriptEngine *TheScriptEngine;
extern Radar *TheRadar;
extern GlobalData *TheWritableGlobalData;

// The out-of-line copy of updateTeamAndPlayerStuff, retail 0x002ED760.
extern int __cdecl bfmeHelper760(void *object, int userData);

static void updateTeamAndPlayerStuff(Object *obj, void *userData)
{
	if (obj)
	{
		TheRadar->refreshObjectColor(obj);
		obj->updateUpgradeModules();

		Drawable *draw = obj->getDrawable();
		if (draw)
		{
			if (TheWritableGlobalData->m_timeOfDay == TIME_OF_DAY_NIGHT)
				draw->setIndicatorColor(obj->getNightIndicatorColor());
			else
				draw->setIndicatorColor(obj->getIndicatorColor());
			draw->teamIndicatorChanged();
		}
	}
}

class ScriptActions
{
protected:
	void doMergeTeamIntoTeam(const AsciiString &teamSrcName, const AsciiString &teamDestName);
};

// ?doMergeTeamIntoTeam@ScriptActions@@IAEXABVAsciiString@@0@Z
void ScriptActions::doMergeTeamIntoTeam(const AsciiString &teamSrcName, const AsciiString &teamDestName)
{
	Team *teamSrc = TheScriptEngine->getTeamNamed(teamSrcName, false);
	Team *teamDest = TheScriptEngine->getTeamNamed(teamDestName, true);
	if (!teamSrc || !teamDest || teamSrc == teamDest)
		return;

	if (teamSrc->getControllingPlayer() != teamDest->getControllingPlayer())
		teamSrc->setControllingPlayer(teamDest->getControllingPlayer());

	Int tries = 3;
	do
	{
		DLINK_ITERATOR<Object> iter = teamSrc->iterate_TeamMemberList();
		Object *nextObj = iter.cur();

		while (!iter.done())
		{
			Object *obj = nextObj;
			if (!obj)
				break;

			// this has to be done here, setting the team will screw up the iterator. total bummer dude. jkmcd
			nextObj = iter.cur();
			iter.advance();

			Object *container = obj->getContainedBy();
			if (container && (container->getTemplate()->m_kindOfWord1 & 0x1000))
				continue;

			obj->setTeam(teamDest);
			updateTeamAndPlayerStuff(obj, 0);
		}

		if (nextObj)
		{
			nextObj->setTeam(teamDest);
			bfmeHelper760(nextObj, 0);
		}

		if (!teamSrc->getFirstItemIn_TeamMemberList())
		{
			teamSrc->deleteTeam(false);
			break;
		}
	} while (--tries > 0);

	teamDest->setActive(); // in case we just created him.
}
