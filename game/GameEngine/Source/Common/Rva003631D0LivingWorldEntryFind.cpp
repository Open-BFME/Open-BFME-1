// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
//
// Retail RVA 0x003631D0 searches the 0x58-byte records in the embedded
// store reached by the named Rva00383870::invoke tail thunk.  The target is
// the relocation-masked twin of the landed 0x00363360 lookup: its comparison
// uses the record's string field at +0x0C.  Its copy route is the target's
// j_0004B470 -> 0x00361930 copy-constructor helper, not the donor's +0x10
// route.  The exact BFME-only class and method spelling are not independently
// known, so this owner is scoped to
// the caller-backed target address.

#include <string.h>
#include <vector>

struct Rva003631D0StringData
{
	int references;
	unsigned short length;
	unsigned short capacity;
	char text[1];
};

template <typename T> class StringBase
{
	friend class Rva003631D0String;

private:
	StringBase(const StringBase<T> &other);
	~StringBase();

	Rva003631D0StringData *m_data;
};

class Rva003631D0String : private StringBase<char>
{
public:
	Rva003631D0String(const Rva003631D0String &other);
	~Rva003631D0String();

	int compare(const Rva003631D0String &other) const
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

class Rva003631D0Entry
{
public:
	Rva003631D0String copyStringAt0C()
	{
		return m_string;
	}

private:
	char m_beforeString[0x0C];
	Rva003631D0String m_string;
	char m_afterString[0x58 - 0x0C - sizeof(Rva003631D0String)];
};

class Rva003631D0LivingWorldEntryStore
{
public:
	Rva003631D0Entry *findByField10(const Rva003631D0String &key);

private:
	char m_beforeEntries[0x18];
	std::vector<Rva003631D0Entry> m_entries;
};

Rva003631D0Entry *Rva003631D0LivingWorldEntryStore::findByField10(
	const Rva003631D0String &key)
{
	for (unsigned int i = 0; i < m_entries.size(); ++i)
	{
		Rva003631D0String current = m_entries[i].copyStringAt0C();
		if (current.compare(key) == 0)
			return &m_entries[i];
	}
	return 0;
}
