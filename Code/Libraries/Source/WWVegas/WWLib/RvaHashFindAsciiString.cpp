// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME5: STLport hashtable<V, AsciiString>::_M_find<AsciiString>, 24
// bodies of 159 bytes.  Every one carried only a machine byte-dump row; the
// same shape is already converted at 0x005C76A0 in
// Code/GameEngine/Source/Common/AsciiStringParticleHashFind.cpp.
//
// Two things shape the body.  The hash functor takes its key BY VALUE, so the
// lookup builds a temporary through StringBase<char>'s copy constructor and
// never destroys it -- MSVC 7.1 leaves that to the callee -- and the functor
// itself is a call.  Those are the only two calls in the body.  The equality
// test, by contrast, inlines whole: the same length-halfword,
// characters-at-eight, empty-literal-at-0x0107388B compare the tree bounds use,
// tested against zero rather than sign.
//
// The bucket walk reads the key out of each node and nothing else, so the
// mapped half of the value is not merely unnamed here -- it is unmeasured, the
// way it is in every one of these lookup bodies.  Each table is therefore
// spelled with its own extract-key functor over a value that begins with the
// AsciiString, and named for the address of the body.

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

#include "string_base.h"

typedef int Int;
typedef bool Bool;

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2, unsigned int count);
#pragma intrinsic(memcmp)

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &other) : m_string(other.m_string) {}

	int compare(const AsciiString &str) const
	{
		const int len = str.m_string.m_data ? str.m_string.m_data->length : 0;
		const char *data = str.m_string.m_data ? &str.m_string.m_data->data[0] : "";
		const int myLen = m_string.m_data ? m_string.m_data->length : 0;
		const char *myData = m_string.m_data ? &m_string.m_data->data[0] : "";
		const int result = memcmp(myData, data, myLen < len ? myLen : len);
		if (result != 0) {
			return result;
		}
		return myLen - len;
	}

	StringBase<char> m_string;
};

inline bool operator==(const AsciiString &left, const AsciiString &right)
{
	return left.compare(right) == 0;
}

namespace rts
{
template <class T>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/STLTypedefs.h
struct hash
{
	unsigned int operator()(T value) const;			// ILT 0x0000EC91
};
}

struct Rva000B8A10Value
{
	AsciiString m_key;
};

struct Rva000B8A10ExtractKey
{
	const AsciiString &operator()( const Rva000B8A10Value &x ) const { return x.m_key; }
};

typedef _STL::hashtable<Rva000B8A10Value, AsciiString, rts::hash<AsciiString>,
	Rva000B8A10ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva000B8A10Value> > Rva000B8A10Table;

// retail 0x000B8A10 -- find() is public, _M_find is not, so the public call emits it
Bool BfmeHashFindAnchor000B8A10( const Rva000B8A10Table &table, const AsciiString &key )
{
	return table.find( key ) != table.end();
}

struct Rva000D7180Value
{
	AsciiString m_key;
};

struct Rva000D7180ExtractKey
{
	const AsciiString &operator()( const Rva000D7180Value &x ) const { return x.m_key; }
};

typedef _STL::hashtable<Rva000D7180Value, AsciiString, rts::hash<AsciiString>,
	Rva000D7180ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva000D7180Value> > Rva000D7180Table;

// retail 0x000D7180 -- find() is public, _M_find is not, so the public call emits it
Bool BfmeHashFindAnchor000D7180( const Rva000D7180Table &table, const AsciiString &key )
{
	return table.find( key ) != table.end();
}

struct Rva000D7250Value
{
	AsciiString m_key;
};

struct Rva000D7250ExtractKey
{
	const AsciiString &operator()( const Rva000D7250Value &x ) const { return x.m_key; }
};

typedef _STL::hashtable<Rva000D7250Value, AsciiString, rts::hash<AsciiString>,
	Rva000D7250ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva000D7250Value> > Rva000D7250Table;

// retail 0x000D7250 -- find() is public, _M_find is not, so the public call emits it
Bool BfmeHashFindAnchor000D7250( const Rva000D7250Table &table, const AsciiString &key )
{
	return table.find( key ) != table.end();
}

struct Rva000F2010Value
{
	AsciiString m_key;
};

struct Rva000F2010ExtractKey
{
	const AsciiString &operator()( const Rva000F2010Value &x ) const { return x.m_key; }
};

