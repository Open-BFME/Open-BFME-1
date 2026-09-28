// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// The 53-byte bodies at 0x009D7350 and 0x009D75C0 are STLport
// hashtable<pair<const char *, Mapped>, const char *, hash<const char *>,
// ...>::_M_bkt_num_key(const key_type &) const: __stl_hash_string over the
// key (times-5 loop) modulo the bucket count, where the bucket count is
// recomputed as (finish - start) >> 2 from the bucket vector at this+4/+8.
// Identity beyond the const char * key and the inline hash is
// address-derived: the mapped type is named per body.

#include <hash_map>

struct Rva009D7350Mapped
{
	char m_data[4];
};

typedef _STL::pair<const char *, Rva009D7350Mapped> Rva009D7350Pair;

typedef _STL::hashtable<Rva009D7350Pair, const char *, _STL::hash<const char *>,
	_STL::_Select1st<Rva009D7350Pair>, _STL::equal_to<const char *>,
	_STL::allocator<Rva009D7350Pair> > Rva009D7350Hashtable;

template unsigned int Rva009D7350Hashtable::_M_bkt_num_key(const char * const &) const;

struct Rva009D75C0Mapped
{
	char m_data[4];
};

typedef _STL::pair<const char *, Rva009D75C0Mapped> Rva009D75C0Pair;

typedef _STL::hashtable<Rva009D75C0Pair, const char *, _STL::hash<const char *>,
	_STL::_Select1st<Rva009D75C0Pair>, _STL::equal_to<const char *>,
	_STL::allocator<Rva009D75C0Pair> > Rva009D75C0Hashtable;

template unsigned int Rva009D75C0Hashtable::_M_bkt_num_key(const char * const &) const;
