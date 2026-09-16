// ?addLogin@GameSpyLoginPreferences@@QAEXVAsciiString@@000@Z
// partial score=0.44 date=2026-09-15
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <map>
#include <list>
#include <algorithm>
#include <new>

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
	if (std::find(m_emailNickMap[email].begin(), m_emailNickMap[email].end(), nick)
		== m_emailNickMap[email].end())
	{
		AsciiStringList &list = m_emailNickMap[email];
		BfmeAsciiListNode *node = (BfmeAsciiListNode *)_STL::__new_alloc::allocate(12);
		new (&node->value) AsciiString(nick);
		BfmeAsciiListNode *sentinel = *(BfmeAsciiListNode **)&list;
		node->next = sentinel;
		node->previous = sentinel->previous;
		sentinel->previous->next = node;
		sentinel->previous = node;
	}
	m_emailPasswordMap[email] = password;
	m_emailDateMap[email] = date;
}
