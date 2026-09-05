// ?insert_unique_noresize@?$hashtable@U?$pair@$$CBHUGen_t_00425240_p12cd@@@_STL@@HU?$hash@H@2@U?$_Select1st@U?$pair@$$CBHUGen_t_00425240_p12cd@@@_STL@@@2@U?$equal_to@H@2@V?$allocator@U?$pair@$$CBHUGen_t_00425240_p12cd@@@_STL@@@2@@_STL@@QAE?AU?$pair@U?$_Ht_iterator@U?$pair@$$CBHUGen_t_00425240_p12cd@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBHUGen_t_00425240_p12cd@@@_STL@@@2@HU?$hash@H@2@U?$_Select1st@U?$pair@$$CBHUGen_t_00425240_p12cd@@@_STL@@@2@U?$equal_to@H@2@V?$allocator@U?$pair@$$CBHUGen_t_00425240_p12cd@@@_STL@@@2@@_STL@@_N@2@ABU?$pair@$$CBHUGen_t_00425240_p12cd@@@2@@Z
// partial score=0.25 date=2026-09-05
// cl: /DNDEBUG /MD /EHsc
// stlport
//
// Open-BFME5: byte-twin of the audio hashtable insert_unique_noresize
// (Code/GameEngine/Source/Common/Audio/STLAudioEventInfoHashtableInsertUniqueNoresize006AB4A0Shape.cpp,
// retail 0x006AB4A0), same STLport template body, int key instead of
// AsciiString: no compare/memcmp machinery needed. Retail 0x00424D30, 270B.
// Callees: allocate (0x0082E540), two ILT thunks (0x0001E4E3, 0x00031AE3).
// pin_consistency: ?insert_unique_noresize@...Gen_t_00425240_p12cd... ->
// 0x00424D30 (matched, owned by d_00424d30) -- consistent. A second stale
// candidate name Gen_t_004258b0_p12cd pins the same address; the payload
// type is an opaque "tgrid" element never dereferenced by this body, so
// either name reproduces retail bytes identically.

// _Node = _M_next(4) + Value(pair<const int, Gen_t_00425240_p12cd>); retail's
// allocate call pushes 0x0c (12), so the payload is a single 4-byte field.
struct Gen_t_00425240_p12cd
{
	void *m_ptr;
};

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

template <class T> struct hash;
template <> struct hash<int>
{
	unsigned int operator()(int key) const { return (unsigned int)key; }
};

template <class T> struct equal_to;
template <> struct equal_to<int>
{
	bool operator()(int left, int right) const { return left == right; }
};

}

typedef _STL::pair<const int, Gen_t_00425240_p12cd> Rva00424D30Pair;
typedef _STL::hashtable<Rva00424D30Pair, int,
	_STL::hash<int>, _STL::_Select1st<Rva00424D30Pair>,
	_STL::equal_to<int>,
	_STL::allocator<Rva00424D30Pair> > Rva00424D30Hashtable;

template _STL::pair<Rva00424D30Hashtable::iterator, bool>
Rva00424D30Hashtable::insert_unique_noresize(const Rva00424D30Pair &);
