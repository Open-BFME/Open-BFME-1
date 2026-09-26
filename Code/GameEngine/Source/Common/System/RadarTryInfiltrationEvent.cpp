// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/radar /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4

#include "PreRTS.h"

#include "Common/AudioEventRTS.h"
#include "Common/GameAudio.h"
#include "Common/MiscAudio.h"
#include "Common/Player.h"
#include "Common/Radar.h"
#include "GameLogic/Object.h"

class Rva00589320Player;

// The out-of-line PlayerList local-player accessor (ILT 0x0000762B -> 0x000DF860)
// on the player-list global at 0x012ED748, spelled as Radar.cpp spells it.
struct Rva002EE330PlayerList
{
	Rva00589320Player *getLocalPlayer();
};
extern Rva002EE330PlayerList *Rva002EE330ThePlayers;

// Retail builds the by-value label in the argument slot with the StringBase<char>
// const char* constructor at 0x00888BC0. The string class forwards its ctors and
// dtor INLINE to that base, which is what puts the EH saved-esp store before
// `mov ecx,esp` (docs/shape_levers.md row 2, reference/shims/stringinline/StringInline.h;
// that header's AsciiString collides with the Zero Hour one this TU includes).
template <typename T> class StringBase
{
	friend class BFMERetailAsciiString;

private:
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	void *m_data;
};

class BFMERetailAsciiString : private StringBase<char>
{
public:
	BFMERetailAsciiString( const char *text ) : StringBase<char>( text ) {}
	BFMERetailAsciiString( const BFMERetailAsciiString &other ) : StringBase<char>( other ) {}
	~BFMERetailAsciiString() {}
};

// InGameUI::message( AsciiString, ... ) is vtable +0x30 (InGameUIDisplayCantBuildMessage.cpp).
#define BFME_INFILTRATION_UI_SLOT(n) virtual void bfmeInfiltrationUiSlot##n() = 0;
class BfmeInfiltrationInGameUIView
{
public:
	BFME_INFILTRATION_UI_SLOT(0) BFME_INFILTRATION_UI_SLOT(1) BFME_INFILTRATION_UI_SLOT(2) BFME_INFILTRATION_UI_SLOT(3)
	BFME_INFILTRATION_UI_SLOT(4) BFME_INFILTRATION_UI_SLOT(5) BFME_INFILTRATION_UI_SLOT(6) BFME_INFILTRATION_UI_SLOT(7)
	BFME_INFILTRATION_UI_SLOT(8) BFME_INFILTRATION_UI_SLOT(9) BFME_INFILTRATION_UI_SLOT(10) BFME_INFILTRATION_UI_SLOT(11)
	virtual void message( BFMERetailAsciiString stringManagerLabel, ... ) = 0;	///< vtable +0x30
};
#undef BFME_INFILTRATION_UI_SLOT

