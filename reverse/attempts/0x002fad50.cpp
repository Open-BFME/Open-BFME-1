// ?doTeamSetModelConditionForDuration@ScriptActions@@IAEXABVAsciiString@@0MH@Z
// partial score=0.9 date=2026-09-06
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/objectdlink
// Open-BFME: TEAM_SET_MODELCONDITION_FOR_DURATION at retail RVA 0x002FAD50.

extern "C" int __cdecl memcmp(const void *, const void *, unsigned int);
#pragma intrinsic(memcmp)

typedef bool Bool;
typedef int Int;
typedef float Real;

template <typename T> struct BfmeStringData
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();

	public:
	__forceinline int compare(const StringBase<T> &other) const
	{
		const int length = other.m_data ? other.m_data->m_length : 0;
		const char *data = other.m_data ? other.m_data->m_text : "";
		const int myLength = m_data ? m_data->m_length : 0;
		const char *myData = m_data ? m_data->m_text : "";
		int result = memcmp(myData, data,
			myLength < length ? myLength : length);
		if (result == 0)
			result = myLength - length;
		return result;
	}

	private:
	BfmeStringData<T> *m_data;
};

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	AsciiString(const char *text)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(text);
	}
	AsciiString(const AsciiString &other)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&other);
	}
	~AsciiString()
	{
		((StringBase<char> *)this)->StringBase<char>::~StringBase();
	}

	int getLength() const
	{
		return m_data ? m_data->m_length : 0;
	}

	const char *str() const
	{
		return m_data ? m_data->m_text : "";
	}

	int compare(const AsciiString &other) const
	{
		int otherLength = other.m_data ? other.m_data->m_length : 0;
		const char *otherText = other.m_data ? other.m_data->m_text : "";
		int thisLength = m_data ? m_data->m_length : 0;
		const char *thisText = m_data ? m_data->m_text : "";
		int result = memcmp(thisText, otherText,
			thisLength < otherLength ? thisLength : otherLength);
		if (result == 0)
			result = thisLength - otherLength;
		return result;
	}

	friend __forceinline bool operator==(const AsciiString &left, const AsciiString &right)
	{
		return left.compare(right) == 0;
	}

private:
	BfmeStringData<char> *m_data;
};

class BfmeStringArgBase
{
	friend class BfmeAsciiStringArg;

private:
	BfmeStringArgBase(const BfmeStringArgBase &other);
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

class BfmeItemRY
{
public:
	void bfmeDoRY(void *condition, void *frames);
};

class Object;

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

class BfmeObjectVtbl
{
public:
	virtual void bfmeObjectSlot0(void);
};

class BfmeObjectDlinkBase
{
public:
	Object *dlink_next_TeamMemberList(void) const;
};

class BfmeObjectDlinkPad
{
public:
	unsigned char m_pad[0x64];
};

class Object : public BfmeObjectVtbl, public BfmeObjectDlinkBase,
	public BfmeObjectDlinkPad, public BfmeObjectVbptrCarrier
{
public:
	unsigned char m_tail[0x40];
};

typedef Object *(Object::*BfmeGetNextTeamMemberFunc)(void) const;

#define callMemberFunction(object, ptrToMember) ((object).*(ptrToMember))

template <class OBJCLASS> class DLINK_ITERATOR
{
public:
	typedef OBJCLASS *(OBJCLASS::*GetNextFunc)(void) const;

private:
	OBJCLASS *m_cur;
	GetNextFunc m_getNextFunc;

public:
	DLINK_ITERATOR() {}
	DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc)
		: m_cur(cur), m_getNextFunc(getNextFunc) {}

	void advance()
	{
		if (m_cur)
			m_cur = callMemberFunction(*m_cur, m_getNextFunc)();
	}

	Bool done() const
	{
		return m_cur == 0;
	}

	OBJCLASS *cur() const
	{
		return m_cur;
	}
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
		return DLINK_ITERATOR<Object>(m_head,
			Object::dlink_next_TeamMemberList);
	}
};

class ScriptEngine
{
public:
	virtual void _se0() = 0;
	virtual void _se1() = 0;
	virtual void _se2() = 0;
	virtual void _se3() = 0;
	virtual void _se4() = 0;
	virtual void _se5() = 0;
	virtual void _se6() = 0;
	virtual void _se7() = 0;
	virtual void _se8() = 0;
	virtual void _se9() = 0;
	virtual void _se10() = 0;
	virtual void _se11() = 0;
	virtual void _se12() = 0;
	virtual void _se13() = 0;
	virtual void _se14() = 0;
	virtual void _se15() = 0;
	virtual void _se16() = 0;
	virtual Team *getTeamNamed(BfmeAsciiStringArg name, Bool exact) = 0;
};

extern ScriptEngine *TheScriptEngine;
extern "C" const char *bfmeGlobalTable12A6918[];

class ScriptActions
{
protected:
	void doTeamSetModelConditionForDuration(
		const AsciiString &teamName, const AsciiString &conditionName,
		Real duration, Int percent);
};

void ScriptActions::doTeamSetModelConditionForDuration(
	const AsciiString &teamName, const AsciiString &conditionName,
	Real duration, Int percent)
{
	Int condition;
	DLINK_ITERATOR<Object> iter;
	Team *theTeam = TheScriptEngine->getTeamNamed(teamName, false);
	if (!theTeam)
		return;

	condition = 0;
	for (; condition < 0x130; ++condition)
	{
		AsciiString name(bfmeGlobalTable12A6918[condition]);
		if (((const StringBase<char> *)&conditionName)->compare(
			*(const StringBase<char> *)&name) == 0)
			break;
	}
	if (condition == 0x130)
		return;

	#define LOGICFRAMES_PER_SECOND (*(const Real *)0x01075344)
	Int frames = (Int)(duration * LOGICFRAMES_PER_SECOND);
	iter = theTeam->iterate_TeamMemberList();
	while (!iter.done())
	{
		Object *obj = iter.cur();
		((BfmeItemRY *)obj)->bfmeDoRY((void *)condition, (void *)frames);
		iter.advance();
	}
}
