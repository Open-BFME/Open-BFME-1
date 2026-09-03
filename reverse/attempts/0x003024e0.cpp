// target experiment for ?doTeamSetUnmanned@ScriptActions@@IAEXABVAsciiString@@@Z
// partial score=0.50 date=2026-09-03

#define _STLP_NO_EXCEPTIONS 1

typedef int Int;
typedef bool Bool;

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

class BfmeInnerRQ
{
public:
	void bfmeSetRQ(Int object, Int commandSource);
};

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	unsigned char m_tail[0x194];
};

class AIUpdateInterface;

typedef Object *(Object::*BfmeGetNextTeamMemberFunc)(void) const;

#define callMemberFunction(object,ptrToMember) ((object).*(ptrToMember))

template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
	typedef OBJCLASS* (OBJCLASS::*GetNextFunc)() const;

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

class ScriptEngine
{
public:
	virtual void _se_0(void) = 0;
	virtual void _se_1(void) = 0;
	virtual void _se_2(void) = 0;
	virtual void _se_3(void) = 0;
	virtual void _se_4(void) = 0;
	virtual void _se_5(void) = 0;
	virtual void _se_6(void) = 0;
	virtual void _se_7(void) = 0;
	virtual void _se_8(void) = 0;
	virtual void _se_9(void) = 0;
	virtual void _se_10(void) = 0;
	virtual void _se_11(void) = 0;
	virtual void _se_12(void) = 0;
	virtual void _se_13(void) = 0;
	virtual void _se_14(void) = 0;
	virtual void _se_15(void) = 0;
	virtual void _se_16(void) = 0;
	virtual Team *getTeamNamed(BfmeAsciiStringArg, Bool) = 0;
};

extern ScriptEngine *TheScriptEngine;

class ScriptActions
{
protected:
	void doTeamSetUnmanned(const AsciiString &teamName);
};

void ScriptActions::doTeamSetUnmanned(const AsciiString &teamName)
{
	Team *team = TheScriptEngine->getTeamNamed(teamName, false);
	if (!team)
		return;

	for (DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList();
		!iter.done(); iter.advance())
	{
		Object *obj = iter.cur();
		if (obj)
		{
			AIUpdateInterface *ai = *(AIUpdateInterface **)(
				reinterpret_cast<unsigned char *>(obj) + 0x204);
			if (ai != 0)
			{
				BfmeInnerRQ *command = reinterpret_cast<BfmeInnerRQ *>(
					reinterpret_cast<unsigned char *>(ai) + 0x20);
				command->bfmeSetRQ(0, 1);
			}
		}
	}
}