// AudioManager: addAudioEvent is vtable +0x44 and getMiscAudio a virtual at
// +0x124 (Player.cpp BfmeAudioManagerView).
#define BFME_INFILTRATION_AUDIO_SLOT(n) virtual void bfmeInfiltrationAudioSlot##n() = 0;
class BfmeInfiltrationAudioView
{
public:
	BFME_INFILTRATION_AUDIO_SLOT(0) BFME_INFILTRATION_AUDIO_SLOT(1) BFME_INFILTRATION_AUDIO_SLOT(2) BFME_INFILTRATION_AUDIO_SLOT(3)
	BFME_INFILTRATION_AUDIO_SLOT(4) BFME_INFILTRATION_AUDIO_SLOT(5) BFME_INFILTRATION_AUDIO_SLOT(6) BFME_INFILTRATION_AUDIO_SLOT(7)
	BFME_INFILTRATION_AUDIO_SLOT(8) BFME_INFILTRATION_AUDIO_SLOT(9) BFME_INFILTRATION_AUDIO_SLOT(10) BFME_INFILTRATION_AUDIO_SLOT(11)
	BFME_INFILTRATION_AUDIO_SLOT(12) BFME_INFILTRATION_AUDIO_SLOT(13) BFME_INFILTRATION_AUDIO_SLOT(14) BFME_INFILTRATION_AUDIO_SLOT(15)
	BFME_INFILTRATION_AUDIO_SLOT(16)
	virtual void addAudioEvent( const AudioEventRTS *e ) = 0;		///< vtable +0x44
	BFME_INFILTRATION_AUDIO_SLOT(18) BFME_INFILTRATION_AUDIO_SLOT(19)
	BFME_INFILTRATION_AUDIO_SLOT(20) BFME_INFILTRATION_AUDIO_SLOT(21) BFME_INFILTRATION_AUDIO_SLOT(22) BFME_INFILTRATION_AUDIO_SLOT(23)
	BFME_INFILTRATION_AUDIO_SLOT(24) BFME_INFILTRATION_AUDIO_SLOT(25) BFME_INFILTRATION_AUDIO_SLOT(26) BFME_INFILTRATION_AUDIO_SLOT(27)
	BFME_INFILTRATION_AUDIO_SLOT(28) BFME_INFILTRATION_AUDIO_SLOT(29) BFME_INFILTRATION_AUDIO_SLOT(30) BFME_INFILTRATION_AUDIO_SLOT(31)
	BFME_INFILTRATION_AUDIO_SLOT(32) BFME_INFILTRATION_AUDIO_SLOT(33) BFME_INFILTRATION_AUDIO_SLOT(34) BFME_INFILTRATION_AUDIO_SLOT(35)
	BFME_INFILTRATION_AUDIO_SLOT(36) BFME_INFILTRATION_AUDIO_SLOT(37) BFME_INFILTRATION_AUDIO_SLOT(38) BFME_INFILTRATION_AUDIO_SLOT(39)
	BFME_INFILTRATION_AUDIO_SLOT(40) BFME_INFILTRATION_AUDIO_SLOT(41) BFME_INFILTRATION_AUDIO_SLOT(42) BFME_INFILTRATION_AUDIO_SLOT(43)
	BFME_INFILTRATION_AUDIO_SLOT(44) BFME_INFILTRATION_AUDIO_SLOT(45) BFME_INFILTRATION_AUDIO_SLOT(46) BFME_INFILTRATION_AUDIO_SLOT(47)
	BFME_INFILTRATION_AUDIO_SLOT(48) BFME_INFILTRATION_AUDIO_SLOT(49) BFME_INFILTRATION_AUDIO_SLOT(50) BFME_INFILTRATION_AUDIO_SLOT(51)
	BFME_INFILTRATION_AUDIO_SLOT(52) BFME_INFILTRATION_AUDIO_SLOT(53) BFME_INFILTRATION_AUDIO_SLOT(54) BFME_INFILTRATION_AUDIO_SLOT(55)
	BFME_INFILTRATION_AUDIO_SLOT(56) BFME_INFILTRATION_AUDIO_SLOT(57) BFME_INFILTRATION_AUDIO_SLOT(58) BFME_INFILTRATION_AUDIO_SLOT(59)
	BFME_INFILTRATION_AUDIO_SLOT(60) BFME_INFILTRATION_AUDIO_SLOT(61) BFME_INFILTRATION_AUDIO_SLOT(62) BFME_INFILTRATION_AUDIO_SLOT(63)
	BFME_INFILTRATION_AUDIO_SLOT(64) BFME_INFILTRATION_AUDIO_SLOT(65) BFME_INFILTRATION_AUDIO_SLOT(66) BFME_INFILTRATION_AUDIO_SLOT(67)
	BFME_INFILTRATION_AUDIO_SLOT(68) BFME_INFILTRATION_AUDIO_SLOT(69) BFME_INFILTRATION_AUDIO_SLOT(70) BFME_INFILTRATION_AUDIO_SLOT(71)
	BFME_INFILTRATION_AUDIO_SLOT(72)
	virtual const MiscAudio *getMiscAudio( void ) = 0;				///< vtable +0x124
};
#undef BFME_INFILTRATION_AUDIO_SLOT

extern class InGameUI *TheInGameUI;

// BFME's MiscAudio carries m_radarInfiltrationSound at +0xE0 (field_names witness).
#define BFME_RADAR_INFILTRATION_SOUND(m) (*(const AudioEventRTS *)((const UnsignedByte *)(m) + 0xE0))

// Object's cached position sits at +0x38 in BFME (retail add edi,0x38).
#define BFME_OBJECT_POSITION(o) ((const Coord3D *)((const UnsignedByte *)(o) + 0x38))

// Retail pushes radar event type 4 for the infiltration event.
#define BFME_RADAR_EVENT_INFILTRATION ((RadarEventType)4)

// Radar::tryInfiltrationEvent (0x001083D0, 258 bytes, ret 4). Object::defect
// (0x001D22C0) calls it at 0x001D237B through ILT 0x0000D805 with TheRadar in ecx
// and `this` pushed, as the Zero Hour twin does; the "RADAR:Infiltration" label
// (0x010888FC) and the static MiscAudio sound match the Zero Hour Radar.cpp body.
// BFME drops the null object guard and adds a null local-player guard.
void Radar::tryInfiltrationEvent( const Object *obj )
{
	if( obj->getControllingPlayer() != (Player *)Rva002EE330ThePlayers->getLocalPlayer() )
		return;

	createEvent( BFME_OBJECT_POSITION( obj ), BFME_RADAR_EVENT_INFILTRATION );

	Player *player = (Player *)Rva002EE330ThePlayers->getLocalPlayer();
	if( player == NULL )
		return;

	((BfmeInfiltrationInGameUIView *)TheInGameUI)->message( "RADAR:Infiltration" );

	static AudioEventRTS infiltrationWarningSound =
		BFME_RADAR_INFILTRATION_SOUND( ((BfmeInfiltrationAudioView *)TheAudio)->getMiscAudio() );
	infiltrationWarningSound.setPlayerIndex( player->getPlayerIndex() );
	((BfmeInfiltrationAudioView *)TheAudio)->addAudioEvent( &infiltrationWarningSound );
}
