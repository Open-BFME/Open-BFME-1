// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/objectdlink
// stlport
//
// BFME's TEAM_STAND_GROUND action.  executeAction jump-table arm 500 passes
// the team and boolean ScriptActionParameter objects directly to this helper.

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>
#include <list>
#include "../../../../../reference/shims/stringinline/StringInline.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum KindOfType
{
	KINDOF_HORDE = 108
};

enum ObjectStatusTypes
{
	OBJECT_STATUS_STAND_GROUND = 67
};

template<int NUMBITS>
class BitFlags
{
public:
	enum _dummy_kInit { kInit };

	BitFlags(_dummy_kInit, Int idx1)
	{
		m_bits.set(idx1);
	}

private:
	_STL::bitset<NUMBITS> m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

#define MAKE_OBJECT_STATUS_MASK(k) ObjectStatusMaskType(ObjectStatusMaskType::kInit, (k))

class ScriptActionParameter
{
public:
	unsigned char m_beforeString[0x10];
	AsciiString m_string;

	Int getInt() const
	{
		return *(const Int *)((const unsigned char *)this + 8);
	}
};

class Object;

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

class Overridable
{
public:
	virtual ~Overridable();
	const Overridable *getFinalOverride() const;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
public:
	Bool isKindOf(KindOfType kind) const
	{
		return (m_kindOf[(UnsignedInt)kind >> 5]
			& (1u << ((UnsignedInt)kind & 31))) != 0;
	}

private:
	unsigned char m_beforeKindOf[0xc8 - 8];
	UnsignedInt m_kindOf[6];
};

class Thing
{
public:
	Bool isKindOf(KindOfType kind) const
	{
		const ThingTemplate *thingTemplate = m_template;
		if (thingTemplate == 0)
		{
			thingTemplate = 0;
		}
		else if (thingTemplate->m_nextOverride != 0)
			thingTemplate = reinterpret_cast<const ThingTemplate *>(
				thingTemplate->m_nextOverride->getFinalOverride());
		return thingTemplate->isKindOf(kind);
	}

protected:
	virtual ~Thing();
	const ThingTemplate *m_template;
};

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	unsigned char m_tail[0x194];
	void setStatus(const BitFlags<86> &objectStatus, bool set = true);
	void *unidentified_001BFE20() const;

};

typedef Object *(Object::*BfmeGetNextTeamMemberFunc)(void) const;

#define callMemberFunction(object,ptrToMember) ((object).*(ptrToMember))

template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS *(OBJCLASS::*GetNextFunc)() const;

private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;

public:
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc)
		: m_cur(cur), m_getNextFunc(getNextFunc) { }

	void advance()
	{
		if (m_cur)
			m_cur = callMemberFunction(*m_cur, m_getNextFunc)();
	}

	Bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};

class Team
{
public:
	Object *m_unmodelled0;
	Object *m_unmodelled1;
	Object *m_unmodelled2;
	Object *m_head;

	DLINK_ITERATOR<Object> iterate_TeamMemberList() const
	{
		return DLINK_ITERATOR<Object>(m_head, Object::dlink_next_TeamMemberList);
	}
};

class BfmeHordeContainInterface
{
public:
#define HORDE_SLOT(N) virtual void _horde_slot_##N() = 0
	HORDE_SLOT(00); HORDE_SLOT(01); HORDE_SLOT(02); HORDE_SLOT(03);
	HORDE_SLOT(04); HORDE_SLOT(05); HORDE_SLOT(06); HORDE_SLOT(07);
	HORDE_SLOT(08); HORDE_SLOT(09); HORDE_SLOT(10); HORDE_SLOT(11);
	HORDE_SLOT(12); HORDE_SLOT(13); HORDE_SLOT(14); HORDE_SLOT(15);
	HORDE_SLOT(16); HORDE_SLOT(17); HORDE_SLOT(18); HORDE_SLOT(19);
	HORDE_SLOT(20); HORDE_SLOT(21); HORDE_SLOT(22); HORDE_SLOT(23);
	HORDE_SLOT(24); HORDE_SLOT(25); HORDE_SLOT(26); HORDE_SLOT(27);
	HORDE_SLOT(28); HORDE_SLOT(29); HORDE_SLOT(30); HORDE_SLOT(31);
	HORDE_SLOT(32); HORDE_SLOT(33); HORDE_SLOT(34); HORDE_SLOT(35);
	HORDE_SLOT(36); HORDE_SLOT(37); HORDE_SLOT(38); HORDE_SLOT(39);
	HORDE_SLOT(40); HORDE_SLOT(41); HORDE_SLOT(42); HORDE_SLOT(43);
	HORDE_SLOT(44); HORDE_SLOT(45); HORDE_SLOT(46); HORDE_SLOT(47);
	HORDE_SLOT(48); HORDE_SLOT(49); HORDE_SLOT(50); HORDE_SLOT(51);
	HORDE_SLOT(52); HORDE_SLOT(53); HORDE_SLOT(54); HORDE_SLOT(55);
	HORDE_SLOT(56); HORDE_SLOT(57); HORDE_SLOT(58); HORDE_SLOT(59);
#undef HORDE_SLOT
	virtual void getMembers(_STL::list<Object *> *members) = 0;
};

class BfmeObjectList : public _STL::list<Object *>
{
public:
	~BfmeObjectList();
};

class ScriptEngine
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
	virtual void slot16() = 0;
	virtual Team *getTeamNamed(AsciiString name, Bool exact) = 0;
};

extern ScriptEngine *TheScriptEngine;

class ScriptActions
{
protected:
	void doTeamStandGround(ScriptActionParameter *teamParameter,
		ScriptActionParameter *standGroundParameter);
};

void ScriptActions::doTeamStandGround(ScriptActionParameter *teamParameter,
	ScriptActionParameter *standGroundParameter)
{
	Team *team = TheScriptEngine->getTeamNamed(teamParameter->m_string, false);
	if (team == 0)
		return;

	for (DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList();
		!iter.done(); iter.advance())
	{
		Object *object = iter.cur();
		if (object == 0)
			continue;

		object->setStatus(MAKE_OBJECT_STATUS_MASK(OBJECT_STATUS_STAND_GROUND),
			standGroundParameter->getInt() != 0);

		if (((Thing *)object)->isKindOf(KINDOF_HORDE))
		{
			BfmeHordeContainInterface *horde =
				(BfmeHordeContainInterface *)object->unidentified_001BFE20();
			if (horde != 0)
			{
				BfmeObjectList members;
				horde->getMembers((_STL::list<Object *> *)&members);
				for (_STL::list<Object *>::iterator member = members.begin();
					member != members.end(); ++member)
				{
					Object *hordeMember = *member;
					hordeMember->setStatus(
						MAKE_OBJECT_STATUS_MASK(OBJECT_STATUS_STAND_GROUND),
						standGroundParameter->getInt() != 0);
				}
			}
		}
	}
}
