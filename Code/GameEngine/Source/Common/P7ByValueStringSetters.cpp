// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: twenty one-line setters that take a STRING BY VALUE and hand it
// to a string member.
//
// Everything about the shape is forced by the by-value parameter.  MSVC makes
// the CALLEE destroy a by-value class argument, so each body ends by calling
// the string destructor on the incoming slot -- `lea ecx,[esp+0x10]` is that
// slot, not a local -- and the exception frame with its two states, 0 across
// the set and -1 after, exists only to run that destructor if the set throws.
// Nothing else in these functions needs EH at all.
//
// THE TWO CALLEES NAME THE TYPES.  0x00887C90 and 0x00887940 are
// StringBase<char>'s set and destructor; 0x00888530 and 0x008881D0 are
// StringBase<unsigned short>'s.  Seventeen of the twenty are narrow and three
// are wide, and the destructor is PRIVATE in both (the ledger's `AAE`), which
// is why the derived string is a friend here rather than the base's
// destructor being protected -- that spelling would mangle as IAE and stop
// resolving.
//
// THE MEMBER MUST BE BOUND AS A REFERENCE FIRST.  Written `m_bfmeText.set(
// value )` the compiler pushes the argument and then forms `this + K`;
// retail forms `this + K` FIRST and pushes after.  Same two instructions,
// opposite order, and binding `StringBase<char> &text = m_bfmeText;` ahead of
// the call is what puts them in retail's order.  The same lever fixed
// P6MemberVectorPushBack.cpp, where it was worth two bytes rather than a
// transposition.
//
// ONE AXIS: the member's offset, 0x10 through 0x444.  The 75/78 split is that
// offset crossing into imm32.
//
// IDENTITY IS NOT RECOVERED for the owners; each is named for its own address
// and `char m_bfmeHead[K]` carries the offset and nothing else.

template <class CharType>
class StringBase
{
public:
	void set( const StringBase &other );		// narrow 0x00887C90, wide 0x00888530

private:
	~StringBase();				// narrow 0x00887940, wide 0x008881D0

	CharType *m_data;

