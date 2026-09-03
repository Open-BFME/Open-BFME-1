// cl: /DNDEBUG /MD /EHsc

extern "C" int __cdecl memcmp(const void *left, const void *right,
	unsigned int count);
#pragma intrinsic(memcmp)

template <class T> struct StringData
{
	int m_refs;
	unsigned short m_length;
	unsigned short m_capacity;
	T m_text[1];
};

template <class T> class StringBase
{
protected:
	StringBase(const StringBase &other);
	~StringBase();
	StringData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	int compare(const AsciiString &other) const
	{
		int otherLength = other.m_data ? other.m_data->m_length : 0;
		const char *otherText = other.m_data ? other.m_data->m_text : "";
		int thisLength = m_data ? m_data->m_length : 0;
		const char *thisText = m_data ? m_data->m_text : "";
		int length = thisLength < otherLength ? thisLength : otherLength;
		int result = memcmp(thisText, otherText, length);
		if (result != 0)
			return result;
		return thisLength - otherLength;
	}
};

class Parameter
{
public:
	int getInt() const { return m_integer; }
	const AsciiString &getString() const { return m_string; }

private:
	char m_unknown[8];
	int m_integer;
	float m_real;
	AsciiString m_string;
};

class Condition
{
public:
	Parameter *getParameter(int index)
	{
		if (index >= 0 && index < m_parameterCount)
			return m_parameters[index];
		return 0;
	}

private:
	char m_unknown[8];
	int m_parameterCount;
	Parameter *m_parameters[12];
};

struct FlagInteractionNode
{
	FlagInteractionNode *m_next;
	FlagInteractionNode *m_previous;
	AsciiString m_name;
};

struct FlagInteractionList
{
	FlagInteractionNode *m_header;
};

class ScriptEngine
{
protected:
	bool *bfmeFlagForWrite(AsciiString name);
	bool evaluateFlag(Condition *condition);

private:
	char m_unknown[0x17270];
	FlagInteractionList m_uiInteractions;
};

bool ScriptEngine::evaluateFlag(Condition *condition)
{
	bool *flag = bfmeFlagForWrite(
		condition->getParameter(0)->getString());
	bool desired = condition->getParameter(1)->getInt() != 0;
	bool actual = *flag != 0;
	if (desired == actual)
		return true;

	FlagInteractionNode *header = m_uiInteractions.m_header;
	for (FlagInteractionNode *node = header->m_next;
		node != header; node = node->m_next)
	{
		if (node->m_name.compare(
			condition->getParameter(0)->getString()) == 0)
		{
			return true;
		}
	}
	return false;
}
