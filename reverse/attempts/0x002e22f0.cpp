// ?xfer@LuaSpyData@@UAEXPAVXfer@@@Z
// partial score=0.37 date=2026-09-24
// cl: /DNDEBUG /MD /EHsc
//
// LuaSpyData::xfer, retail 0x002E22F0 (657 bytes).  Identity: the vtable at
// 0x010BA790 (installed by the constructor at 0x0027EE90, and by
// AIUpdateInterface's constructor for its embedded copy) has four slots: the
// scalar-deleting destructor, an empty method, a getter returning the string
// "LuaSpyData" (VA 0x010BA7A4, stored right after the table) and this body,
// which takes the Xfer and versions the object like every Snapshot::xfer.
//
// The object holds a vector of 12-byte records at +4: two NameKeyTypes and an
// STLport list<int>.  Saving writes each record's keys as names (KEYNAME) and
// hands its list to the list transfer at ILT 0x0000FFE2; loading reads the two
// names back into keys, appends a record with an empty list and fills that
// list through the same transfer.  The vector and list views below model
// retail's STLport: push_back calls its element construct out of line, the
// list constructor and clear() are inline, and ~_List_base is out of line.

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

template <typename T> struct StringData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data(0) {}
	~StringBase();
	void set(const StringBase<T> &other);

	StringData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() {}
	~AsciiString() {}
	AsciiString &operator=(const AsciiString &that)
	{
		set(that);
		return *this;
	}
	const char *str() const { return m_data ? m_data->m_text : ""; }
};

AsciiString KEYNAME(NameKeyType key);	///< ILT 0x0000AF1A

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);	///< ILT 0x0003ADD7
};

extern NameKeyGenerator *TheNameKeyGenerator;	///< retail [0x012ED600]

namespace _STL
{
struct __false_type
{
};

template <class Type>
class allocator
{
};

class __new_alloc
{
public:
	static void *__cdecl allocate(unsigned int size);
};

template <bool Threads, int Inst>
class __node_alloc
{
public:
	static void __cdecl _M_deallocate(void *pointer, unsigned int size);
};

template <class Type>
struct _List_node
{
	_List_node<Type> *_M_next;
	_List_node<Type> *_M_prev;
	Type _M_data;
};

template <class Type, class Allocator>
class _List_base
{
public:
	_List_base()
	{
		_M_node = (_List_node<Type> *)__new_alloc::allocate(sizeof(_List_node<Type>));
		_M_node->_M_next = _M_node;
		_M_node->_M_prev = _M_node;
	}
	~_List_base();

	void clear()
	{
		_List_node<Type> *current = _M_node->_M_next;
		while (current != _M_node)
		{
			_List_node<Type> *next = current->_M_next;
			__node_alloc<true, 0>::_M_deallocate(current, sizeof(_List_node<Type>));
			current = next;
		}
		_M_node->_M_next = _M_node;
		_M_node->_M_prev = _M_node;
	}

protected:
	_List_node<Type> *_M_node;
};

template <class Type, class Allocator = allocator<Type> >
class list : public _List_base<Type, Allocator>
{
};

template <class Type>
void __cdecl BfmeElementConstruct(Type *destination, const Type &value);

template <class Type, class Allocator = allocator<Type> >
class vector
{
public:
	void reserve(unsigned int count);
	int size() const { return _M_finish - _M_start; }
	Type &operator[](int index) { return _M_start[index]; }
	Type &back() { return _M_finish[-1]; }
	void push_back(const Type &value)
	{
		if (_M_finish != _M_end_of_storage)
		{
			BfmeElementConstruct(_M_finish, value);
			++_M_finish;
		}
		else
		{
			__false_type tag;
			_M_insert_overflow(_M_finish, value, tag, 1, true);
		}
	}

protected:
	void _M_insert_overflow(Type *position, const Type &value,
		const __false_type &, unsigned int fillLength, bool atEnd);

	Type *_M_start;
	Type *_M_finish;
	Type *_M_end_of_storage;
};
}

// One LuaSpyData record: two name keys and a list of ints (12 bytes).
struct LuaSpyRecord
{
	__forceinline LuaSpyRecord(const char *first, const char *second)
		: m_first(TheNameKeyGenerator->nameToKey(first)),
		  m_second(TheNameKeyGenerator->nameToKey(second))
	{
	}

	NameKeyType m_first;
	NameKeyType m_second;
	_STL::list<int> m_list;
};

// The version pair slot +0x28 takes: current version, then the version read.
struct LuaSpyVersionPair
{
	unsigned char m_version;
	unsigned char m_currentVersion;
};

class BfmeSeedTarget;
void bfmeHandOver_0000FFE2(BfmeSeedTarget *target, void *item);	///< ILT 0x0000FFE2, list<int> transfer

class Xfer
{
public:
	virtual void slot00();
	virtual bool slot04();	///< true on the path that reads records in
	virtual bool slot08();	///< true on the path that writes records out
	virtual void slot0C(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1C(); virtual void slot20();
	virtual void slot24();
	virtual void xferVersion(LuaSpyVersionPair *version);	///< +0x28
	virtual void slot2C(); virtual void slot30(); virtual void slot34();
	virtual void slot38(); virtual void slot3C(); virtual void slot40();
	virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54(); virtual void slot58();
	virtual void slot5C(); virtual void slot60(); virtual void slot64();
	virtual void xferAsciiString(AsciiString *value);	///< +0x68
	virtual void slot6C(); virtual void slot70(); virtual void slot74();
	virtual void xferInt(int *value);	///< +0x78
};

class LuaSpyData
{
public:
	virtual ~LuaSpyData();
	virtual void slot04();
	virtual const char *getName();
	virtual void xfer(Xfer *xfer);

private:
	_STL::vector<LuaSpyRecord> m_records;
};

// ?xfer@LuaSpyData@@UAEXPAVXfer@@@Z
void LuaSpyData::xfer(Xfer *xfer)
{
	{
		LuaSpyVersionPair version;
		version.m_version = 1;
		version.m_currentVersion = 1;
		xfer->xferVersion(&version);
	}

	int count = m_records.size();
	xfer->xferInt(&count);
	m_records.reserve(count);

	for (int i = 0; i < count; ++i)
	{
		AsciiString first;
		AsciiString second;
		if (xfer->slot08())
		{
			LuaSpyRecord &record = m_records[i];
			first = KEYNAME(record.m_first);
			second = KEYNAME(record.m_second);
			xfer->xferAsciiString(&first);
			xfer->xferAsciiString(&second);
			bfmeHandOver_0000FFE2((BfmeSeedTarget *)xfer, &record.m_list);
		}
		else if (xfer->slot04())
		{
			xfer->xferAsciiString(&first);
			xfer->xferAsciiString(&second);
			m_records.push_back(LuaSpyRecord(first.str(), second.str()));
			_STL::list<int> &list = m_records.back().m_list;
			list.clear();
			bfmeHandOver_0000FFE2((BfmeSeedTarget *)xfer, &list);
		}
	}
}
