// cl: /DNDEBUG /MD /EHsc
// readable body of ?update@Eva@@: Code/GameEngine/Source/GameClient/Eva.cpp
// Open-BFME5: Eva::update, spelled against the retail BFME layout.
//
// BFME's Eva is not Zero Hour's.  Retail runs one countdown pair per live check
// record in milliseconds rather than tracking absolute frame numbers, and it
// only reaches for the next line when EVA is enabled, the audio manager exists,
// nothing is already speaking, and the logic has run more than two frames.  The
// Zero Hour GameClient/Eva.h describes none of that, so the class is spelled
// against the retail layout in its own translation unit (AGENTS.md,
// "Placement and integrity").
//
// Identity: slot 5 of the primary Eva vtable at 0x010F1FA8, whose slot 1 is the
// already matched ?init@Eva@@UAEXXZ region and slot 4 is the matched
// reset body ?reset@Eva@@UAEXXZ.  The +0x4c check vector, +0x58 speech handle and
// +0x5c enable flag are the same members ?setEvaEnabled@Eva@@QAEX_N@Z and
// Eva::reset touch.  The [vtable+0xB0] dispatch on TheAudio is the identical
// call the matched ?isCurrentlyPlaying@AudioEventRTS@@QBE_NXZ makes, which is
// what names it.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef UnsignedInt AudioHandle;

// One logic frame at thirty frames a second, which is the step retail subtracts
// from both countdowns.
#define MSEC_PER_LOGICFRAME_REAL ( 1000.0f / 30.0f )

// __single_inheritance so the pointer-to-member below is the compact
// "just an address" representation retail compiled with; without it MSVC falls
// back to the general form and emits the whole vtordisp dance.
class __single_inheritance AudioManager;
extern AudioManager *TheAudio;

// Only the frame counter at +0x3c is load-bearing here; retail reads it inline
// rather than calling an accessor.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	UnsignedInt getFrame( void ) const { return m_frame; }

private:
	char        m_head[ 0x3c ];
	UnsignedInt m_frame;			// +0x3c
};

extern GameLogic *TheGameLogic;

// Retail per-message check record, 24 bytes: two millisecond countdowns and a
// played flag at +0x14.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Eva.h
struct EvaCheck
{
	Real m_timeUntilExpire;
	Real m_timeUntilNextCheck;
	char m_rest[ 0x10 ];
};

// Retail parsed check-info record; only its 28-byte stride matters here.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Eva.h
struct EvaCheckInfo
{
	char m_raw[ 28 ];
};

class EvaCheckInfoVec
{
public:
	Int size( void ) const { return m_end - m_begin; }

	EvaCheckInfo *m_begin;
	EvaCheckInfo *m_end;
	EvaCheckInfo *m_capacity;
};

class EvaCheckVec
{
public:
	Int size( void ) const { return m_end - m_begin; }

	EvaCheck *m_begin;
	EvaCheck *m_end;
	EvaCheck *m_capacity;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Eva.h
class Eva
{
public:
	// Slot 5 of the primary vtable at 0x010F1FA8; virtual so the body carries
	// retail's ?update@Eva@@UAEXXZ decoration and the +0x00 vtable pointer lands
	// where retail's does.
	virtual void update( void );

private:
	// 0x004237E0 through the ILT entry at 0x0000F32B: walks the check-info table
	// and starts the highest-priority pending line.  Retail never named it.
	void _bfme_serviceHighestPriorityCheck( void );

	char            m_head[ 0x08 ];		// +0x04 pad and the +0x08 vtable pointer
	EvaCheckInfoVec m_checkInfos;		// +0x0c
	EvaCheckInfoVec m_defaultCheckInfos;	// +0x18
	char            m_sideSounds[ 0x28 ];	// +0x24 the two side-sound containers
	EvaCheckVec     m_checks;		// +0x4c
	AudioHandle     m_speechHandle;		// +0x58
	Bool            m_enabled;		// +0x5c
};

void Eva::update( void )
{
	// The live records and the parsed table are built together; a mismatch means
	// nothing has been parsed yet.
	if( m_checks.size() != m_checkInfos.size() )
		return;

	if( m_enabled && TheAudio != 0 )
	{
		typedef Bool (AudioManager::*IsCurrentlyPlayingProc)( AudioHandle );
		if( !(TheAudio->**(IsCurrentlyPlayingProc *)(*(char **)TheAudio + 0xB0))( m_speechHandle )
				&& TheGameLogic->getFrame() > 2 )
		{
			_bfme_serviceHighestPriorityCheck();
		}
	}

	// Both countdowns run whether or not anything was started this frame.
	EvaCheck *check = m_checks.m_begin;
	EvaCheck *last = m_checks.m_end;
	while( check != last )
	{
		check->m_timeUntilExpire -= MSEC_PER_LOGICFRAME_REAL;
		check->m_timeUntilNextCheck -= MSEC_PER_LOGICFRAME_REAL;
		++check;
	}
}
