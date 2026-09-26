// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

// Four more of P7ByValueStringSetters.cpp's one-line by-value setters, split
// out only because their string sits at +4 or +8 -- the four smallest heads in
// the family, below the 0x10 where that file starts.
//
// Everything else is that file's shape and its reasoning applies unchanged:
// MSVC makes the CALLEE destroy a by-value class argument, so each body ends
// with the destructor on the incoming slot at `lea ecx,[esp+0x10]`, and the
// exception frame exists only to run it if the set throws.
//
// THE TWO CALLEES NAME THE TYPE.  0x00887C90 and 0x00887940 are
// StringBase<char>'s set and destructor (the narrow function-local statics at
// 0x01336E10/0x01336E2C); StringBase<unsigned short>'s are 0x00888530 and
// 0x008881D0 on 0x01336E30/0x01336E4C.  All four of these are narrow, which is
// what rules out the LANPlayer setters they were previously landed as --
// LANPlayer's m_login and m_host are UnicodeStrings.
//
// THE MEMBER MUST BE BOUND AS A REFERENCE FIRST, or the compiler pushes the
// argument before forming `this + K` and retail forms it after.
//
// IDENTITY IS NOT RECOVERED for the owners; each is named for its own address
// and `char m_bfmeHead[K]` carries the offset and nothing else.

#include "string_base.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : public StringBase<char>
{
public:
	AsciiString( const AsciiString &other );
	~AsciiString() {}
};

class Gen000A7690
{
public:
	void bfmeSet( AsciiString value );

private:
	char m_bfmeHead[ 0x4 ];
	AsciiString m_bfmeText;			// +0x04
};

class Gen00193C60
{
public:
	void bfmeSet( AsciiString value );

private:
	char m_bfmeHead[ 0x4 ];
	AsciiString m_bfmeText;			// +0x04
};

class Gen00450270
{
public:
	void bfmeSet( AsciiString value );

private:
	char m_bfmeHead[ 0x8 ];
	AsciiString m_bfmeText;			// +0x08
};

class Gen00601710
{
public:
	void bfmeSet( AsciiString value );

private:
	char m_bfmeHead[ 0x4 ];
	AsciiString m_bfmeText;			// +0x04
};

// ?bfmeSet@Gen000A7690@@QAEXVAsciiString@@@Z		75B
void Gen000A7690::bfmeSet( AsciiString value )
{
	StringBase<char> &text = m_bfmeText;

	text.set( value );
}

// ?bfmeSet@Gen00193C60@@QAEXVAsciiString@@@Z		75B
void Gen00193C60::bfmeSet( AsciiString value )
{
	StringBase<char> &text = m_bfmeText;

	text.set( value );
}

// ?bfmeSet@Gen00450270@@QAEXVAsciiString@@@Z		75B
void Gen00450270::bfmeSet( AsciiString value )
{
	StringBase<char> &text = m_bfmeText;

	text.set( value );
}

// ?bfmeSet@Gen00601710@@QAEXVAsciiString@@@Z		75B
void Gen00601710::bfmeSet( AsciiString value )
{
	StringBase<char> &text = m_bfmeText;

	text.set( value );
}