typedef _STL::hashtable<Rva000F2010Value, AsciiString, rts::hash<AsciiString>,
	Rva000F2010ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva000F2010Value> > Rva000F2010Table;

// retail 0x000F2010 -- find() is public, _M_find is not, so the public call emits it
Bool BfmeHashFindAnchor000F2010( const Rva000F2010Table &table, const AsciiString &key )
{
	return table.find( key ) != table.end();
}

struct Rva001366A0Value
{
	AsciiString m_key;
};

struct Rva001366A0ExtractKey
{
	const AsciiString &operator()( const Rva001366A0Value &x ) const { return x.m_key; }
};

typedef _STL::hashtable<Rva001366A0Value, AsciiString, rts::hash<AsciiString>,
	Rva001366A0ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva001366A0Value> > Rva001366A0Table;

// retail 0x001366A0 -- find() is public, _M_find is not, so the public call emits it
Bool BfmeHashFindAnchor001366A0( const Rva001366A0Table &table, const AsciiString &key )
{
	return table.find( key ) != table.end();
}

struct Rva0038BE40Value
{
	AsciiString m_key;
};

struct Rva0038BE40ExtractKey
{
	const AsciiString &operator()( const Rva0038BE40Value &x ) const { return x.m_key; }
};

typedef _STL::hashtable<Rva0038BE40Value, AsciiString, rts::hash<AsciiString>,
	Rva0038BE40ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva0038BE40Value> > Rva0038BE40Table;

// retail 0x0038BE40 -- find() is public, _M_find is not, so the public call emits it
Bool BfmeHashFindAnchor0038BE40( const Rva0038BE40Table &table, const AsciiString &key )
{
	return table.find( key ) != table.end();
}

struct Rva0038BF10Value
{
	AsciiString m_key;
};

struct Rva0038BF10ExtractKey
{
	const AsciiString &operator()( const Rva0038BF10Value &x ) const { return x.m_key; }
};

typedef _STL::hashtable<Rva0038BF10Value, AsciiString, rts::hash<AsciiString>,
	Rva0038BF10ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva0038BF10Value> > Rva0038BF10Table;

// retail 0x0038BF10 -- find() is public, _M_find is not, so the public call emits it
Bool BfmeHashFindAnchor0038BF10( const Rva0038BF10Table &table, const AsciiString &key )
{
	return table.find( key ) != table.end();
}

struct Rva004246F0Value
{
	AsciiString m_key;
};

struct Rva004246F0ExtractKey
{
	const AsciiString &operator()( const Rva004246F0Value &x ) const { return x.m_key; }
};

typedef _STL::hashtable<Rva004246F0Value, AsciiString, rts::hash<AsciiString>,
	Rva004246F0ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva004246F0Value> > Rva004246F0Table;

// retail 0x004246F0 -- find() is public, _M_find is not, so the public call emits it
Bool BfmeHashFindAnchor004246F0( const Rva004246F0Table &table, const AsciiString &key )
{
	return table.find( key ) != table.end();
}

struct Rva00460B30Value
{
	AsciiString m_key;
};

struct Rva00460B30ExtractKey
{
	const AsciiString &operator()( const Rva00460B30Value &x ) const { return x.m_key; }
};

typedef _STL::hashtable<Rva00460B30Value, AsciiString, rts::hash<AsciiString>,
	Rva00460B30ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva00460B30Value> > Rva00460B30Table;

// retail 0x00460B30 -- find() is public, _M_find is not, so the public call emits it
Bool BfmeHashFindAnchor00460B30( const Rva00460B30Table &table, const AsciiString &key )
{
	return table.find( key ) != table.end();
}

struct Rva00460C00Value
{
	AsciiString m_key;
};

struct Rva00460C00ExtractKey
{
	const AsciiString &operator()( const Rva00460C00Value &x ) const { return x.m_key; }
};

typedef _STL::hashtable<Rva00460C00Value, AsciiString, rts::hash<AsciiString>,
	Rva00460C00ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva00460C00Value> > Rva00460C00Table;

// retail 0x00460C00 -- find() is public, _M_find is not, so the public call emits it
Bool BfmeHashFindAnchor00460C00( const Rva00460C00Table &table, const AsciiString &key )
{
	return table.find( key ) != table.end();
}

struct Rva00460CD0Value
{
	AsciiString m_key;
};

struct Rva00460CD0ExtractKey
{
	const AsciiString &operator()( const Rva00460CD0Value &x ) const { return x.m_key; }
};

