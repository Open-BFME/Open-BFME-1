// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/objectdlink /Ireference/shims/stringinline
// ScriptConditions body at 0x00328470, 228 bytes.
// Address-derived condition name: team member visibility against a player mask.
// The helper at1CAEE0 reads the viewer at+2C; this caller supplies Player*,
// so use that actual argument type rather than the legacy Object* declaration.
// Shroud status helper1C7B30 and mask iteration DF4A0 are matched separately.

#include "StringInline.h"

typedef bool Bool;
typedef unsigned short UnsignedShort;

class Object;
class Player;

class BfmeObjectVirtualTail { public: unsigned char m_vt[4]; };

class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};

class BfmeObjectVtbl { public: virtual void bfmeObjectSlot0(void); };

class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList(void) const;
};

class BfmeObjectDlinkPad { public: unsigned char m_pad[0x64]; };

enum ObjectShroudStatus
{
	OBJECTSHROUD_INVALID = 0,
	OBJECTSHROUD_CLEAR,
	OBJECTSHROUD_FOGGED,
	OBJECTSHROUD_SHROUDED
};

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	unsigned char m_tail[0x40];
	Bool queryRva001CAEE0(const Player *viewer) const;
	ObjectShroudStatus getShroudedStatus(int playerIndex) const;
};

typedef Object *(Object::*BfmeGetNextTeamMemberFunc)(void) const;

#define callMemberFunction(object,ptrToMember)  ((object).*(ptrToMember))

template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS* (OBJCLASS::*GetNextFunc)() const;
private:
	OBJCLASS* m_cur;
	GetNextFunc m_getNextFunc;
public:
	DLINK_ITERATOR(OBJCLASS* cur, GetNextFunc getNextFunc) : m_cur(cur), m_getNextFunc(getNextFunc)
	{
	}

	void advance()
	{
		if (m_cur)
			m_cur = callMemberFunction(*m_cur, m_getNextFunc)();
	}

	Bool done() const
	{
		return m_cur == 0;
	}

	OBJCLASS* cur() const
	{
		return m_cur;
	}
};

class Parameter
{
public:
	const AsciiString &getString(void) const { return m_string; }

private:
	unsigned char m_beforeString[0x10];
	AsciiString m_string;
};

class Player
{
public:
	unsigned char m_beforeIndex[0x24];
	int m_playerIndex;
};

class Team
{
public:
	void *m_vptr;
	void *m_proto;
	void *m_id;
	Object *m_head;

	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_head, Object::dlink_next_TeamMemberList);
	}
};

class PlayerList
{
public:
	Player *getEachPlayerFromMask(UnsignedShort &mask);
};

class ScriptEngine
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
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual Team *getTeamNamed(AsciiString, Bool) = 0;
	UnsignedShort unidentified_0034DB40(Parameter *);
};

struct ObjectFlagView
{
	unsigned char m_beforeFlag[0x1a4];
	int m_flags;
};

extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;

class ScriptConditions
{
protected:
	Bool evaluateRva00328470(Parameter *, Parameter *);
};

// ?evaluateRva00328470@ScriptConditions@@IAE_NPAVParameter@@0@Z
Bool ScriptConditions::evaluateRva00328470(
	Parameter *pTeamParm, Parameter *pPlayerParm)
{
	Team *theTeam = TheScriptEngine->getTeamNamed(pTeamParm->getString(), false);
	if (!theTeam)
		return false;

	UnsignedShort mask = TheScriptEngine->unidentified_0034DB40(pPlayerParm);
	DLINK_ITERATOR<Object> it = theTeam->iterate_TeamMemberList();
	for (; !it.done(); it.advance()) {
		Object *obj = it.cur();
		if (((ObjectFlagView *)obj)->m_flags & 8)
			continue;
		UnsignedShort working = mask;
		while (working) {
			Player *player = ThePlayerList->getEachPlayerFromMask(working);
			if (!obj->queryRva001CAEE0(player)) {
				int idx = player->m_playerIndex;
				ObjectShroudStatus k = obj->getShroudedStatus(idx);
				if (k == OBJECTSHROUD_CLEAR || k == OBJECTSHROUD_FOGGED)
					return true;
			}
		}
	}

	return false;
}
