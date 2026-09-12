// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport

// Open-BFME5: STLport hashtable<V, AsciiString>::_M_insert, 22 bodies of 114
// bytes.  Every one carried only a machine byte-dump row.
//
// Four calls and the layout falls out of them.  resize for one more element
// first, then the bucket index -- which is a CALL here, not the inline divide
// the scalar-keyed sibling at 0x000675E0 compiles to, because
// rts::hash<AsciiString> takes its key by value and is itself out of line.
// Then twelve bytes for the node and the value copy-constructed into it at +4,
// which is why the next pointer is cleared before the call and only linked to
// the old bucket head after.
//
// Twelve bytes of node is four of next pointer and eight of value, and eight
// bytes of value beside a four-byte AsciiString key leaves four for the mapped
// type.  Four of the twenty-two allocate 0x10, 0x18 or 0x34 instead, which is
// the same arithmetic at 8, 16 and 44 bytes of mapped type.  That is the whole of what these bodies say about it -- so it is a
// four-byte member named for the address of the body, reached through the
// table's own extract-key functor rather than an asserted pair.

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
	AsciiString(const AsciiString &other) : m_data(other.m_data) {}

	int compare(const AsciiString &str) const
	{
		const int len = str.m_data.m_data ? str.m_data.m_data->length : 0;
		const char *data = str.m_data.m_data ? &str.m_data.m_data->data[0] : "";
		const int myLen = m_data.m_data ? m_data.m_data->length : 0;
		const char *myData = m_data.m_data ? &m_data.m_data->data[0] : "";
		const int result = memcmp(myData, data, myLen < len ? myLen : len);
		if (result != 0) {
			return result;
		}
		return myLen - len;
	}

	StringBase<char> m_data;
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

struct Rva000B8AE0Value
{
	AsciiString m_key;
	int m_mapped;
};

struct Rva000B8AE0ExtractKey
{
	const AsciiString &operator()( const Rva000B8AE0Value &entry ) const { return entry.m_key; }
};

typedef _STL::hashtable<Rva000B8AE0Value, AsciiString, rts::hash<AsciiString>,
	Rva000B8AE0ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva000B8AE0Value> > AsciiStringIntHash000B8AE0;

// retail 0x000B8AE0
void BfmeHashInsertAnchor000B8AE0( AsciiStringIntHash000B8AE0 &table, const Rva000B8AE0Value &value )
{
	table._M_insert( value );
}

struct Rva000D6770Value
{
	AsciiString m_key;
	int m_mapped;
};

struct Rva000D6770ExtractKey
{
	const AsciiString &operator()( const Rva000D6770Value &entry ) const { return entry.m_key; }
};

typedef _STL::hashtable<Rva000D6770Value, AsciiString, rts::hash<AsciiString>,
	Rva000D6770ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva000D6770Value> > AsciiStringIntHash000D6770;

// retail 0x000D6770
void BfmeHashInsertAnchor000D6770( AsciiStringIntHash000D6770 &table, const Rva000D6770Value &value )
{
	table._M_insert( value );
}

struct Rva000D6C60Value
{
	AsciiString m_key;
	int m_mapped;
};

struct Rva000D6C60ExtractKey
{
	const AsciiString &operator()( const Rva000D6C60Value &entry ) const { return entry.m_key; }
};

typedef _STL::hashtable<Rva000D6C60Value, AsciiString, rts::hash<AsciiString>,
	Rva000D6C60ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva000D6C60Value> > AsciiStringIntHash000D6C60;

// retail 0x000D6C60
void BfmeHashInsertAnchor000D6C60( AsciiStringIntHash000D6C60 &table, const Rva000D6C60Value &value )
{
	table._M_insert( value );
}

struct Rva000F6C10Value
{
	AsciiString m_key;
	int m_mapped;
};

struct Rva000F6C10ExtractKey
{
	const AsciiString &operator()( const Rva000F6C10Value &entry ) const { return entry.m_key; }
};