	friend class AsciiString;
	friend class UnicodeString;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : public StringBase<char>
{
public:
	AsciiString( const AsciiString &other );
	~AsciiString() {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString : public StringBase<unsigned short>
{
public:
	UnicodeString( const UnicodeString &other );
	~UnicodeString() {}
};

class Gen00193CC0
{
public:
	void bfmeSet( AsciiString value );

private:
	char m_bfmeHead[ 0x30 ];
	AsciiString m_bfmeText;			// +0x30
};

class Gen001C4240
{
public:
	void bfmeSet( AsciiString value );

private:
	char m_bfmeHead[ 0x240 ];
	AsciiString m_bfmeText;			// +0x240
};

class Gen0022A620
{
public:
	void bfmeSet( AsciiString value );

private:
	char m_bfmeHead[ 0x328 ];
	AsciiString m_bfmeText;			// +0x328
};

class Gen002BA170
{
public:
	void bfmeSet( AsciiString value );

private:
	char m_bfmeHead[ 0x32C ];
	AsciiString m_bfmeText;			// +0x32C
};

class Gen002E3FD0
{
public:
	void bfmeSet( AsciiString value );

private:
	char m_bfmeHead[ 0x10 ];
	AsciiString m_bfmeText;			// +0x10
};

class Gen00338F20
{
public:
	void bfmeSet( AsciiString value );

private:
	char m_bfmeHead[ 0x30 ];
	AsciiString m_bfmeText;			// +0x30
};

class Gen0036B0E0
{
public:
	void bfmeSet( AsciiString value );

private:
	char m_bfmeHead[ 0x10 ];
	AsciiString m_bfmeText;			// +0x10
};

class Gen0040F660
{
public:
	void bfmeSet( AsciiString value );

private:
	char m_bfmeHead[ 0xEC ];
	AsciiString m_bfmeText;			// +0xEC
};

class Gen00489B60
{
public:
	void bfmeSet( AsciiString value );

private:
	char m_bfmeHead[ 0x10 ];
	AsciiString m_bfmeText;			// +0x10
};

class Gen004D4810
{
public:
	void bfmeSet( AsciiString value );

private:
	char m_bfmeHead[ 0x444 ];
	AsciiString m_bfmeText;			// +0x444
};

class Gen004D4880
{
public:
	void bfmeSet( UnicodeString value );

private:
	char m_bfmeHead[ 0x418 ];
	UnicodeString m_bfmeText;			// +0x418
};

class Gen00505D40
{
public:
	void bfmeSet( AsciiString value );

private:
	char m_bfmeHead[ 0x4C ];
	AsciiString m_bfmeText;			// +0x4C
};

class Gen006018F0
{
public:
	void bfmeSet( AsciiString value );

private:
	char m_bfmeHead[ 0x4C ];
	AsciiString m_bfmeText;			// +0x4C
};

class Gen006019B0
{
public:
	void bfmeSet( AsciiString value );

private:
	char m_bfmeHead[ 0x48 ];
	AsciiString m_bfmeText;			// +0x48
};

class Gen006312E0
{
public:
	void bfmeSet( AsciiString value );

private:
	char m_bfmeHead[ 0x424 ];
	AsciiString m_bfmeText;			// +0x424
};

class Gen00637390
{
public:
	void bfmeSet( AsciiString value );

private:
	char m_bfmeHead[ 0x74 ];
	AsciiString m_bfmeText;			// +0x74
};

class Gen00637FD0
{
public:
	void bfmeSet( AsciiString value );

private:
	char m_bfmeHead[ 0x48 ];
	AsciiString m_bfmeText;			// +0x48
};

class Gen0068AE60
{
public:
	void bfmeSet( AsciiString value );

private:
	char m_bfmeHead[ 0x60 ];
	AsciiString m_bfmeText;			// +0x60
};

class Gen0068DD60
{
public:
	void bfmeSet( UnicodeString value );

private:
	char m_bfmeHead[ 0x48 ];
	UnicodeString m_bfmeText;			// +0x48
};

class Gen0068DDC0
{
public:
	void bfmeSet( UnicodeString value );

private:
	char m_bfmeHead[ 0x4C ];
	UnicodeString m_bfmeText;			// +0x4C
};

// ?bfmeSet@Gen00193CC0@@QAEXVAsciiString@@@Z		75B
void Gen00193CC0::bfmeSet( AsciiString value )
{
	StringBase<char> &text = m_bfmeText;

	text.set( value );
}

// ?bfmeSet@Gen001C4240@@QAEXVAsciiString@@@Z		78B
void Gen001C4240::bfmeSet( AsciiString value )
{
	StringBase<char> &text = m_bfmeText;

	text.set( value );
}

// ?bfmeSet@Gen0022A620@@QAEXVAsciiString@@@Z		78B
void Gen0022A620::bfmeSet( AsciiString value )
{
	StringBase<char> &text = m_bfmeText;

	text.set( value );
}

// ?bfmeSet@Gen002BA170@@QAEXVAsciiString@@@Z		78B
void Gen002BA170::bfmeSet( AsciiString value )
{
	StringBase<char> &text = m_bfmeText;

	text.set( value );
}

// ?bfmeSet@Gen002E3FD0@@QAEXVAsciiString@@@Z		75B
void Gen002E3FD0::bfmeSet( AsciiString value )
{
	StringBase<char> &text = m_bfmeText;

	text.set( value );
}

// ?bfmeSet@Gen00338F20@@QAEXVAsciiString@@@Z		75B
void Gen00338F20::bfmeSet( AsciiString value )
{
	StringBase<char> &text = m_bfmeText;

	text.set( value );
}

// ?bfmeSet@Gen0036B0E0@@QAEXVAsciiString@@@Z		75B
void Gen0036B0E0::bfmeSet( AsciiString value )
{
	StringBase<char> &text = m_bfmeText;

	text.set( value );
}

// ?bfmeSet@Gen0040F660@@QAEXVAsciiString@@@Z		78B
void Gen0040F660::bfmeSet( AsciiString value )
{
	StringBase<char> &text = m_bfmeText;

	text.set( value );
}

// ?bfmeSet@Gen00489B60@@QAEXVAsciiString@@@Z		75B
void Gen00489B60::bfmeSet( AsciiString value )
{
	StringBase<char> &text = m_bfmeText;

	text.set( value );
}

// ?bfmeSet@Gen004D4810@@QAEXVAsciiString@@@Z		78B
void Gen004D4810::bfmeSet( AsciiString value )
{
	StringBase<char> &text = m_bfmeText;

	text.set( value );
}

// ?bfmeSet@Gen004D4880@@QAEXVUnicodeString@@@Z		78B
void Gen004D4880::bfmeSet( UnicodeString value )
{
	StringBase<unsigned short> &text = m_bfmeText;

	text.set( value );
}

// ?bfmeSet@Gen00505D40@@QAEXVAsciiString@@@Z		75B
void Gen00505D40::bfmeSet( AsciiString value )
{
	StringBase<char> &text = m_bfmeText;

	text.set( value );
}

// ?bfmeSet@Gen006018F0@@QAEXVAsciiString@@@Z		75B
void Gen006018F0::bfmeSet( AsciiString value )
{
	StringBase<char> &text = m_bfmeText;

	text.set( value );
}

// ?bfmeSet@Gen006019B0@@QAEXVAsciiString@@@Z		75B
void Gen006019B0::bfmeSet( AsciiString value )
{
	StringBase<char> &text = m_bfmeText;

	text.set( value );
}

// ?bfmeSet@Gen006312E0@@QAEXVAsciiString@@@Z		78B
void Gen006312E0::bfmeSet( AsciiString value )
{
	StringBase<char> &text = m_bfmeText;

	text.set( value );
}

// ?bfmeSet@Gen00637390@@QAEXVAsciiString@@@Z		75B
void Gen00637390::bfmeSet( AsciiString value )
{
	StringBase<char> &text = m_bfmeText;

	text.set( value );
}

// ?bfmeSet@Gen00637FD0@@QAEXVAsciiString@@@Z		75B
void Gen00637FD0::bfmeSet( AsciiString value )
{
	StringBase<char> &text = m_bfmeText;

	text.set( value );
}

// ?bfmeSet@Gen0068AE60@@QAEXVAsciiString@@@Z		75B
void Gen0068AE60::bfmeSet( AsciiString value )
{
	StringBase<char> &text = m_bfmeText;

	text.set( value );
}

// ?bfmeSet@Gen0068DD60@@QAEXVUnicodeString@@@Z		75B
void Gen0068DD60::bfmeSet( UnicodeString value )
{
	StringBase<unsigned short> &text = m_bfmeText;

	text.set( value );
}

// ?bfmeSet@Gen0068DDC0@@QAEXVUnicodeString@@@Z		75B
void Gen0068DDC0::bfmeSet( UnicodeString value )
{
	StringBase<unsigned short> &text = m_bfmeText;

	text.set( value );
}
