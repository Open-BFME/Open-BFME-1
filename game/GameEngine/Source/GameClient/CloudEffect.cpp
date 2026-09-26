// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/ini /Iinputs/reference/shims/iniexception /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

// FILE: CloudEffect.cpp //////////////////////////////////////////////////////
//
// The CloudEffect block, BFME-only, next door to CloudBreakEffect and the same
// shape: copy saved into active, parse over active, write back unless this is an
// override load, then poke the cloud system through vtable slot 9.
//
// CloudBreakEffect.cpp records this one as unclaimable because its settings
// struct copies through a compiler-generated operator= that nothing in the image
// names. That is true, and it is also the way in: the generated body at
// 0x0040B430 is 295 bytes of member copies and it spells the whole layout out.
// Reconstructing the struct from it makes MSVC generate the same operator=, and
// the pin then names our own symbol rather than a retail one.
//
// Layout read straight off 0x0040B430: five AsciiStrings (0x00, 0x04, 0x08,
// 0x14, 0x88), four twelve-byte PODs copied by lea plus three dword moves
// (0x20, 0x44, 0x54, 0x64), three bytes at 0x3C-0x3E, and plain dwords for the
// rest. Only the shapes are recoverable, not the meanings, so the members are
// named for their offsets.
//
///////////////////////////////////////////////////////////////////////////////
#include "PreRTS.h"
#include "Common/INI.h"

static INILoadType retailLoadType( const INI *ini )
{
	struct RetailINI { char m_pad[ 0x08 ]; INILoadType m_loadType; };
	return reinterpret_cast<const RetailINI *>( ini )->m_loadType;
}

static const INILoadType INI_LOAD_BFME_TYPE_4 = (INILoadType)4;

// Twelve bytes copied as three dwords through a lea - a nested POD, not three
// loose members.
struct CloudEffectTriple
{
	Real m_x;
	Real m_y;
	Real m_z;
};

struct CloudEffect
{
	AsciiString m_string00;
	AsciiString m_string04;
	AsciiString m_string08;
	Int m_int0C;
	Int m_int10;
	AsciiString m_string14;
	Int m_int18;
	Int m_int1C;
	CloudEffectTriple m_triple20;
	Int m_int2C;
	Int m_int30;
	Int m_int34;
	Int m_int38;
	Bool m_bool3C;
	Bool m_bool3D;
	Bool m_bool3E;
	Int m_int40;
	CloudEffectTriple m_triple44;
	Int m_int50;
	CloudEffectTriple m_triple54;
	Int m_int60;
	CloudEffectTriple m_triple64;
	Int m_int70;
	Int m_int74;
	Int m_int78;
	Int m_int7C;
	Int m_int80;
	Int m_int84;
	AsciiString m_string88;

	static const FieldParse m_fieldParseTable[];
};

class CloudEffectSystem
{
public:
	virtual void _bfme_pad_0() = 0;
	virtual void _bfme_pad_1() = 0;
	virtual void _bfme_pad_2() = 0;
	virtual void _bfme_pad_3() = 0;
	virtual void _bfme_pad_4() = 0;
	virtual void _bfme_pad_5() = 0;
	virtual void _bfme_pad_6() = 0;
	virtual void _bfme_pad_7() = 0;
	virtual void _bfme_pad_8() = 0;
	virtual void settingsChanged() = 0;		// slot 9, +0x24
};

extern CloudEffect TheCloudEffectSaved;			// 0x012F1108
extern CloudEffect TheCloudEffectActive;		// 0x012F1198
// A different pointer from the one CloudBreakEffect.cpp reaches at 0x012F10F0:
// this block pokes 0x012F1104. Spelled apart rather than sharing that name,
// which would claim one global at two addresses.
extern CloudEffectSystem *TheCloudEffectSystem;	// 0x012F1104

// ?parseCloudEffect@@YAXPAVINI@@@Z
void parseCloudEffect( INI *ini )
{
	TheCloudEffectActive = TheCloudEffectSaved;
	ini->initFromINI( &TheCloudEffectActive, CloudEffect::m_fieldParseTable );

	const INILoadType loadType = retailLoadType( ini );
	if( loadType != INI_LOAD_CREATE_OVERRIDES && loadType != INI_LOAD_BFME_TYPE_4 )
		TheCloudEffectSaved = TheCloudEffectActive;

	if( TheCloudEffectSystem )
		TheCloudEffectSystem->settingsChanged();
}