typedef _STL::hashtable<Rva000F6C10Value, AsciiString, rts::hash<AsciiString>,
	Rva000F6C10ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva000F6C10Value> > AsciiStringIntHash000F6C10;

// retail 0x000F6C10
void BfmeHashInsertAnchor000F6C10( AsciiStringIntHash000F6C10 &table, const Rva000F6C10Value &value )
{
	table._M_insert( value );
}

struct Rva001360E0Value
{
	AsciiString m_key;
	int m_mapped;
};

struct Rva001360E0ExtractKey
{
	const AsciiString &operator()( const Rva001360E0Value &entry ) const { return entry.m_key; }
};

typedef _STL::hashtable<Rva001360E0Value, AsciiString, rts::hash<AsciiString>,
	Rva001360E0ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva001360E0Value> > AsciiStringIntHash001360E0;

// retail 0x001360E0
void BfmeHashInsertAnchor001360E0( AsciiStringIntHash001360E0 &table, const Rva001360E0Value &value )
{
	table._M_insert( value );
}

struct Rva0038ED80Value
{
	AsciiString m_key;
	int m_mapped;
};

struct Rva0038ED80ExtractKey
{
	const AsciiString &operator()( const Rva0038ED80Value &entry ) const { return entry.m_key; }
};

typedef _STL::hashtable<Rva0038ED80Value, AsciiString, rts::hash<AsciiString>,
	Rva0038ED80ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva0038ED80Value> > AsciiStringIntHash0038ED80;

// retail 0x0038ED80
void BfmeHashInsertAnchor0038ED80( AsciiStringIntHash0038ED80 &table, const Rva0038ED80Value &value )
{
	table._M_insert( value );
}

struct Rva0038EE10Value
{
	AsciiString m_key;
	int m_mapped;
};

struct Rva0038EE10ExtractKey
{
	const AsciiString &operator()( const Rva0038EE10Value &entry ) const { return entry.m_key; }
};

typedef _STL::hashtable<Rva0038EE10Value, AsciiString, rts::hash<AsciiString>,
	Rva0038EE10ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva0038EE10Value> > AsciiStringIntHash0038EE10;

// retail 0x0038EE10
void BfmeHashInsertAnchor0038EE10( AsciiStringIntHash0038EE10 &table, const Rva0038EE10Value &value )
{
	table._M_insert( value );
}

struct Rva00461250Value
{
	AsciiString m_key;
	int m_mapped;
};

struct Rva00461250ExtractKey
{
	const AsciiString &operator()( const Rva00461250Value &entry ) const { return entry.m_key; }
};

typedef _STL::hashtable<Rva00461250Value, AsciiString, rts::hash<AsciiString>,
	Rva00461250ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva00461250Value> > AsciiStringIntHash00461250;

// retail 0x00461250
void BfmeHashInsertAnchor00461250( AsciiStringIntHash00461250 &table, const Rva00461250Value &value )
{
	table._M_insert( value );
}

struct Rva004613F0Value
{
	AsciiString m_key;
	int m_mapped;
};

struct Rva004613F0ExtractKey
{
	const AsciiString &operator()( const Rva004613F0Value &entry ) const { return entry.m_key; }
};

typedef _STL::hashtable<Rva004613F0Value, AsciiString, rts::hash<AsciiString>,
	Rva004613F0ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva004613F0Value> > AsciiStringIntHash004613F0;

// retail 0x004613F0
void BfmeHashInsertAnchor004613F0( AsciiStringIntHash004613F0 &table, const Rva004613F0Value &value )
{
	table._M_insert( value );
}

struct Rva00469D20Value
{
	AsciiString m_key;
	int m_mapped;
};

struct Rva00469D20ExtractKey
{
	const AsciiString &operator()( const Rva00469D20Value &entry ) const { return entry.m_key; }
};

typedef _STL::hashtable<Rva00469D20Value, AsciiString, rts::hash<AsciiString>,
	Rva00469D20ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva00469D20Value> > AsciiStringIntHash00469D20;

// retail 0x00469D20
void BfmeHashInsertAnchor00469D20( AsciiStringIntHash00469D20 &table, const Rva00469D20Value &value )
{
	table._M_insert( value );
}

