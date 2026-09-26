// cl: /DNDEBUG /MD /GX

// Open-BFME5: 31 by-value string accessors, 32 or 35 bytes each.  Every one
// carried only a machine byte-dump row; over a hundred bodies of exactly this
// shape are already converted, in native_network.cpp and lanapi.cpp among
// others.
//
// The whole body is one return: copy-construct the caller's return slot from a
// string that lives at a fixed offset inside the object.  `add ecx, N` is that
// offset and it is the only thing that varies between them -- 35 bytes rather
// than 32 wherever N needs a dword instead of a byte.
//
// The copy constructor names the string.  Twenty-one reach 0x00887B60, which is
// the four-byte narrow string's; two reach 0x00888400 and one 0x004FB220, both
// wide.  Seven reach copy constructors that are themselves still dumps, so
// those get a string class of their own with the constructor pinned to the
// address the body calls -- four bytes wide and copied out of line, which is
// all the call proves.
//
// The HOSTS are not recovered at all.  Nothing in 32 bytes says what object
// holds the string, only that it holds one at that offset, so each host is a
// class named for the address of its accessor.

namespace _STL
{

template <class Character>
class char_traits
{
};

template <class Character>
class allocator
{
};

// The destructor is what makes these bodies 32 bytes rather than 24: with
// exceptions on, a by-value return of a type that has one needs an unwind state
// slot, which is the `push ecx` and the zero stored into it.
template <class Character, class Traits, class Alloc>
class basic_string
{
public:
	basic_string( const basic_string &other );
	~basic_string();
};

}

template <class Character>
class StringBase
{
public:
	StringBase( const StringBase &other );
	~StringBase();
};

// One of the public names the 0x00887B60 fold already carries in the ledger.
template <class Character>
class BFMERetailStringBase
{
public:
	BFMERetailStringBase( const BFMERetailStringBase &other );
	~BFMERetailStringBase();
};

// 0x00887B60 and 0x004FB1B0 are BOTH four-byte-string copy constructors and
// they are NOT the same function -- 121 bytes against 86.  The first is the
// identical-code-folding group the ledger already knows as StringBase<char>'s,
// reached under half a dozen public names; the second is _STL::basic_string's.
// Twenty-one of these accessors call the first and five the second, so they
// return different string classes and are spelled that way.
typedef BFMERetailStringBase<char> BfmeRetailNarrowString;
typedef _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> >
	BfmeNarrowString;
typedef _STL::basic_string<unsigned short, _STL::char_traits<unsigned short>,
	_STL::allocator<unsigned short> > BfmeWideString;
typedef StringBase<unsigned short> BfmeWideStringBase;

class Rva00083DA0Host
{
public:
	BfmeWideStringBase copyStringAt1280( void );
};

// retail 0x00083DA0, the string at +0x1280
BfmeWideStringBase Rva00083DA0Host::copyStringAt1280( void )
{
	return *reinterpret_cast<const BfmeWideStringBase *>(
		reinterpret_cast<const char *>( this ) + 0x1280 );
}

class Rva0009F820String
{
public:
	Rva0009F820String( const Rva0009F820String &other );
	~Rva0009F820String();
};

class Rva0009F820Host
{
public:
	Rva0009F820String copyStringAt14( void );
};

// retail 0x0009F820, the string at +0x14
Rva0009F820String Rva0009F820Host::copyStringAt14( void )
{
	return *reinterpret_cast<const Rva0009F820String *>(
		reinterpret_cast<const char *>( this ) + 0x14 );
}

class Rva00193D20Host
{
public:
	BfmeRetailNarrowString copyStringAt30( void );
};

// retail 0x00193D20, the string at +0x30
BfmeRetailNarrowString Rva00193D20Host::copyStringAt30( void )
{
	return *reinterpret_cast<const BfmeRetailNarrowString *>(
		reinterpret_cast<const char *>( this ) + 0x30 );
}

class Rva001A6F90Host
{
public:
	BfmeRetailNarrowString copyStringAt54( void );
};

// retail 0x001A6F90, the string at +0x54
BfmeRetailNarrowString Rva001A6F90Host::copyStringAt54( void )
{
	return *reinterpret_cast<const BfmeRetailNarrowString *>(
		reinterpret_cast<const char *>( this ) + 0x54 );
}

class Rva001A6FC0Host
{
public:
	BfmeRetailNarrowString copyStringAt58( void );
};

// retail 0x001A6FC0, the string at +0x58
BfmeRetailNarrowString Rva001A6FC0Host::copyStringAt58( void )
{
	return *reinterpret_cast<const BfmeRetailNarrowString *>(
		reinterpret_cast<const char *>( this ) + 0x58 );
}

class Rva001C42B0Host
{
public:
	BfmeRetailNarrowString copyStringAt270( void );
};

// retail 0x001C42B0, the string at +0x270
BfmeRetailNarrowString Rva001C42B0Host::copyStringAt270( void )
{
	return *reinterpret_cast<const BfmeRetailNarrowString *>(
		reinterpret_cast<const char *>( this ) + 0x270 );
}

