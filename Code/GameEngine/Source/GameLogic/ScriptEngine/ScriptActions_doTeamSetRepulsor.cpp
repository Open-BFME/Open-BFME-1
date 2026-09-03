// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/objectdlink
// stlport
// readable body of ?doTeamSetRepulsor@ScriptActions@@IAEXABVAsciiString@@_N@Z: Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions.cpp
// Open-BFME: ScriptActions::doTeamSetRepulsor, retail 0x002FD570, 128 bytes.
//
// Team-member walk via Object's virtually-inherited DLINK PMF
// {pfn=0x00401140, delta=-100, vbindex=0}. Layout from ObjectDlinkPmf.h.

#define _STLP_NO_EXCEPTIONS 1
#include <bitset>

// Object skeleton copied from reference/shims/objectdlink/ObjectDlinkPmf.h
// so setStatus can be declared on Object (matched name at 0x001C7370).
class Object;

class BfmeObjectVirtualTail { public: unsigned char m_vt[4]; };

class BfmeObjectVbptrCarrier : public virtual BfmeObjectVirtualTail
{
public:
	unsigned char m_carrier[4];
};

class BfmeObjectVtbl { public: virtual void bfmeObjectSlot0( void ); };

class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList( void ) const;
};

class BfmeObjectDlinkPad { public: unsigned char m_pad[0x64]; };

template<int NUMBITS> class BitFlags;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	unsigned char m_tail[0x40];
	void setStatus(const BitFlags<86> &objectStatus, bool set = true);
};

typedef Object *(Object::*BfmeGetNextTeamMemberFunc)( void ) const;

typedef int Int;
typedef bool Bool;

enum ObjectStatusTypes
{
	OBJECT_STATUS_REPULSOR = 8
};

template<int NUMBITS>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BitFlags.h
class BitFlags
{
public:
	enum _dummy_kInit { kInit };

	BitFlags(_dummy_kInit, Int idx1)
	{
		m_bits.set(idx1);
	}

	BitFlags() { }

private:
	_STL::bitset<NUMBITS>	m_bits;
};

typedef BitFlags<86> ObjectStatusMaskType;

#define MAKE_OBJECT_STATUS_MASK(k) ObjectStatusMaskType(ObjectStatusMaskType::kInit, (k))

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
	char *m_data;
};

class BfmeStringArgBase
{
	friend class BfmeAsciiStringArg;

private:
	BfmeStringArgBase(const BfmeStringArgBase &);
	~BfmeStringArgBase();
};

class BfmeAsciiStringArg
{
public:
	BfmeAsciiStringArg(const AsciiString &that)
	{
		((BfmeStringArgBase *)this)->BfmeStringArgBase::BfmeStringArgBase(
			*(const BfmeStringArgBase *)&that);
	}
	~BfmeAsciiStringArg();

private:
	char *m_text;
};

// setStatus lives on Object so the reloc names the matched
// ?setStatus@Object@@QAEXABV?$BitFlags@$0FG@@@_N@Z at 0x001C7370.

#define callMemberFunction(object,ptrToMember)  ((object).*(ptrToMember))

template<class OBJCLASS>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameCommon.h
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
		return m_cur == NULL;
	}

	OBJCLASS* cur() const
	{
		return m_cur;
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Team.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	virtual void _se_0() = 0;
	virtual void _se_1() = 0;
	virtual void _se_2() = 0;
	virtual void _se_3() = 0;
	virtual void _se_4() = 0;
	virtual void _se_5() = 0;
	virtual void _se_6() = 0;
	virtual void _se_7() = 0;
	virtual void _se_8() = 0;
	virtual void _se_9() = 0;
	virtual void _se_10() = 0;
	virtual void _se_11() = 0;
	virtual void _se_12() = 0;
	virtual void _se_13() = 0;
	virtual void _se_14() = 0;
	virtual void _se_15() = 0;
	virtual void _se_16() = 0;
	virtual Team *getTeamNamed(BfmeAsciiStringArg, Bool) = 0;
};

extern ScriptEngine *TheScriptEngine;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptActions.h
class ScriptActions
{
protected:
	void doTeamSetRepulsor(const AsciiString& teamName, Bool repulsor);
};

void ScriptActions::doTeamSetRepulsor(const AsciiString& teamName, Bool repulsor)
{
	Team *theSrcTeam = TheScriptEngine->getTeamNamed(teamName, false);
	if (!theSrcTeam) {
		return;
	}

	if (theSrcTeam)
	{
		for (DLINK_ITERATOR<Object> iter = theSrcTeam->iterate_TeamMemberList(); !iter.done(); iter.advance())
		{
			Object *obj = iter.cur();
			if (!obj)
			{
				continue;
			}
			obj->setStatus(
				MAKE_OBJECT_STATUS_MASK(OBJECT_STATUS_REPULSOR), repulsor);
		}
	}
}
