// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: _STL::hashtable<pair<const NameKeyType, DamageFX> >::_M_insert,
// retail 0x000675E0, 114 bytes. The body carried only a machine byte-dump row;
// reverse/reloc_names.csv holds the name with identity=real.
//
// The layout falls out of the offsets. Three empty functors sit at +0 and pad
// to four, then the bucket vector's three pointers at +4, +8 and +0x0C, and
// the element count at +0x10.
//
// The bucket index is computed inline as a plain divide: rts::hash<NameKeyType>
// is the identity, so the key is read straight out of the pair and taken modulo
// the bucket count. The node is 0x408 bytes -- one next pointer and a 1028-byte
// pair, so DamageFX itself is 1024 -- and the value is copy-constructed through
// an out-of-line _Construct,
// which is why the next pointer is cleared before the call and only linked to
// the old bucket head afterwards.
//
// There is no unwind frame, so this translation unit is built without
// exceptions and STLport's try around the construct is gone.

typedef int Int;

enum NameKeyType { NAMEKEY_INVALID = 0 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/DamageFX.h
class DamageFX
{
	char m_bfmeBody[1024];
};

namespace rts
{

template <class T>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/STLTypedefs.h
struct hash
{
	unsigned int operator()(const T &x) const { return (unsigned int)x; }
};

// equal_to comes from rts too, not from _STL: retail's name back-references a
// different namespace for it than for _Select1st.
template <class T>
struct equal_to {};

}

namespace _STL
{

// The allocator picks between the small and large blocks by size. Here the node
// is a compile-time 0x408, so the comparison folds away and only the large call
// survives -- which is why this body reaches 0x00881F30 where its 12-byte
// siblings reach 0x0082E540.
void *__cdecl vectorLargeAllocate(unsigned int bytes);
void *__cdecl vectorSmallAllocate(unsigned int bytes);

inline void *BfmeNodeAllocate(unsigned int bytes)
{
	if (bytes > 128)
		return vectorLargeAllocate(bytes);
	return vectorSmallAllocate(bytes);
}

template <class T1, class T2>
struct pair
{
	typedef T1 first_type;

	T1 first;
	T2 second;
};


template <class T>
struct _Select1st
{
	const typename T::first_type &operator()(const T &x) const { return x.first; }
};

template <class T>
class allocator {};

// _M_buckets is a vector of void*, not of node pointers, and its size and its
// indexing go through separate inline accessors -- which is why retail reloads
// the start pointer after the divide instead of keeping it live.
class _BucketVector
{
public:
	unsigned int size(void) const { return (unsigned int)(_M_finish - _M_start); }

	void *&operator[](unsigned int n) { return *(_M_start + n); }
	void *const &operator[](unsigned int n) const { return *(_M_start + n); }

	void **_M_start;					// +0x00
	void **_M_finish;					// +0x04
	void **_M_end_of_storage;				// +0x08
};

template <class V>
struct _Hashtable_node
{
	_Hashtable_node<V> *_M_next;
	V _M_val;
};

template <class T1, class T2>
void _Construct(T1 *p, const T2 &value);			// ILT 0x0000310C

template <class Value, class Key, class HashFcn, class ExtractKey, class EqualKey, class Alloc>
class hashtable
{
public:
	typedef unsigned int size_type;
	typedef _Hashtable_node<Value> _Node;

	Value &_M_insert(const Value &obj);

private:
	void resize(size_type numElementsHint);			// ILT 0x0003729F

	size_type _M_bkt_num_key(const Key &key) const
	{
		return _M_hash(key) % _M_buckets.size();
	}

	size_type _M_bkt_num(const Value &obj) const
	{
		return _M_bkt_num_key(_M_get_key(obj));
	}

	_Node *_M_new_node(const Value &obj)
	{
		_Node *n = (_Node *)BfmeNodeAllocate(sizeof(_Node));
		n->_M_next = 0;
		_Construct(&n->_M_val, obj);
		return n;
	}

	HashFcn _M_hash;					// +0x00
	EqualKey _M_equals;
	ExtractKey _M_get_key;
	_BucketVector _M_buckets;				// +0x04
	size_type _M_num_elements;				// +0x10
};

template <class Value, class Key, class HashFcn, class ExtractKey, class EqualKey, class Alloc>
Value &hashtable<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>::_M_insert(const Value &obj)
{
	resize(_M_num_elements + 1);

	size_type n = _M_bkt_num(obj);
	_Node *first = (_Node *)_M_buckets[n];
	_Node *tmp = _M_new_node(obj);
	tmp->_M_next = first;
	_M_buckets[n] = tmp;
	++_M_num_elements;
	return tmp->_M_val;
}

typedef pair<const NameKeyType, DamageFX> BfmeDamageFXPair;

template BfmeDamageFXPair &hashtable<BfmeDamageFXPair, NameKeyType,
	rts::hash<NameKeyType>, _Select1st<BfmeDamageFXPair>, rts::equal_to<NameKeyType>,
	allocator<BfmeDamageFXPair> >::_M_insert(const BfmeDamageFXPair &);

}
