// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringbaseascii/Common /Igame/Libraries/Source/WWVegas/WWLib
//
// Retail 0x0035C0C0 (579 B) -- the Script chunk reader the Open-BFME5 lift named
// ?ParseScript@Script@@SAPAV1@AAVDataChunkInput@@G@Z.
//
// That mangled name is CONTRADICTED by the body and is not used here:
//   * the frame keeps ECX (`mov esi,ecx` at +0x24) and stores through ES+0x04
//     .. ES+0x1A, so this is a __thiscall INSTANCE method, not a static;
//   * it ends `push esi / mov ecx,edi / call parse / ret 8` -- the return value
//     is file.parse(this) in AL and there is no `operator new`, so the return
//     type is bool, not Script *;
//   * the only 16-bit parameter is at [esp+0x2c] (`cmp word ptr [esp+0x2c],2`),
//     which is the `G` unsigned short the name already carried.
//
// The CLASS is proven, and the method name is not, so the method keeps the
// address token.  Class proof: the store pattern
//   +4, +8, +0xC  = three AsciiString::operator= (StringBase<char>::set,
//                 0x00887C90) fed by DataChunkInput::readAsciiString
//   +0x10         = DataChunkInput::readInt (0x0003A805), guarded by version>=2
//   +0x14 +0x15   = one readByte result stored twice
//   +0x16 +0x18 +0x19 +0x1A +0x17 = five more readByte results
// is the exact member layout the landed BFME ctor carries
// (ScriptCtor.cpp: m_scriptName, m_comment, m_conditionComment,
// m_delayEvaluationSeconds, m_isActive, m_isOneShot, m_easy, m_isSubroutine,
// m_normal, m_hard, m_bfmeFlag), and the three nested parsers registered are
// named "OrCondition" (0x010E8AD4), "ScriptAction" (0x010E7CD0) and
// "ScriptActionFalse" (0x010E8520) under parent "Script" (0x010E8470) --
// Script's own children, through the callbacks
//   0x00416568 -> 0x0035B700 ?ParseOrConditionDataChunk@OrCondition@@ (landed)
//   0x0042F70C -> 0x00358FE0 ?ParseActionDataChunk@ScriptAction@@ (landed)
//   0x00425DE2 -> 0x00359030 the false-action twin (landed)
// Retail takes the address of each callback through the incremental-link jump
// thunk it emitted for it, so the immediates are the thunk addresses, the same
// trick the landed Rva00350F50ParserRegistrationCtor.cpp uses for 0x0041579E.
//
// The three readAsciiString temporaries share one frame slot, and each is
// released by StringBase<char>::releaseBuffer (0x00887940) at the end of its
// own full expression, which is what the nine /EHsc unwind states in the retail
// FuncInfo (handler 0x01019828) describe.

#include "AsciiString.h"

class Xfer;
class UserParser;
class DataChunkInput;
struct DataChunkInfo;

typedef int Int;
typedef bool Bool;

typedef Bool (__cdecl *BfmeParserCallback)( DataChunkInput &, DataChunkInfo *, void * );

// Incremental-link thunks of the three nested parsers (game/gen_small/gthunks_*.cpp).
void j_00016568();
void j_0002f70c();
void j_00025de2();

class DataChunkInput
{
public:
	AsciiString readAsciiString();
	unsigned char bfmeReadByte();
	Int readInt();
	void registerParser( const AsciiString &name, const AsciiString &label,
		BfmeParserCallback callback, void *userData );
	Bool parse( void *userData );
};

// The retail layout, as the landed BFME ctor carries it (ScriptCtor.cpp).  Only
// the vtable slot and the members the body touches are spelled out; the
// pointer/flag members that follow keep the offsets that follow +0x1A out of
// this body, so only the leading run needs to be exact here.
class Script
{
public:
	virtual void xfer( Xfer *xfer );
	Bool Rva0035C0C0( DataChunkInput &file, unsigned short version );

private:
	AsciiString m_scriptName;					///< retail this+0x04
	AsciiString m_comment;						///< retail this+0x08
	AsciiString m_conditionComment;				///< retail this+0x0C
	Int m_delayEvaluationSeconds;				///< retail this+0x10
	bool m_isActive;							///< retail this+0x14
	bool m_isOneShot;							///< retail this+0x15
	bool m_easy;								///< retail this+0x16
	bool m_isSubroutine;						///< retail this+0x17
	bool m_normal;								///< retail this+0x18
	bool m_hard;								///< retail this+0x19
	bool m_bfmeFlag;							///< retail this+0x1A
};

// ?Rva0035C0C0@Script@@QAE_NAAVDataChunkInput@@G@Z
Bool Script::Rva0035C0C0( DataChunkInput &file, unsigned short version )
{
	m_scriptName = file.readAsciiString();
	m_comment = file.readAsciiString();
	m_conditionComment = file.readAsciiString();

	// One byte feeds both flags: the body stores the single test/setne result
	// to +0x14 and +0x15 before it reads the next byte.
	Bool onoff = ( file.bfmeReadByte() != 0 );
	m_isActive = onoff;
	m_isOneShot = onoff;
	m_easy = ( file.bfmeReadByte() != 0 );
	m_normal = ( file.bfmeReadByte() != 0 );
	m_hard = ( file.bfmeReadByte() != 0 );
	m_bfmeFlag = ( file.bfmeReadByte() != 0 );
	m_isSubroutine = ( file.bfmeReadByte() != 0 );

	if ( version >= 2 ) {
		m_delayEvaluationSeconds = file.readInt();
	}

	file.registerParser( AsciiString( "OrCondition" ), AsciiString( "Script" ),
		(BfmeParserCallback)j_00016568, 0 );
	file.registerParser( AsciiString( "ScriptAction" ), AsciiString( "Script" ),
		(BfmeParserCallback)j_0002f70c, 0 );
	file.registerParser( AsciiString( "ScriptActionFalse" ), AsciiString( "Script" ),
		(BfmeParserCallback)j_00025de2, 0 );

	return file.parse( this );
}
