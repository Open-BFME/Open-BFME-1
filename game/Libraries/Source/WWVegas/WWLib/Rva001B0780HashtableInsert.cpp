// cl: /DNDEBUG /MD /EHsc
//
// 111B twin of _STL::hashtable<pair<const Int,Int> >::_M_insert
// (stlport_hashtable_int_int_insert.cpp, retail 0x000D3430): identical
// shape (resize, inline bucket-index divide, node allocate, out-of-line
// construct, link into bucket, ++count), but the node size pushed before
// the allocate call is 0x68 here (not 0xc), so the value type is 0x64
// bytes, not the 8-byte pair<const int,int>.
// Address-derived: the real key/value types were unknown, only their total
// size (0x64) was recovered from the node-size immediate.
//
// Both out-of-line callees are now spelled as the bodies retail actually
// calls, so this TU links. Neither costs a byte: the call sequence is the
// one the 111 bytes already contain.
//
//  - 0x0000129E is an ILT thunk onto 0x001B0050, the ledger's
//    ?_Construct@U?$pair@$$CBW4NameKeyType@@VArmorTemplate@@@_STL@@U12@@_STL@@YAX
//    PAU?$pair@$$CBW4NameKeyType@@VArmorTemplate@@@0@ABU10@@Z
//    (game/GameEngine/Source/GameLogic/Object/Armor.cpp). That body is
//    STLport's out-of-line copy-construct of a pair<const NameKeyType,
//    ArmorTemplate>, and the value type is 0x64 bytes: a four-byte key
//    followed by ArmorTemplate's 0x60. That is the node size recovered here,
//    so the value is spelled as that pair and the call goes through
//    _STL::_Construct, the same spelling the converted twin
//    stlport_hashtable_namekey_damagefx_insert.cpp compiles to.
//  - 0x00047FBE is an ILT thunk onto 0x001B0480, the ledger's
//    ?resize@?$hashtable@URva001B0480Value@@... (RvaHashResize.cpp). Retail
//    links this call to that body, so the call is spelled with the
//    instantiation the ledger owns there; resize derives its bucket only
//    from the value's leading key, which is why one body serves every table.

namespace _STL
{

// The node allocator's own _M_allocate is private in STLport, so the call is
// spelled through the free-function name the ledger already pins on the same
// body at 0x0082E540.
// The node allocator's pool entry points are private STLport members
// (_STL::__node_alloc<true, 0>::_M_allocate at 0x0082E540, _M_deallocate at
// 0x0082E5F0); these TU-local helpers reach them under their real names.
template <bool __threads, int __inst> class __node_alloc;
static void *vectorSmallAllocate(unsigned int bytes);
template <bool __threads, int __inst>
class __node_alloc
{
	friend void *vectorSmallAllocate(unsigned int);
	static void *__cdecl _M_allocate(unsigned int __n);
	static void __cdecl _M_deallocate(void *__p, unsigned int __n);
};
static inline void *vectorSmallAllocate(unsigned int bytes) { return __node_alloc<true, 0>::_M_allocate(bytes); }

// STLport's placement helpers, declared (never defined) under their real
// names: _Construct is the out-of-line construct retail calls at 0x001B0050,
// and hashtable carries the resize declaration retail calls at 0x001B0480.
// The template parameter lists are the vendored STLport 5.x ones, which is
// what the mangled names encode; no STLport header is included here, so no
// other STLport body can be emitted from this TU.
template <class T1, class T2>
struct pair
{
	typedef T1 first_type;

	T1 first;
	T2 second;
};

template <class T1, class T2>
void _Construct(T1 *p, const T2 &value);

template <class T> struct hash {};
template <class T> struct equal_to {};
// allocator is a class in vendored STLport, the rest are structs; the
// class/struct tag is part of the mangled name.
template <class T> class allocator {};

template <class Value, class Key, class HashFcn, class ExtractKey, class EqualKey, class Alloc>
class hashtable
{
public:
	typedef unsigned int size_type;

