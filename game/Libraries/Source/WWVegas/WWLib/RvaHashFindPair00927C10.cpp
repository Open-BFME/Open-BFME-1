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

extern void Rva00927800Target();

class RvaHashFindRoute
{
public:
	typedef void *(RvaHashFindRoute::*Call)(const RvaHashKey &key) const;
};

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
	union { void (*address)(); RvaHashFindRoute::Call member; } route = { Rva00927800Target };
	out->m_node = (reinterpret_cast<const RvaHashFindRoute *>(this)->*route.member)(key);
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
	union { void (*address)(); RvaHashFindRoute::Call member; } route = { Rva00927800Target };
	out->m_node = (reinterpret_cast<const RvaHashFindRoute *>(this)->*route.member)(key);
	out->m_owner = (void *)this;
	return out;
}
