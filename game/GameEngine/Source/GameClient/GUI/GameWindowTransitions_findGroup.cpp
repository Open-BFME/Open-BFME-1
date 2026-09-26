// cl: /DNDEBUG /DWIN32 /MD /EHsc
// GameWindowTransitionsHandler::findGroup. ZH twin with BFME string layout
// and inlined compareNoCase (ControlBarScheme_find donor).

typedef int Int;
typedef unsigned short UnsignedShort;

extern "C" __declspec(dllimport) int __cdecl _memicmp(const void *buf1, const void *buf2, unsigned int count);

template <typename T> class StringBase
{
friend class AsciiString;
private:
	StringBase(const StringBase<T> &other);
	void releaseBuffer(void);
};

struct BfmeAsciiStringData
{
	UnsignedShort m_refCount;
	UnsignedShort m_numCharsAllocated;
	UnsignedShort m_len;
	UnsignedShort m_pad;
};

class AsciiString
{
public:
	AsciiString(const AsciiString &other)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&other);
	}
	~AsciiString()
	{
		((StringBase<char> *)this)->StringBase<char>::releaseBuffer();
	}
	bool isEmpty(void) const
	{
		return m_data == 0 || *(UnsignedShort *)(m_data + 4) == 0;
	}
	Int getLength(void) const
	{
		return m_data ? ((BfmeAsciiStringData *)m_data)->m_len : 0;
	}
	const char *str(void) const
	{
		return m_data ? m_data + 8 : "";
	}
	Int compareNoCase(const AsciiString &other) const
	{
		Int lenOther = other.getLength();
		const char *pOther = other.str();
		Int lenThis = getLength();
		const char *pThis = str();
		Int shorter = lenThis < lenOther ? lenThis : lenOther;
		Int diff = _memicmp(pThis, pOther, shorter);
		if (diff != 0)
			return diff;
		return lenThis - lenOther;
	}
private:
	char *m_data;
};

class TransitionGroup
{
public:
	AsciiString getName(void);
};

struct TransitionGroupNode
{
	TransitionGroupNode *m_next;
	TransitionGroupNode *m_previous;
	TransitionGroup *m_value;
};

class GameWindowTransitionsHandler
{
public:
	TransitionGroup *findGroup(AsciiString groupName);
private:
	char m_pad[0x1C];
	TransitionGroupNode *m_groupHead;
};

TransitionGroup *GameWindowTransitionsHandler::findGroup(AsciiString groupName)
{
	GameWindowTransitionsHandler *self = this;
	if (groupName.isEmpty())
		return 0;

	TransitionGroupNode *head = self->m_groupHead;
	for (TransitionGroupNode *node = head->m_next; node != self->m_groupHead; node = node->m_next)
	{
		TransitionGroup *g = node->m_value;
		if (groupName.compareNoCase(g->getName()) == 0)
			return g;
	}
	return 0;
}