	void resize(size_type numElementsHint);
};

}

typedef float Real;

// retail 0x001B0050 is _Construct over a pair of these two, so the key is the
// four-byte NameKeyType and the mapped value is ArmorTemplate, 0x60 bytes:
// 23 damage coefficients plus the separate damage scalar.
enum NameKeyType { NAMEKEY_INVALID = 0 };

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Armor.h
class ArmorTemplate
{
	Real m_damageCoefficient[23];			// +0x00 .. +0x58
	Real m_damageScalar;					// +0x5C
};

// The 0x64-byte value the 0x68 node carries. Its identity is the pair retail
// copy-constructs out of line; it is kept as an opaque byte block on the
// hashtable below only so this file's own _M_insert keeps its landed
// signature.
typedef _STL::pair<const NameKeyType, ArmorTemplate> Rva001B0780Pair;

// The table the ledger owns at 0x001B0480 (RvaHashResize.cpp), named for that
// body because retail's own call at 0x00047FBE lands on it. resize reads only
// the key at the head of the value, so its spelling constrains nothing else
// about the table it is reached through.
struct Rva001B0480Value
{
	unsigned int m_key;
};

struct Rva001B0480ExtractKey
{
	const unsigned int &operator()( const Rva001B0480Value &x ) const { return x.m_key; }
};

typedef _STL::hashtable<Rva001B0480Value, unsigned int, _STL::hash<unsigned int>,
	Rva001B0480ExtractKey, _STL::equal_to<unsigned int>,
	_STL::allocator<Rva001B0480Value> > Rva001B0480Table;

struct Rva001B0780Value
{
	char m_bytes[0x64];
};

// _BucketVector: a vector of void*, not of node pointers; size and indexing
// go through separate inline accessors, matching why retail reloads the
// start pointer after the divide instead of keeping it live.
class Rva001B0780Buckets
{
public:
	unsigned int size(void) const { return (unsigned int)(_M_finish - _M_start); }

	void *&operator[](unsigned int n) { return *(_M_start + n); }

	void **_M_start;					// +0x00
	void **_M_finish;					// +0x04
	void **_M_end_of_storage;				// +0x08
};

struct Rva001B0780Node
{
	Rva001B0780Node *_M_next;
	Rva001B0780Value _M_val;
};

class Rva001B0780Hashtable
{
public:
	typedef unsigned int size_type;

	Rva001B0780Value &_M_insert(const Rva001B0780Value &obj);

	size_type bucketOf(const Rva001B0780Value &obj) const
	{
		unsigned int key = *(const unsigned int *)&obj;
		return key % _M_buckets.size();
	}

	Rva001B0780Node *_M_new_node(const Rva001B0780Value &obj)
	{
		Rva001B0780Node *node = (Rva001B0780Node *)_STL::vectorSmallAllocate(sizeof(Rva001B0780Node));
		node->_M_next = 0;
		// retail 0x0000129E: out-of-line copy-construct of the value pair.
		_Construct((Rva001B0780Pair *)&node->_M_val, *(const Rva001B0780Pair *)&obj);
		return node;
	}

	char m_pad0[4];						// three empty functors, padded to +0x00
	Rva001B0780Buckets _M_buckets;				// +0x04
	size_type _M_num_elements;				// +0x10
};

Rva001B0780Value &Rva001B0780Hashtable::_M_insert(const Rva001B0780Value &obj)
{
	// retail 0x00047FBE: this table's resize, which is the body the ledger
	// owns at 0x001B0480 (see Rva001B0480Table above).
	((Rva001B0480Table *)this)->resize(_M_num_elements + 1);

	size_type bucketIndex = bucketOf(obj);
	Rva001B0780Node *first = (Rva001B0780Node *)_M_buckets[bucketIndex];
	Rva001B0780Node *node = _M_new_node(obj);
	node->_M_next = first;
	_M_buckets[bucketIndex] = node;
	++_M_num_elements;
	return node->_M_val;
}