typedef _STL::hashtable<Rva00460CD0Value, AsciiString, rts::hash<AsciiString>,
	Rva00460CD0ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva00460CD0Value> > Rva00460CD0Table;

// retail 0x00460CD0 -- find() is public, _M_find is not, so the public call emits it
Bool BfmeHashFindAnchor00460CD0( const Rva00460CD0Table &table, const AsciiString &key )
{
	return table.find( key ) != table.end();
}

struct Rva0046A130Value
{
	AsciiString m_key;
};

struct Rva0046A130ExtractKey
{
	const AsciiString &operator()( const Rva0046A130Value &x ) const { return x.m_key; }
};

typedef _STL::hashtable<Rva0046A130Value, AsciiString, rts::hash<AsciiString>,
	Rva0046A130ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva0046A130Value> > Rva0046A130Table;

// retail 0x0046A130 -- find() is public, _M_find is not, so the public call emits it
Bool BfmeHashFindAnchor0046A130( const Rva0046A130Table &table, const AsciiString &key )
{
	return table.find( key ) != table.end();
}

struct Rva0046A200Value
{
	AsciiString m_key;
};

struct Rva0046A200ExtractKey
{
	const AsciiString &operator()( const Rva0046A200Value &x ) const { return x.m_key; }
};

typedef _STL::hashtable<Rva0046A200Value, AsciiString, rts::hash<AsciiString>,
	Rva0046A200ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva0046A200Value> > Rva0046A200Table;

// retail 0x0046A200 -- find() is public, _M_find is not, so the public call emits it
Bool BfmeHashFindAnchor0046A200( const Rva0046A200Table &table, const AsciiString &key )
{
	return table.find( key ) != table.end();
}

struct Rva0046A2D0Value
{
	AsciiString m_key;
};

struct Rva0046A2D0ExtractKey
{
	const AsciiString &operator()( const Rva0046A2D0Value &x ) const { return x.m_key; }
};

typedef _STL::hashtable<Rva0046A2D0Value, AsciiString, rts::hash<AsciiString>,
	Rva0046A2D0ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva0046A2D0Value> > Rva0046A2D0Table;

// retail 0x0046A2D0 -- find() is public, _M_find is not, so the public call emits it
Bool BfmeHashFindAnchor0046A2D0( const Rva0046A2D0Table &table, const AsciiString &key )
{
	return table.find( key ) != table.end();
}

struct Rva0046A3A0Value
{
	AsciiString m_key;
};

struct Rva0046A3A0ExtractKey
{
	const AsciiString &operator()( const Rva0046A3A0Value &x ) const { return x.m_key; }
};

typedef _STL::hashtable<Rva0046A3A0Value, AsciiString, rts::hash<AsciiString>,
	Rva0046A3A0ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva0046A3A0Value> > Rva0046A3A0Table;

// retail 0x0046A3A0 -- find() is public, _M_find is not, so the public call emits it
Bool BfmeHashFindAnchor0046A3A0( const Rva0046A3A0Table &table, const AsciiString &key )
{
	return table.find( key ) != table.end();
}

struct Rva0046A470Value
{
	AsciiString m_key;
};

struct Rva0046A470ExtractKey
{
	const AsciiString &operator()( const Rva0046A470Value &x ) const { return x.m_key; }
};

typedef _STL::hashtable<Rva0046A470Value, AsciiString, rts::hash<AsciiString>,
	Rva0046A470ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva0046A470Value> > Rva0046A470Table;

// retail 0x0046A470 -- find() is public, _M_find is not, so the public call emits it
Bool BfmeHashFindAnchor0046A470( const Rva0046A470Table &table, const AsciiString &key )
{
	return table.find( key ) != table.end();
}

struct Rva0046A540Value
{
	AsciiString m_key;
};

struct Rva0046A540ExtractKey
{
	const AsciiString &operator()( const Rva0046A540Value &x ) const { return x.m_key; }
};

typedef _STL::hashtable<Rva0046A540Value, AsciiString, rts::hash<AsciiString>,
	Rva0046A540ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva0046A540Value> > Rva0046A540Table;

// retail 0x0046A540 -- find() is public, _M_find is not, so the public call emits it
Bool BfmeHashFindAnchor0046A540( const Rva0046A540Table &table, const AsciiString &key )
{
	return table.find( key ) != table.end();
}

struct Rva0046A610Value
{
	AsciiString m_key;
};

