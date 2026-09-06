// Open-BFME7: reloc-only twins (diff 0) of the AudioEventInfo hashtable insert_unique_noresize
// at 0x006AB4A0: 0x00424D30 and 0x005C9A20, AsciiString key + pointer payload; only the
// _M_bkt_num_key and _Construct callee thunks differ.
// cl: /DNDEBUG /MD /EHsc
// stlport

// The 0x006AB4A0 body is the STLport hash insertion used by the audio-name
// table.  The generated pin list also contains two stale integer-payload
// candidates at this address; the retail node is 0x0c bytes and its key walk
// is the BFME AsciiString comparison, so the concrete shape below follows the
// bytes rather than those candidate names.

extern "C" int __cdecl memcmp(const void *left, const void *right,
	unsigned int count);
#pragma intrinsic(memcmp)

struct Rva00424D30StringData
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	char m_data[1];
};

class AsciiString
{
public:
	AsciiString(const AsciiString &other);
	~AsciiString();

	int compare(const AsciiString &other) const
	{
		int otherLength = other.m_data ? other.m_data->m_length : 0;
		const char *otherData = other.m_data ? other.m_data->m_data :
			(const char *)"";
		int thisLength = m_data ? m_data->m_length : 0;
		const char *thisData = m_data ? m_data->m_data : (const char *)"";
		int length = thisLength < otherLength ? thisLength : otherLength;
		int result = memcmp(thisData, otherData, length);
		if (result != 0)
			return result;
		return thisLength - otherLength;
	}

private:
	Rva00424D30StringData *m_data;
};

struct Rva00424D30Value;
struct Rva005C9A20Value;

namespace rts
{
template <class T> struct hash;
template <> struct hash<AsciiString>
{
	unsigned int operator()(const AsciiString &) const;
};

template <class T> struct equal_to;

template <> struct equal_to<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left.compare(right) == 0;
	}
};
}

namespace _STL
{

void *__cdecl vectorSmallAllocate(unsigned int bytes);

template <class T1, class T2>
struct pair
{
	typedef T1 first_type;

	T1 first;
	T2 second;

	pair(const T1 &a, const T2 &b) : first(a), second(b) {}
	pair(const pair &other) : first(other.first), second(other.second) {}
};

template <class T>
struct _Select1st
{
	const typename T::first_type &operator()(const T &value) const
	{
		return value.first;
	}
};

template <class T>
class allocator {};

class _BucketVector
{
public:
	unsigned int size(void) const
	{
		return (unsigned int)(_M_finish - _M_start);
	}

	void *&operator[](unsigned int index) { return *(_M_start + index); }
	void *const &operator[](unsigned int index) const
	{
		return *(_M_start + index);
	}

	void **_M_start;
	void **_M_finish;
	void **_M_end_of_storage;
};

template <class Value>
struct _Hashtable_node
{
	_Hashtable_node<Value> *_M_next;
	Value _M_val;
};

template <class T1, class T2>
void _Construct(T1 *place, const T2 &value);

struct Rva00424D30AudioPair
{
	const AsciiString first;
	Rva00424D30Value *second;
};

template <class Value, class Key, class HashFcn, class ExtractKey,
	class EqualKey, class Alloc>
class hashtable;

template <class Value>
struct _Nonconst_traits
{
	typedef Value &reference;
	typedef Value *pointer;
};

template <class Value, class Traits, class Key, class HashFcn,
	class ExtractKey, class EqualKey, class Alloc>
struct _Ht_iterator
{
	typedef _Hashtable_node<Value> _Node;
	typedef hashtable<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc> _Hashtable;

	_Node *_M_cur;
	_Hashtable *_M_ht;

	_Ht_iterator(_Node *node, _Hashtable *table) : _M_cur(node), _M_ht(table) {}
};

template <class Value, class Key, class HashFcn, class ExtractKey,
	class EqualKey, class Alloc>
class hashtable
{
public:
	typedef unsigned int size_type;
	typedef _Hashtable_node<Value> _Node;
	typedef _Ht_iterator<Value, _Nonconst_traits<Value>, Key, HashFcn, ExtractKey, EqualKey, Alloc>
		iterator;

	_STL::pair<iterator, bool> insert_unique_noresize(const Value &value);

private:
	size_type _M_bkt_num_key(const Key &key, size_type count) const;

	size_type _M_bkt_num(const Value &value) const
	{
		return _M_bkt_num_key(_M_get_key(value), _M_buckets.size());
	}

	const Key &_M_get_key(const Value &value) const
	{
		return ExtractKey() (value);
	}

	_Node *_M_new_node(const Value &value)
	{
		_Node *node = (_Node *)vectorSmallAllocate(sizeof(_Node));
		node->_M_next = 0;
		_Construct(&node->_M_val, value);
		return node;
	}

	HashFcn _M_hash;
	EqualKey _M_equals;
	ExtractKey _M_get_key_functor;
	_BucketVector _M_buckets;
	size_type _M_num_elements;
};

template <class Value, class Key, class HashFcn, class ExtractKey,
	class EqualKey, class Alloc>
_STL::pair<typename hashtable<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>::iterator, bool>
hashtable<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>::insert_unique_noresize(
	const Value &obj)
{
	const size_type n = _M_bkt_num(obj);
	_Node *first = (_Node *)_M_buckets[n];

	for (_Node *cur = first; cur; cur = cur->_M_next)
		if (_M_equals(_M_get_key(cur->_M_val), _M_get_key(obj)))
			return _STL::pair<iterator, bool>(iterator(cur, this), false);

	_Node *tmp = _M_new_node(obj);
	tmp->_M_next = first;
	_M_buckets[n] = tmp;
	++_M_num_elements;
	return _STL::pair<iterator, bool>(iterator(tmp, this), true);
}

}

typedef _STL::pair<const AsciiString, Rva00424D30Value *> Rva00424D30Pair;
typedef _STL::hashtable<Rva00424D30Pair, AsciiString,
	rts::hash<AsciiString>, _STL::_Select1st<Rva00424D30Pair>,
	rts::equal_to<AsciiString>,
	_STL::allocator<Rva00424D30Pair> > Rva00424D30Hashtable;

template _STL::pair<Rva00424D30Hashtable::iterator, bool>
Rva00424D30Hashtable::insert_unique_noresize(const Rva00424D30Pair &);
typedef _STL::pair<const AsciiString, Rva005C9A20Value *> Rva005C9A20Pair;
typedef _STL::hashtable<Rva005C9A20Pair, AsciiString,
	rts::hash<AsciiString>, _STL::_Select1st<Rva005C9A20Pair>,
	rts::equal_to<AsciiString>,
	_STL::allocator<Rva005C9A20Pair> > Rva005C9A20Hashtable;

template _STL::pair<Rva005C9A20Hashtable::iterator, bool>
Rva005C9A20Hashtable::insert_unique_noresize(const Rva005C9A20Pair &);
