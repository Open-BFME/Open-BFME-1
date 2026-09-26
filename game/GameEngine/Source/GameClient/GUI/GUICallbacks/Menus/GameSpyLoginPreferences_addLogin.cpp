// ?addLogin@GameSpyLoginPreferences@@QAEXVAsciiString@@000@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#define __new_alloc BFMEHeaderNewAlloc
#include <map>
#include <list>
#include <algorithm>
#include <new>
#undef __new_alloc

namespace _STL
{
class __new_alloc
{
public:
	static void *allocate(unsigned int size);
};
}

template <class T> class StringBase
{
	friend class AsciiString;
private:
	StringBase(const StringBase &source);
	StringBase();
	~StringBase();
	void set(const StringBase &source);
	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &source) : StringBase<char>(source) {}
	~AsciiString() {}
	AsciiString &operator=(const AsciiString &source)
	{
		set(source);
		return *this;
	}
	bool operator==(const AsciiString &other) const { return m_data == other.m_data; }
	bool operator<(const AsciiString &other) const;
};

struct BFMEFindStringHeader
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	char data[1];
};

struct BFMEFindAsciiStringView
{
	BFMEFindStringHeader *m_data;

	int compare(const BFMEFindAsciiStringView &string) const
	{
		const BFMEFindAsciiStringView *self = this;
		const BFMEFindAsciiStringView *that = &string;
		int thatLen = that->m_data ? that->m_data->length : 0;
		const char *thatData = that->m_data ? &that->m_data->data[0] : (const char *)"";
		int thisLen = self->m_data ? self->m_data->length : 0;
		const char *thisData = self->m_data ? &self->m_data->data[0] : (const char *)"";
		int n = thisLen < thatLen ? thisLen : thatLen;
		int c = memcmp(thisData, thatData, n);
		if (c != 0)
			return c;
		return thisLen - thatLen;
	}
};

inline bool operator==(const BFMEFindAsciiStringView &a,
	const BFMEFindAsciiStringView &b)
{
	return a.compare(b) == 0;
}

typedef std::list<AsciiString> AsciiStringList;
struct BfmeAsciiListNode
{
	BfmeAsciiListNode *next;
	BfmeAsciiListNode *previous;
	AsciiString value;
};
typedef std::map<AsciiString, AsciiString> PassMap;
typedef std::map<AsciiString, AsciiStringList> NickMap;
typedef std::map<AsciiString, AsciiString> DateMap;

class UserPreferences
{
public:
	virtual ~UserPreferences();
private:
	unsigned char m_pad[0x10];
};

class GameSpyLoginPreferences : public UserPreferences
{
public:
	void addLogin(AsciiString email, AsciiString nick,
		AsciiString password, AsciiString date);
private:
	PassMap m_emailPasswordMap;
	NickMap m_emailNickMap;
	DateMap m_emailDateMap;
};

void GameSpyLoginPreferences::addLogin(AsciiString email, AsciiString nick,
	AsciiString password, AsciiString date)
{
	if (std::find(
		reinterpret_cast<std::list<BFMEFindAsciiStringView> &>(m_emailNickMap[email]).begin(),
		reinterpret_cast<std::list<BFMEFindAsciiStringView> &>(m_emailNickMap[email]).end(),
		reinterpret_cast<const BFMEFindAsciiStringView &>(nick))
		== reinterpret_cast<std::list<BFMEFindAsciiStringView> &>(m_emailNickMap[email]).end())
	{
		AsciiStringList &list = m_emailNickMap[email];
		BfmeAsciiListNode *sentinel = *(BfmeAsciiListNode **)&list;
		BfmeAsciiListNode *node = (BfmeAsciiListNode *)_STL::__new_alloc::allocate(12);
		AsciiString *value = &node->value;
		new (value) AsciiString(nick);
		BfmeAsciiListNode *previous = sentinel->previous;
		node->next = sentinel;
		node->previous = previous;
		previous->next = node;
		sentinel->previous = node;
	}
	m_emailPasswordMap[email] = password;
	m_emailDateMap[email] = date;
}
