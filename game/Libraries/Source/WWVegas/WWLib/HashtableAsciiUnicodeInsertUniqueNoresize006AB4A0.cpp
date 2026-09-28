// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// stlport

// Retail 0x006AB4A0: STLport hashtable::insert_unique_noresize for
// hash_map<AsciiString, UnicodeString, rts::hash, rts::equal_to>.  The body
// was earlier filed under an AsciiString -> AudioEventInfo* table, but its
// node constructor (ILT 0x00035B0C -> _Construct 0x006A15D0 -> ILT 0x0001183D)
// ends in the out-of-line pair copy at 0x0069EF10, which copy-constructs
// StringBase<char> at +0 and StringBase<G> at +4: the stored value is
// pair<const AsciiString, UnicodeString>.  Its callers are the
// MilesAudioManager subtitle map (0x006AF840, inlined hash_map::insert) and
// two out-of-line hash_map::insert copies (0x006AC740, 0x006AF510), which
// resize through the matched 0x006A7B60 first.  The node is 0x0c bytes and
// the key walk is the BFME AsciiString comparison; the hashtable below is
// modelled on those bytes.

extern "C" int __cdecl memcmp(const void *left, const void *right,
	unsigned int count);
#pragma intrinsic(memcmp)

struct Rva006AB4A0StringData
{
	int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	char m_data[1];
};

#include "ascii_string.h"
#include "unicode_string.h"

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

typedef _STL::pair<const AsciiString, UnicodeString> Rva006AB4A0Pair;
typedef _STL::hashtable<Rva006AB4A0Pair, AsciiString,
	rts::hash<AsciiString>, _STL::_Select1st<Rva006AB4A0Pair>,
	rts::equal_to<AsciiString>,
	_STL::allocator<Rva006AB4A0Pair> > Rva006AB4A0Hashtable;

template _STL::pair<Rva006AB4A0Hashtable::iterator, bool>
Rva006AB4A0Hashtable::insert_unique_noresize(const Rva006AB4A0Pair &);
