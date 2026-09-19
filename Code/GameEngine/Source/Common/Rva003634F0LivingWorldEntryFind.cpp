// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport

#include <string.h>
#include <vector>

struct Rva003634F0StringData
{
	int references;
	unsigned short length;
	unsigned short capacity;
	char text[1];
};

template <typename T> class StringBase
{
	friend class BfmeSharedString;

private:
	StringBase(const StringBase<T> &other);
	~StringBase();

	Rva003634F0StringData *m_data;
};

class BfmeSharedString : private StringBase<char>
{
public:
	BfmeSharedString(const BfmeSharedString &other) : StringBase<char>(other) {}
	~BfmeSharedString() {}

	int compare(const BfmeSharedString &other) const
	{
		int otherLength = other.m_data ? other.m_data->length : 0;
		const char *otherText = other.m_data ? other.m_data->text : "";
		int thisLength = m_data ? m_data->length : 0;
		const char *thisText = m_data ? m_data->text : "";
		int length = thisLength < otherLength ? thisLength : otherLength;
		int result = memcmp(thisText, otherText, length);
		return result ? result : thisLength - otherLength;
	}

};

class Rva00361960
{
public:
	BfmeSharedString copyString();

private:
	char m_beforeString[0x10];
	BfmeSharedString m_string;
	char m_afterString[0x58 - 0x10 - sizeof(BfmeSharedString)];
};

class Rva003634F0LivingWorldEntryStore
{
public:
	int findByField10(const BfmeSharedString &key);

private:
	char m_beforeEntries[0x18];
	std::vector<Rva00361960> m_entries;
};

int Rva003634F0LivingWorldEntryStore::findByField10(
	const BfmeSharedString &key)
{
	for (unsigned int i = 0; i < m_entries.size(); ++i)
	{
		BfmeSharedString current = m_entries[i].copyString();
		if (current.compare(key) == 0)
			return i;
	}
	return -1;
}