class Rva00235D20Host
{
public:
	BfmeRetailNarrowString copyStringAt240( void );
};

// retail 0x00235D20, the string at +0x240
BfmeRetailNarrowString Rva00235D20Host::copyStringAt240( void )
{
	return *reinterpret_cast<const BfmeRetailNarrowString *>(
		reinterpret_cast<const char *>( this ) + 0x240 );
}

class Rva00338EF0Host
{
public:
	BfmeRetailNarrowString copyStringAt30( void );
};

// retail 0x00338EF0, the string at +0x30
BfmeRetailNarrowString Rva00338EF0Host::copyStringAt30( void )
{
	return *reinterpret_cast<const BfmeRetailNarrowString *>(
		reinterpret_cast<const char *>( this ) + 0x30 );
}

class Rva0037B100Host
{
public:
	BfmeRetailNarrowString copyStringAtF4( void );
};

// retail 0x0037B100, the string at +0xF4
BfmeRetailNarrowString Rva0037B100Host::copyStringAtF4( void )
{
	return *reinterpret_cast<const BfmeRetailNarrowString *>(
		reinterpret_cast<const char *>( this ) + 0xF4 );
}

class Rva00385F20Host
{
public:
	BfmeWideStringBase copyStringAt418( void );
};

// retail 0x00385F20, the string at +0x418
BfmeWideStringBase Rva00385F20Host::copyStringAt418( void )
{
	return *reinterpret_cast<const BfmeWideStringBase *>(
		reinterpret_cast<const char *>( this ) + 0x418 );
}

class Rva00415BF0Host
{
public:
	BfmeRetailNarrowString copyStringAt7C4( void );
};

// retail 0x00415BF0, the string at +0x7C4
BfmeRetailNarrowString Rva00415BF0Host::copyStringAt7C4( void )
{
	return *reinterpret_cast<const BfmeRetailNarrowString *>(
		reinterpret_cast<const char *>( this ) + 0x7C4 );
}

class Rva00465550Host
{
public:
	BfmeRetailNarrowString copyStringAt254( void );
};

// retail 0x00465550, the string at +0x254
BfmeRetailNarrowString Rva00465550Host::copyStringAt254( void )
{
	return *reinterpret_cast<const BfmeRetailNarrowString *>(
		reinterpret_cast<const char *>( this ) + 0x254 );
}

class Rva004A3C00Host
{
public:
	BfmeRetailNarrowString copyStringAt184( void );
};

// retail 0x004A3C00, the string at +0x184
BfmeRetailNarrowString Rva004A3C00Host::copyStringAt184( void )
{
	return *reinterpret_cast<const BfmeRetailNarrowString *>(
		reinterpret_cast<const char *>( this ) + 0x184 );
}

class Rva004D7AC0Host
{
public:
	BfmeRetailNarrowString copyStringAt444( void );
};

// retail 0x004D7AC0, the string at +0x444
BfmeRetailNarrowString Rva004D7AC0Host::copyStringAt444( void )
{
	return *reinterpret_cast<const BfmeRetailNarrowString *>(
		reinterpret_cast<const char *>( this ) + 0x444 );
}

class Rva00537630String
{
public:
	Rva00537630String( const Rva00537630String &other );
	~Rva00537630String();
};

class Rva00537630Host
{
public:
	Rva00537630String copyStringAt20( void );
};

// retail 0x00537630, the string at +0x20
Rva00537630String Rva00537630Host::copyStringAt20( void )
{
	return *reinterpret_cast<const Rva00537630String *>(
		reinterpret_cast<const char *>( this ) + 0x20 );
}

class Rva00629ED0Host
{
public:
	BfmeRetailNarrowString copyStringAt8C( void );
};

// retail 0x00629ED0, the string at +0x8C
BfmeRetailNarrowString Rva00629ED0Host::copyStringAt8C( void )
{
	return *reinterpret_cast<const BfmeRetailNarrowString *>(
		reinterpret_cast<const char *>( this ) + 0x8C );
}

class Rva0062C8B0Host
{
public:
	BfmeRetailNarrowString copyStringAt448( void );
};

// retail 0x0062C8B0, the string at +0x448
BfmeRetailNarrowString Rva0062C8B0Host::copyStringAt448( void )
{
	return *reinterpret_cast<const BfmeRetailNarrowString *>(
		reinterpret_cast<const char *>( this ) + 0x448 );
}

class Rva006372A0Host
{
public:
	BfmeRetailNarrowString copyStringAt6C( void );
};

// retail 0x006372A0, the string at +0x6C
BfmeRetailNarrowString Rva006372A0Host::copyStringAt6C( void )
{
	return *reinterpret_cast<const BfmeRetailNarrowString *>(
		reinterpret_cast<const char *>( this ) + 0x6C );
}

