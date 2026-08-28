// cl: /DNDEBUG /MD /EHsc
// readable body of ??0W3DTankDrawModuleData@@: Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DTankDraw.cpp
// Open-BFME5: W3DTankDrawModuleData::W3DTankDrawModuleData at retail 0x0077EA70.
//
// Identity is settled by the "TrackDebrisDirtLeft"/"TrackDebrisDirtRight"
// literals at 0x011259C4/0x01125950 and by the member constants, which are
// Zero Hour's verbatim: 0.0f, 0.6f, 0.3f at +0x164/+0x168/+0x16C.
//
// TU-scoped ABI slice only: the base is an address-derived stand-in sized so
// the two AsciiStrings land at retail's +0x15C/+0x160, and its constructor is
// declared without a body so it stays the out-of-line call retail makes
// through the incremental-link thunk at 0x0000289C.
//
// THE RESIDUE THAT CLOSED THIS ROW EARLIER WAS A TWO-INSTRUCTION SWAP, AND IT
// IS A SUB-OBJECT-ADDRESS TELL, NOT SCHEDULING. Retail sets up the FIRST
// string with `lea ecx,[esi+0x15C]` BEFORE pushing the literal, but the SECOND
// with the push first. A plain `AsciiString m_left` member emits push-then-lea
// for both, because for a direct member-init entry MSVC evaluates the argument
// before materialising `this`. Wrapping the first string in an aggregate whose
// own inline constructor carries the member-init entry reverses exactly that
// one pair: the sub-object address is materialised before the inlined body
// runs, so `lea` precedes `push` for the first string and nothing else moves.
// An intermediate BASE class does the same reordering but is wrong here -- it
// is polymorphic, so it emits a second vftable store and widens the EH-state
// transition from a byte to a dword.

typedef float Real;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	void *m_data;
	AsciiString( const char *s );
	~AsciiString( void );
};

class W3DTankDrawModuleDataBase
{
public:
	virtual ~W3DTankDrawModuleDataBase();
	char m_baseFields[0x158];
	W3DTankDrawModuleDataBase();
};

struct W3DTankDrawTreadDebrisLeft
{
	AsciiString m_name;
	W3DTankDrawTreadDebrisLeft() : m_name( "TrackDebrisDirtLeft" ) {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/Module/W3DTankDraw.h
class W3DTankDrawModuleData : public W3DTankDrawModuleDataBase
{
public:
	W3DTankDrawTreadDebrisLeft m_treadDebrisNameLeft;
	AsciiString m_treadDebrisNameRight;
	Real m_treadAnimationRate;
	Real m_treadPivotSpeedFraction;
	Real m_treadDriveSpeedFraction;

	W3DTankDrawModuleData();
};

W3DTankDrawModuleData::W3DTankDrawModuleData() :
	m_treadDebrisNameRight( "TrackDebrisDirtRight" ),
	m_treadAnimationRate( 0.0f ),
	m_treadPivotSpeedFraction( 0.6f ),
	m_treadDriveSpeedFraction( 0.3f )
{
}