struct Rva0046A610ExtractKey
{
	const AsciiString &operator()( const Rva0046A610Value &x ) const { return x.m_key; }
};

typedef _STL::hashtable<Rva0046A610Value, AsciiString, rts::hash<AsciiString>,
	Rva0046A610ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva0046A610Value> > Rva0046A610Table;

// retail 0x0046A610 -- find() is public, _M_find is not, so the public call emits it
Bool BfmeHashFindAnchor0046A610( const Rva0046A610Table &table, const AsciiString &key )
{
	return table.find( key ) != table.end();
}

struct Rva00583580Value
{
	AsciiString m_key;
};

struct Rva00583580ExtractKey
{
	const AsciiString &operator()( const Rva00583580Value &x ) const { return x.m_key; }
};

typedef _STL::hashtable<Rva00583580Value, AsciiString, rts::hash<AsciiString>,
	Rva00583580ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva00583580Value> > Rva00583580Table;

// retail 0x00583580 -- find() is public, _M_find is not, so the public call emits it
Bool BfmeHashFindAnchor00583580( const Rva00583580Table &table, const AsciiString &key )
{
	return table.find( key ) != table.end();
}

struct Rva00613AE0Value
{
	AsciiString m_key;
};

struct Rva00613AE0ExtractKey
{
	const AsciiString &operator()( const Rva00613AE0Value &x ) const { return x.m_key; }
};

typedef _STL::hashtable<Rva00613AE0Value, AsciiString, rts::hash<AsciiString>,
	Rva00613AE0ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva00613AE0Value> > Rva00613AE0Table;

// retail 0x00613AE0 -- find() is public, _M_find is not, so the public call emits it
Bool BfmeHashFindAnchor00613AE0( const Rva00613AE0Table &table, const AsciiString &key )
{
	return table.find( key ) != table.end();
}

struct Rva00613BB0Value
{
	AsciiString m_key;
};

struct Rva00613BB0ExtractKey
{
	const AsciiString &operator()( const Rva00613BB0Value &x ) const { return x.m_key; }
};

typedef _STL::hashtable<Rva00613BB0Value, AsciiString, rts::hash<AsciiString>,
	Rva00613BB0ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva00613BB0Value> > Rva00613BB0Table;

// retail 0x00613BB0 -- find() is public, _M_find is not, so the public call emits it
Bool BfmeHashFindAnchor00613BB0( const Rva00613BB0Table &table, const AsciiString &key )
{
	return table.find( key ) != table.end();
}

struct Rva006931A0Value
{
	AsciiString m_key;
};

struct Rva006931A0ExtractKey
{
	const AsciiString &operator()( const Rva006931A0Value &x ) const { return x.m_key; }
};

typedef _STL::hashtable<Rva006931A0Value, AsciiString, rts::hash<AsciiString>,
	Rva006931A0ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva006931A0Value> > Rva006931A0Table;

// retail 0x006931A0 -- find() is public, _M_find is not, so the public call emits it
Bool BfmeHashFindAnchor006931A0( const Rva006931A0Table &table, const AsciiString &key )
{
	return table.find( key ) != table.end();
}

struct Rva006A7F80Value
{
	AsciiString m_key;
};

struct Rva006A7F80ExtractKey
{
	const AsciiString &operator()( const Rva006A7F80Value &x ) const { return x.m_key; }
};

typedef _STL::hashtable<Rva006A7F80Value, AsciiString, rts::hash<AsciiString>,
	Rva006A7F80ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva006A7F80Value> > Rva006A7F80Table;

// retail 0x006A7F80 -- find() is public, _M_find is not, so the public call emits it
Bool BfmeHashFindAnchor006A7F80( const Rva006A7F80Table &table, const AsciiString &key )
{
	return table.find( key ) != table.end();
}

struct Rva006A8050Value
{
	AsciiString m_key;
};

struct Rva006A8050ExtractKey
{
	const AsciiString &operator()( const Rva006A8050Value &x ) const { return x.m_key; }
};

typedef _STL::hashtable<Rva006A8050Value, AsciiString, rts::hash<AsciiString>,
	Rva006A8050ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva006A8050Value> > Rva006A8050Table;

// retail 0x006A8050 -- find() is public, _M_find is not, so the public call emits it
Bool BfmeHashFindAnchor006A8050( const Rva006A8050Table &table, const AsciiString &key )
{
	return table.find( key ) != table.end();
}