struct Rva00469FC0Value
{
	AsciiString m_key;
	int m_mapped;
};

struct Rva00469FC0ExtractKey
{
	const AsciiString &operator()( const Rva00469FC0Value &entry ) const { return entry.m_key; }
};

typedef _STL::hashtable<Rva00469FC0Value, AsciiString, rts::hash<AsciiString>,
	Rva00469FC0ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva00469FC0Value> > AsciiStringIntHash00469FC0;

// retail 0x00469FC0
void BfmeHashInsertAnchor00469FC0( AsciiStringIntHash00469FC0 &table, const Rva00469FC0Value &value )
{
	table._M_insert( value );
}

struct Rva0046AF20Value
{
	AsciiString m_key;
	int m_mapped;
};

struct Rva0046AF20ExtractKey
{
	const AsciiString &operator()( const Rva0046AF20Value &entry ) const { return entry.m_key; }
};

typedef _STL::hashtable<Rva0046AF20Value, AsciiString, rts::hash<AsciiString>,
	Rva0046AF20ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva0046AF20Value> > AsciiStringIntHash0046AF20;

// retail 0x0046AF20
void BfmeHashInsertAnchor0046AF20( AsciiStringIntHash0046AF20 &table, const Rva0046AF20Value &value )
{
	table._M_insert( value );
}

struct Rva0046C000Value
{
	AsciiString m_key;
	int m_mapped;
};

struct Rva0046C000ExtractKey
{
	const AsciiString &operator()( const Rva0046C000Value &entry ) const { return entry.m_key; }
};

typedef _STL::hashtable<Rva0046C000Value, AsciiString, rts::hash<AsciiString>,
	Rva0046C000ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva0046C000Value> > AsciiStringIntHash0046C000;

// retail 0x0046C000
void BfmeHashInsertAnchor0046C000( AsciiStringIntHash0046C000 &table, const Rva0046C000Value &value )
{
	table._M_insert( value );
}

struct Rva0046C540Value
{
	AsciiString m_key;
	int m_mapped;
};

struct Rva0046C540ExtractKey
{
	const AsciiString &operator()( const Rva0046C540Value &entry ) const { return entry.m_key; }
};

typedef _STL::hashtable<Rva0046C540Value, AsciiString, rts::hash<AsciiString>,
	Rva0046C540ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva0046C540Value> > AsciiStringIntHash0046C540;

// retail 0x0046C540
void BfmeHashInsertAnchor0046C540( AsciiStringIntHash0046C540 &table, const Rva0046C540Value &value )
{
	table._M_insert( value );
}

struct Rva00614BC0Value
{
	AsciiString m_key;
	int m_mapped;
};

struct Rva00614BC0ExtractKey
{
	const AsciiString &operator()( const Rva00614BC0Value &entry ) const { return entry.m_key; }
};

typedef _STL::hashtable<Rva00614BC0Value, AsciiString, rts::hash<AsciiString>,
	Rva00614BC0ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva00614BC0Value> > AsciiStringIntHash00614BC0;

// retail 0x00614BC0
void BfmeHashInsertAnchor00614BC0( AsciiStringIntHash00614BC0 &table, const Rva00614BC0Value &value )
{
	table._M_insert( value );
}

struct Rva00614D10Value
{
	AsciiString m_key;
	int m_mapped;
};

struct Rva00614D10ExtractKey
{
	const AsciiString &operator()( const Rva00614D10Value &entry ) const { return entry.m_key; }
};

typedef _STL::hashtable<Rva00614D10Value, AsciiString, rts::hash<AsciiString>,
	Rva00614D10ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva00614D10Value> > AsciiStringIntHash00614D10;

// retail 0x00614D10
void BfmeHashInsertAnchor00614D10( AsciiStringIntHash00614D10 &table, const Rva00614D10Value &value )
{
	table._M_insert( value );
}

struct Rva00693020Value
{
	AsciiString m_key;
	int m_mapped;
};

