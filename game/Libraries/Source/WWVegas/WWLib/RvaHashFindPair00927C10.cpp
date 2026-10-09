// Two hash-find wrappers (0x00927C10 + 0x00928200) over the pair<int,int>
// _M_find at 0x00927800, plus the 0x00927800 callable alias pin.
// IDENTITY IS NOT RECOVERED: every name keeps its address token.
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

typedef unsigned int UnsignedInt;

typedef _STL::pair<int, int> RvaHashKey;
typedef _STL::pair<const RvaHashKey, int> RvaHashValue;

struct RvaHashFn
{
	UnsignedInt operator()(const RvaHashKey &key) const
	{
		return (static_cast<UnsignedInt>(key.second) << 16)
			+ static_cast<UnsignedInt>(key.first);
	}
};

struct RvaHashEq
{
	bool operator()(const RvaHashKey &left, const RvaHashKey &right) const
	{
		return left.first == right.first && left.second == right.second;
	}
};

typedef _STL::hashtable<RvaHashValue, RvaHashKey,
	RvaHashFn, _STL::_Select1st<RvaHashValue>, RvaHashEq,
	_STL::allocator<RvaHashValue> > RvaHashTable;

struct Rva00927800Hash;
struct Rva00927800Eq;
class Rva00927C10Find;
class Rva00928200Find;
namespace _STL
{
template <> class hashtable<RvaHashValue, RvaHashKey,
    Rva00927800Hash, _Select1st<RvaHashValue>, Rva00927800Eq,
    allocator<RvaHashValue> >
{
    friend class ::Rva00927C10Find;
    friend class ::Rva00928200Find;
    template <class Lookup>
    _Hashtable_node<RvaHashValue> *_M_find(const Lookup &) const;
};
}

struct Rva00927C10Result
{
	void *m_node;
	void *m_owner;
};

class Rva00927C10Find
{
public:
	Rva00927C10Result *find(Rva00927C10Result *out, const RvaHashKey &key) const;
	RvaHashTable m_table;
};

// mov eax,[esp+8] / push esi / push eax / mov esi,ecx / call 0x00927800 /
// mov ecx,[esp+8] / mov [ecx],eax / mov [ecx+4],esi / mov eax,ecx / pop esi /
// ret 8: forwards the key slot into the pinned _M_find, then fills the
// caller's (node, owner) out-pair and returns the out-pointer.
Rva00927C10Result *Rva00927C10Find::find(Rva00927C10Result *out,
	const RvaHashKey &key) const
{
	out->m_node = reinterpret_cast<const _STL::hashtable<RvaHashValue, RvaHashKey,
        Rva00927800Hash, _STL::_Select1st<RvaHashValue>, Rva00927800Eq,
        _STL::allocator<RvaHashValue> > *>(this)->_M_find<RvaHashKey>(key);
	out->m_owner = (void *)this;
	return out;
}

struct Rva00928200Result
{
	void *m_node;
	void *m_owner;
};

class Rva00928200Find
{
public:
	Rva00928200Result *find(Rva00928200Result *out, const RvaHashKey &key) const;
	RvaHashTable m_table;
};

// Byte-identical twin of 0x00927C10: one-identity rule needs its own
// address-derived owner.
Rva00928200Result *Rva00928200Find::find(Rva00928200Result *out,
	const RvaHashKey &key) const
{
	out->m_node = reinterpret_cast<const _STL::hashtable<RvaHashValue, RvaHashKey,
        Rva00927800Hash, _STL::_Select1st<RvaHashValue>, Rva00927800Eq,
        _STL::allocator<RvaHashValue> > *>(this)->_M_find<RvaHashKey>(key);
	out->m_owner = (void *)this;
	return out;
}
