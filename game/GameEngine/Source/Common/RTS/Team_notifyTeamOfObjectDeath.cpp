// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// Retail 0x000EE7F0, Team::notifyTeamOfObjectDeath(Object *), 279 bytes
// (ret 4 at +0x114).
// Identity: Object::onDie (0x001CEFC0 +0x44D) loads ECX from Object+0x23C and
// calls ILT 0x00030AA3 with the dying Object; tools/ilt_oracle.py confirms
// ?notifyTeamOfObjectDeath@Team@@QAEXPAVObject@@@Z exactly at that ILT.
// Zero Hour twin Team::notifyTeamOfObjectDeath() in GeneralsMD Team.cpp; BFME
// adds the Object argument and, once no member of the team is alive with an
// AI, raises Lua event 7 with a stack DelayedLuaEventList (the
// GameLogic::sendObjectCreated pattern). runScript takes the team name first,
// as in the matched Team::updateState. Layout evidence:
// targets/game/reverse/identity_evidence/000ee7f0-event-lifetime.md.

#include "ascii_string.h"

#include "../../../Include/Common/ScalarTypes.h"


template <> inline bool StringBase<char>::isEmpty() const
{
	if (m_data == 0)
		return true;
	if (m_data->length == 0)
		return true;
	return false;
}

class Team;

class BfmeObjectDlinkObject;

class BfmeObjectVirtualTail { public: unsigned char m_vt[4]; };

class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};

class BfmeObjectVtbl { public: virtual void bfmeObjectSlot0(); };

class BfmeObjectDlinkBase
{
public:
	BfmeObjectDlinkObject *dlink_next_TeamMemberList() const;
};

class BfmeObjectDlinkPad
{
public:
	unsigned char m_pad[0x64];
};

class BfmeObjectDlinkObject : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	unsigned char m_tail[0x40];
};

typedef BfmeObjectDlinkObject *(BfmeObjectDlinkObject::*BfmeGetNextTeamMemberFunc)() const;

template <class ObjectType> class BfmeDlinkIterator
{
public:
	BfmeDlinkIterator(ObjectType *cur, BfmeGetNextTeamMemberFunc getNext)
		: m_cur(cur), m_getNext(getNext) { }

	Bool done() const { return m_cur == 0; }
	ObjectType *cur() const { return m_cur; }

	void advance()
	{
		if (m_cur)
			m_cur = (m_cur->*m_getNext)();
	}

private:
	ObjectType *m_cur;
	BfmeGetNextTeamMemberFunc m_getNext;
};

class AIUpdateInterface;

class Object : public BfmeObjectDlinkObject
{
public:
	AIUpdateInterface *getAIUpdateInterface() const
	{
		return *(AIUpdateInterface *const *)((const char *)this + 0x204);
	}

	Bool isEffectivelyDead() const
	{
		return (*(const unsigned char *)((const char *)this + 0x344) & 1) != 0;
	}
};

class BfmeDelayedLuaEvent {
public:
	BfmeDelayedLuaEvent();
	~BfmeDelayedLuaEvent();
	char data[0x18];
};

// Same view as GameLogicSendObjectCreated.cpp: ctor 0x000EDBB0, inline
// cleanup through the eh vector destructor iterator and base vtable 01073744
// (the Snapshot base vtable; dir32 records it as ??_7BfmeSnapshotBase@@6B@).
class BfmeSnapshotBase {
public:
	virtual ~BfmeSnapshotBase() {}
};
class __declspec(novtable) DelayedLuaEventList : public BfmeSnapshotBase {
public:
	DelayedLuaEventList();
	__forceinline ~DelayedLuaEventList() {}
	BfmeDelayedLuaEvent events[3];
};

class BfmeOwnerBR {
public:
	void bfmeGo939B(int, Object *, DelayedLuaEventList *);
};
class LuaScriptEngine;
extern LuaScriptEngine *TheLuaScriptEngine;

class ScriptEngine
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14();
	// slot 15, +0x3C; BFME passes the running team's name first
	virtual void runScript(const AsciiString &teamName, const AsciiString &scriptName, Team *pThisTeam);
};

extern ScriptEngine *TheScriptEngine;

// The shared empty AsciiString the nullable team-name accessor falls back on.
extern const AsciiString Rva01336E50EmptyString;

// TeamTemplateInfo at TeamPrototype+0x12C (see Team_updateState.cpp).
struct BfmeTeamTemplateInfoView
{
	unsigned char m_unmodelled_000[0x84];
	AsciiString m_scriptOnUnitDestroyed;				// +0x84
};

class TeamPrototype
{
public:
	const AsciiString &getName() const { return m_name; }
	const BfmeTeamTemplateInfoView *getTemplateInfo() const
	{
		return (const BfmeTeamTemplateInfoView *)((const char *)this + 0x12c);
	}

	unsigned char m_unmodelled_000[0x10];
	AsciiString m_name;						// +0x10
};

class Team
{
public:
	void notifyTeamOfObjectDeath(Object *obj);

	const AsciiString &getName() const
	{
		if (!m_proto)
			return Rva01336E50EmptyString;
		return m_proto->getName();
	}

	BfmeDlinkIterator<BfmeObjectDlinkObject> iterate_TeamMemberList() const
	{
		return BfmeDlinkIterator<BfmeObjectDlinkObject>(m_memberList, BfmeObjectDlinkBase::dlink_next_TeamMemberList);
	}

	void *m_vptr;
	TeamPrototype *m_proto;						// +0x04
	unsigned int m_id;						// +0x08
	BfmeObjectDlinkObject *m_memberList;				// +0x0C
};

// ?notifyTeamOfObjectDeath@Team@@QAEXPAVObject@@@Z
void Team::notifyTeamOfObjectDeath(Object *obj)
{
	if (!m_proto)
		return;
	const BfmeTeamTemplateInfoView *pInfo = m_proto->getTemplateInfo();
	if (!pInfo)
		return;

	Bool anyAlive = false;
	for (BfmeDlinkIterator<BfmeObjectDlinkObject> iter = iterate_TeamMemberList();
		!iter.done(); iter.advance())
	{
		Object *member = (Object *)iter.cur();
		if (!member->isEffectivelyDead() && member->getAIUpdateInterface())
		{
			anyAlive = true;
			break;
		}
	}

	if (!anyAlive)
	{
		DelayedLuaEventList events;
		reinterpret_cast<BfmeOwnerBR *>(TheLuaScriptEngine)->bfmeGo939B(7, obj, &events);
	}

	if (pInfo->m_scriptOnUnitDestroyed.isEmpty())
		return;

	TheScriptEngine->runScript(getName(), pInfo->m_scriptOnUnitDestroyed, this);
}
