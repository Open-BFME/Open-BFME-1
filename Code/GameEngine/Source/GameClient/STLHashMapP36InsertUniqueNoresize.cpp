// cl: /DNDEBUG /MD

// Open-BFME5: hashtable<pair<const int, 36-byte value>>::insert_unique_noresize,
// retail 0x0042DF60, 146 bytes. Called from parseFXListDefinition after
// hashtable::resize; the matching clear at 0x0042DC10 already names the
// mapped type Gen_t_0042dc10_p36cd. Node is 0x2C: next + int key + 36-byte
// FXList. Hash is the identity, so the bucket index is a plain divide.
//
// There is no unwind frame, so this translation unit is built without
// exceptions and STLport's try around the construct is gone.

typedef int Int;

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
};

template <class T>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/STLTypedefs.h
struct hash
{
	unsigned int operator()(const T &x) const { return (unsigned int)x; }
};

template <class T>
struct equal_to
{
	bool operator()(const T &a, const T &b) const { return a == b; }
};

template <class T>
struct _Select1st
{
	const typename T::first_type &operator()(const T &x) const { return x.first; }
};

template <class T>
class allocator {};

class _BucketVector
{
public:
	unsigned int size(void) const { return (unsigned int)(_M_finish - _M_start); }

	void *&operator[](unsigned int n) { return *(_M_start + n); }
	void *const &operator[](unsigned int n) const { return *(_M_start + n); }

	void **_M_start;
	void **_M_finish;
	void **_M_end_of_storage;
};

template <class V>
struct _Hashtable_node
{
	_Hashtable_node<V> *_M_next;
	V _M_val;
};

template <class T1, class T2>
void _Construct(T1 *p, const T2 &value);

struct Gen_t_0042dc10_p36cd
{
	int a[9];
	Gen_t_0042dc10_p36cd();
	Gen_t_0042dc10_p36cd(const Gen_t_0042dc10_p36cd &);
	~Gen_t_0042dc10_p36cd();
};

typedef pair<const Int, Gen_t_0042dc10_p36cd> BfmeFXListPair;

template <class Value, class Key, class HashFcn, class ExtractKey, class EqualKey, class Alloc>
class hashtable
{
public:
	typedef unsigned int size_type;
	typedef _Hashtable_node<Value> _Node;

	struct iterator
	{
		_Node *_M_cur;
		hashtable *_M_ht;

		iterator(_Node *n, hashtable *h) : _M_cur(n), _M_ht(h) {}
	};

	pair<iterator, bool> insert_unique_noresize(const Value &obj);

private:
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
		_Node *n = (_Node *)vectorSmallAllocate(sizeof(_Node));
		n->_M_next = 0;
		_Construct(&n->_M_val, obj);
		return n;
	}

	HashFcn _M_hash;
	EqualKey _M_equals;
	ExtractKey _M_get_key;
	_BucketVector _M_buckets;
	size_type _M_num_elements;
};

template <class Value, class Key, class HashFcn, class ExtractKey, class EqualKey, class Alloc>
pair<typename hashtable<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>::iterator, bool>
hashtable<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>::insert_unique_noresize(const Value &obj)
{
	const size_type n = _M_bkt_num(obj);
	_Node *first = (_Node *)_M_buckets[n];

	for (_Node *cur = first; cur; cur = cur->_M_next)
		if (_M_equals(_M_get_key(cur->_M_val), _M_get_key(obj)))
			return pair<iterator, bool>(iterator(cur, this), false);

	_Node *tmp = _M_new_node(obj);
	tmp->_M_next = first;
	_M_buckets[n] = tmp;
	++_M_num_elements;
	return pair<iterator, bool>(iterator(tmp, this), true);
}

template pair<hashtable<BfmeFXListPair, Int, hash<Int>,
	_Select1st<BfmeFXListPair>, equal_to<Int>,
	allocator<BfmeFXListPair> >::iterator, bool>
hashtable<BfmeFXListPair, Int, hash<Int>,
	_Select1st<BfmeFXListPair>, equal_to<Int>,
	allocator<BfmeFXListPair> >::insert_unique_noresize(const BfmeFXListPair &);

}
