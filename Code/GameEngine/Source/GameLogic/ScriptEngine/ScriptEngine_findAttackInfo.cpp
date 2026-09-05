// cl: /DNDEBUG /MD
// ScriptEngine::findAttackInfo, retail 0x0033DBF0.
// ZH twin: ScriptEngine.cpp findAttackInfo. Layout from
// ScriptEngine_getAttackInfo.cpp (array at +0x1607C, count at +0x1707C).

typedef int Int;
typedef unsigned short UnsignedShort;
typedef bool Bool;

extern "C" int __cdecl memcmp(const void *left, const void *right, unsigned int count);

struct BfmeAsciiStringData
{
	UnsignedShort m_refCount;
	UnsignedShort m_numCharsAllocated;
	UnsignedShort m_numChars;
	UnsignedShort m_unreconstructed_06;
};

class AsciiString
{
public:
	~AsciiString() { releaseBuffer(); }
	void set(const AsciiString &that);

	Int getLength(void) const
	{
		return m_data ? m_data->m_numChars : 0;
	}

	const char *str(void) const
	{
		return m_data ? (const char *)(m_data + 1) : (const char *)0x0107388B;
	}

	Int compare(const AsciiString &other) const
	{
		Int lenOther = other.getLength();
		const char *pOther = other.str();
		Int lenThis = getLength();
		const char *pThis = str();
		Int shorter = lenThis < lenOther ? lenThis : lenOther;

		Int diff = memcmp(pThis, pOther, shorter);
		if (diff != 0)
			return diff;

		return lenThis - lenOther;
	}

	Bool operator==(const AsciiString &rhs) const
	{
		return compare(rhs) == 0;
	}

private:
	void releaseBuffer();
	BfmeAsciiStringData *m_data;
};

class AttackPriorityInfo
{
public:
	AsciiString getName(void) const;
	void friend_setName(const AsciiString &n) { m_name.set(n); }

	void *m_unreconstructed_00;
	AsciiString m_name;
	Int m_defaultPriority;
	void *m_priorityMap;
};

class ScriptEngine
{
public:
	AttackPriorityInfo *findAttackInfo(const AsciiString &name, Bool addIfNotFound);

private:
	unsigned char m_unreconstructed_00000[0x1607C];
	AttackPriorityInfo m_attackPriorityInfo[256];
	Int m_numAttackInfo;
};

AttackPriorityInfo *ScriptEngine::findAttackInfo(const AsciiString &name, Bool addIfNotFound)
{
	Int i;
	for (i = 1; i < m_numAttackInfo; i++)
	{
		if (m_attackPriorityInfo[i].getName() == name)
			return &m_attackPriorityInfo[i];
	}
	if (addIfNotFound && m_numAttackInfo < 256)
	{
		m_attackPriorityInfo[m_numAttackInfo].friend_setName(name);
		m_numAttackInfo++;
		return &m_attackPriorityInfo[m_numAttackInfo - 1];
	}
	return 0;
}
