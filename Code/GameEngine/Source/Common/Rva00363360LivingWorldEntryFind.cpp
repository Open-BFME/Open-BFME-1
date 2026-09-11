// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
//
// Retail RVA 0x00363360 searches the 0x58-byte records in the embedded
// Living World store reached through the GameLogic +0x170 tail-thunk
// family.  Its comparison uses the record's string field at +0x10.  The exact
// BFME-only class and method spelling are not independently known, so the
// owner and operation remain address scoped.

#include <string.h>
#include <vector>

struct Rva00363360StringData
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

	Rva00363360StringData *m_data;
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

class Rva00363360LivingWorldEntryStore
{
public:
	Rva00361960 *findByField10(const BfmeSharedString &key);

private:
	char m_beforeEntries[0x18];
	std::vector<Rva00361960> m_entries;
};

Rva00361960 *Rva00363360LivingWorldEntryStore::findByField10(
	const BfmeSharedString &key)
{
	for (unsigned int i = 0; i < m_entries.size(); ++i)
	{
		BfmeSharedString current = m_entries[i].copyString();
		if (current.compare(key) == 0)
			return &m_entries[i];
	}
	return 0;
}
