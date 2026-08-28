// ?parseCrateCreationEntry@CrateTemplate@@SAXPAVINI@@PAX1PBX@Z
// partial score=0.98 date=2026-08-28
// cl: /DNDEBUG /MD /EHsc

typedef int Int;

extern "C" __declspec(dllimport) int __cdecl sscanf(const char *, const char *, ...);

class INIException
{
public:
	INIException(Int code, const char *message, ...);
	INIException(const INIException &other);

private:
	Int m_code;
	const char *m_message;
};

class INI
{
public:
	const char *getNextToken(const char *separators = 0);
};

class AsciiString
{
public:
	AsciiString() : m_text(0) {}
	AsciiString(const char *text);
	AsciiString(const AsciiString &other);
	~AsciiString();

	void set(const AsciiString &other);

	AsciiString &operator=(const AsciiString &other)
	{
		set(other);
		return *this;
	}

private:
	char *m_text;
};

struct crateCreationEntry
{
	AsciiString crateName;
	float crateChance;
};

namespace _STL
{
void *__cdecl vectorLargeAllocate(unsigned int bytes);
void *__cdecl vectorSmallAllocate(unsigned int bytes);

inline void *BfmeNodeAllocate(unsigned int bytes)
{
	if (bytes > 128)
		return vectorLargeAllocate(bytes);
	return vectorSmallAllocate(bytes);
}

template <typename Destination, typename Source>
void __cdecl _Construct(Destination *place, const Source &value);

template <typename T>
class allocator
{
};

template <typename T>
struct _Nonconst_traits
{
};

struct _List_node_base
{
	_List_node_base *_M_next;
	_List_node_base *_M_prev;
};

template <typename T>
struct _List_node : public _List_node_base
{
	T _M_data;
};

template <typename T, typename Traits>
struct _List_iterator
{
	_List_iterator(_List_node_base *node) : _M_node(node) {}

	_List_node_base *_M_node;
};

template <typename T, typename Allocator>
class _List_base
{
public:
	typedef _List_node<T> _Node;

	_Node *_M_node;
};

template <typename T, typename Allocator>
class list : public _List_base<T, Allocator>
{
public:
	typedef _List_node<T> _Node;
	typedef _List_iterator<T, _Nonconst_traits<T> > iterator;

	iterator insert(iterator position, const T &value)
	{
		_Node *node = _M_create_node(value);
		_List_node_base *at = position._M_node;
		_List_node_base *before = at->_M_prev;
		node->_M_next = at;
		node->_M_prev = before;
		before->_M_next = node;
		at->_M_prev = node;
		return iterator(node);
	}

	void push_back(const T &value)
	{
		insert(iterator(this->_M_node), value);
	}

private:
	_Node *_M_create_node(const T &value)
	{
		_Node *node = (_Node *)BfmeNodeAllocate(sizeof(_Node));
		_Construct(&node->_M_data, value);
		return node;
	}
};
}

class CrateTemplate
{
public:
	static void parseCrateCreationEntry(INI *ini, void *instance,
		void *, const void *);

private:
	unsigned char m_padding[0x34];
	_STL::list<crateCreationEntry,
		_STL::allocator<crateCreationEntry> > m_possibleCrates;
};

// ?parseCrateCreationEntry@CrateTemplate@@SAXPAVINI@@PAX1PBX@Z
void CrateTemplate::parseCrateCreationEntry(INI *ini, void *instance,
	void *, const void *)
{
	CrateTemplate *self = (CrateTemplate *)instance;

	const char *token = ini->getNextToken();
	AsciiString crateName = token;

	token = ini->getNextToken();
	float crateValue;
	if (sscanf(token, "%f", &crateValue) != 1)
		throw INIException(3,
			"Floating point value expected instead of '%s'", token);

	crateCreationEntry newEntry;
	newEntry.crateName = crateName;
	newEntry.crateChance = crateValue;

	self->m_possibleCrates.push_back(newEntry);
}