class Rva00637360Host
{
public:
	BfmeRetailNarrowString copyStringAt74( void );
};

// retail 0x00637360, the string at +0x74
BfmeRetailNarrowString Rva00637360Host::copyStringAt74( void )
{
	return *reinterpret_cast<const BfmeRetailNarrowString *>(
		reinterpret_cast<const char *>( this ) + 0x74 );
}

class Rva00637450Host
{
public:
	BfmeRetailNarrowString copyStringAt7C( void );
};

// retail 0x00637450, the string at +0x7C
BfmeRetailNarrowString Rva00637450Host::copyStringAt7C( void )
{
	return *reinterpret_cast<const BfmeRetailNarrowString *>(
		reinterpret_cast<const char *>( this ) + 0x7C );
}

class Rva006380C0Host
{
public:
	BfmeRetailNarrowString copyStringAt74( void );
};

// retail 0x006380C0, the string at +0x74
BfmeRetailNarrowString Rva006380C0Host::copyStringAt74( void )
{
	return *reinterpret_cast<const BfmeRetailNarrowString *>(
		reinterpret_cast<const char *>( this ) + 0x74 );
}

class Rva00647720Host
{
public:
	BfmeNarrowString copyStringAtB0( void );
};

// retail 0x00647720, the string at +0xB0
BfmeNarrowString Rva00647720Host::copyStringAtB0( void )
{
	return *reinterpret_cast<const BfmeNarrowString *>(
		reinterpret_cast<const char *>( this ) + 0xB0 );
}

class Rva00647750Host
{
public:
	BfmeNarrowString copyStringAtC0( void );
};

// retail 0x00647750, the string at +0xC0
BfmeNarrowString Rva00647750Host::copyStringAtC0( void )
{
	return *reinterpret_cast<const BfmeNarrowString *>(
		reinterpret_cast<const char *>( this ) + 0xC0 );
}

class Rva00647780Host
{
public:
	BfmeWideString copyStringAt218( void );
};

// retail 0x00647780, the string at +0x218
BfmeWideString Rva00647780Host::copyStringAt218( void )
{
	return *reinterpret_cast<const BfmeWideString *>(
		reinterpret_cast<const char *>( this ) + 0x218 );
}

class Rva006477B0Host
{
public:
	BfmeNarrowString copyStringAt14C( void );
};

// retail 0x006477B0, the string at +0x14C
BfmeNarrowString Rva006477B0Host::copyStringAt14C( void )
{
	return *reinterpret_cast<const BfmeNarrowString *>(
		reinterpret_cast<const char *>( this ) + 0x14C );
}

class Rva006477E0Host
{
public:
	BfmeNarrowString copyStringAt140( void );
};

// retail 0x006477E0, the string at +0x140
BfmeNarrowString Rva006477E0Host::copyStringAt140( void )
{
	return *reinterpret_cast<const BfmeNarrowString *>(
		reinterpret_cast<const char *>( this ) + 0x140 );
}

class Rva00647920Host
{
public:
	BfmeNarrowString copyStringAt3CC( void );
};

// retail 0x00647920, the string at +0x3CC
BfmeNarrowString Rva00647920Host::copyStringAt3CC( void )
{
	return *reinterpret_cast<const BfmeNarrowString *>(
		reinterpret_cast<const char *>( this ) + 0x3CC );
}

class Rva0068AEC0Host
{
public:
	BfmeRetailNarrowString copyStringAt60( void );
};

// retail 0x0068AEC0, the string at +0x60
BfmeRetailNarrowString Rva0068AEC0Host::copyStringAt60( void )
{
	return *reinterpret_cast<const BfmeRetailNarrowString *>(
		reinterpret_cast<const char *>( this ) + 0x60 );
}

class Rva006E22E0Host
{
public:
	BfmeRetailNarrowString copyStringAt9C( void );
};

// retail 0x006E22E0, the string at +0x9C
BfmeRetailNarrowString Rva006E22E0Host::copyStringAt9C( void )
{
	return *reinterpret_cast<const BfmeRetailNarrowString *>(
		reinterpret_cast<const char *>( this ) + 0x9C );
}

class Rva00751390Host
{
public:
	BfmeRetailNarrowString copyStringAt5C( void );
};

// retail 0x00751390, the string at +0x5C
BfmeRetailNarrowString Rva00751390Host::copyStringAt5C( void )
{
	return *reinterpret_cast<const BfmeRetailNarrowString *>(
		reinterpret_cast<const char *>( this ) + 0x5C );
}

class Rva00759500Host
{
public:
	// retail returns with `ret 8`, so this one takes an argument it never reads
	BfmeRetailNarrowString copyStringAt8( int unused );
};

// retail 0x00759500, the string at +0x8
BfmeRetailNarrowString Rva00759500Host::copyStringAt8( int )
{
	return *reinterpret_cast<const BfmeRetailNarrowString *>(
		reinterpret_cast<const char *>( this ) + 0x8 );
}