struct Rva00693020ExtractKey
{
	const AsciiString &operator()( const Rva00693020Value &entry ) const { return entry.m_key; }
};

typedef _STL::hashtable<Rva00693020Value, AsciiString, rts::hash<AsciiString>,
	Rva00693020ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva00693020Value> > AsciiStringIntHash00693020;

// retail 0x00693020
void BfmeHashInsertAnchor00693020( AsciiStringIntHash00693020 &table, const Rva00693020Value &value )
{
	table._M_insert( value );
}

struct Rva006A7AD0Value
{
	AsciiString m_key;
	int m_mapped;
};

struct Rva006A7AD0ExtractKey
{
	const AsciiString &operator()( const Rva006A7AD0Value &entry ) const { return entry.m_key; }
};

typedef _STL::hashtable<Rva006A7AD0Value, AsciiString, rts::hash<AsciiString>,
	Rva006A7AD0ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva006A7AD0Value> > AsciiStringIntHash006A7AD0;

// retail 0x006A7AD0
void BfmeHashInsertAnchor006A7AD0( AsciiStringIntHash006A7AD0 &table, const Rva006A7AD0Value &value )
{
	table._M_insert( value );
}

struct Rva00461360Value
{
	AsciiString m_key;
	char m_mapped[ 44 ];
};

struct Rva00461360ExtractKey
{
	const AsciiString &operator()( const Rva00461360Value &entry ) const { return entry.m_key; }
};

typedef _STL::hashtable<Rva00461360Value, AsciiString, rts::hash<AsciiString>,
	Rva00461360ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva00461360Value> > AsciiStringMapped44Hash00461360;

// retail 0x00461360, a 0x34-byte node
void BfmeHashInsertAnchor00461360( AsciiStringMapped44Hash00461360 &table, const Rva00461360Value &value )
{
	table._M_insert( value );
}

struct Rva0046AC80Value
{
	AsciiString m_key;
	char m_mapped[ 8 ];
};

struct Rva0046AC80ExtractKey
{
	const AsciiString &operator()( const Rva0046AC80Value &entry ) const { return entry.m_key; }
};

typedef _STL::hashtable<Rva0046AC80Value, AsciiString, rts::hash<AsciiString>,
	Rva0046AC80ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva0046AC80Value> > AsciiStringMapped8Hash0046AC80;

// retail 0x0046AC80, a 0x10-byte node
void BfmeHashInsertAnchor0046AC80( AsciiStringMapped8Hash0046AC80 &table, const Rva0046AC80Value &value )
{
	table._M_insert( value );
}

struct Rva0046C2A0Value
{
	AsciiString m_key;
	char m_mapped[ 8 ];
};

struct Rva0046C2A0ExtractKey
{
	const AsciiString &operator()( const Rva0046C2A0Value &entry ) const { return entry.m_key; }
};

typedef _STL::hashtable<Rva0046C2A0Value, AsciiString, rts::hash<AsciiString>,
	Rva0046C2A0ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva0046C2A0Value> > AsciiStringMapped8Hash0046C2A0;

// retail 0x0046C2A0, a 0x10-byte node
void BfmeHashInsertAnchor0046C2A0( AsciiStringMapped8Hash0046C2A0 &table, const Rva0046C2A0Value &value )
{
	table._M_insert( value );
}

struct Rva00583B30Value
{
	AsciiString m_key;
	char m_mapped[ 16 ];
};

struct Rva00583B30ExtractKey
{
	const AsciiString &operator()( const Rva00583B30Value &entry ) const { return entry.m_key; }
};

typedef _STL::hashtable<Rva00583B30Value, AsciiString, rts::hash<AsciiString>,
	Rva00583B30ExtractKey, _STL::equal_to<AsciiString>,
	_STL::allocator<Rva00583B30Value> > AsciiStringMapped16Hash00583B30;

// retail 0x00583B30, a 0x18-byte node
void BfmeHashInsertAnchor00583B30( AsciiStringMapped16Hash00583B30 &table, const Rva00583B30Value &value )
{
	table._M_insert( value );
}

