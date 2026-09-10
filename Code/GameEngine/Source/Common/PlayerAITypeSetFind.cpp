// cl: /O2 /EHsc

extern "C" int __cdecl memcmp(const void *left, const void *right,
	unsigned int count);
#pragma intrinsic(memcmp)

struct BfmeAsciiStringData
{
	int m_references;
	unsigned short m_length;
	unsigned short m_capacity;
	char m_text[1];
};

class AsciiString
{
public:
	int compare(const AsciiString &other) const
	{
		int otherLength = other.m_data ? other.m_data->m_length : 0;
		const char *otherText = other.m_data ? other.m_data->m_text : (const char *)0x0107388b;
		int thisLength = m_data ? m_data->m_length : 0;
		const char *thisText = m_data ? m_data->m_text : (const char *)0x0107388b;
		int difference = memcmp(thisText, otherText,
			thisLength < otherLength ? thisLength : otherLength);
		if (difference != 0)
			return difference;
		return thisLength - otherLength;
	}

	BfmeAsciiStringData *m_data;
};

class SubsystemInterface
{
private:
	void *m_vtable;
	AsciiString m_name;
};

struct PlayerAITypeEntry
{
	AsciiString m_name;
	char m_rest[12];
};

class PlayerAITypeVector
{
public:
	unsigned int size() const
	{
		return (unsigned int)(m_end - m_begin);
	}

	PlayerAITypeEntry &operator[](unsigned int index) const
	{
		return m_begin[index];
	}

	PlayerAITypeEntry *m_begin;
	PlayerAITypeEntry *m_end;
	PlayerAITypeEntry *m_capacity;
};

class PlayerAITypeSet : public SubsystemInterface
{
public:
	int find(AsciiString *name);

private:
	PlayerAITypeVector m_types;
};

int PlayerAITypeSet::find(AsciiString *name)
{
	PlayerAITypeSet *self = this;
	int index = 0;
	for (; (unsigned int)index < self->m_types.size(); ++index)
	{
		if (self->m_types[index].m_name.compare(*name) == 0)
			return index;
	}
	return -1;
}
