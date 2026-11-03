// ?triggerAbilityEffect@SpecialDisguiseUpdate@@MAEXXZ
// Retail: 433 bytes at 0x00267D80, through RET at +0x1B0.
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

// FILE: SpecialDisguiseUpdateTriggerAbilityEffect.cpp ////////////////////////
//
// SpecialDisguiseUpdate::triggerAbilityEffect.
//
// BFME 1 evidence: the SpecialDisguiseUpdate constructor 0x00267820 installs
// vtable 0x010B7708 whose slot 15 reaches this body through ILT 0x0003DD43;
// ilt_oracle CONFIRMS ?triggerAbilityEffect@SpecialDisguiseUpdate@@MAEXXZ
// here (exact). The body's first call is 0x002A9850, which ilt_oracle
// CONFIRMS as SpecialAbilityUpdate::triggerAbilityEffect (called by its
// defined row name, as ToggleMountedSpecialAbilityUpdate's override does).
//
// Shape from the Open BFME 2 donor SpecialDisguiseUpdate.cpp (donor revision
// 59e3f8f825, ?triggerAbilityEffect@SpecialDisguiseUpdate@@UAEXXZ at BFME 2
// 0x004B0653, 431 B): base call, idle-AI and state-1 gates; an active
// disguise condition is cleared and the visual swap gets true; otherwise the
// contain module empties, the drawable fades (Drawable::setStealthLook(2,
// 0.2, 0.7, 2.0)), the condition is set, the visual swap gets whether the
// owner is the local player's, and the local player hears "DisguiseStarted".
// BFME 1 offsets come from this body: owner +0x08, state +0x24; object
// condition word +0x130 bit 0x800 (bit 267 of the +0x110 array, the bit
// Rva00267D00 clears), contain +0x1FC (slots 64/37), AI +0x204 (slot 96),
// id +0x74; local player at ThePlayerList +0x0C; TheAudio slot 17.
//
///////////////////////////////////////////////////////////////////////////////

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef unsigned int AudioHandle;

// An enum: AudioEventRTS::setObjectID's parameter type is part of its symbol.
enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

enum StealthLookType
{
	STEALTHLOOK_NONE = 0
};

#include "ascii_string.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS
{
public:
	AudioEventRTS( const AudioEventRTS &source );
	~AudioEventRTS();

	void setObjectID( ObjectID id );

private:
	unsigned char m_unmodelled[ 0x70 ];
};

class Drawable
{
public:
	void setStealthLook( StealthLookType look, Real first, Real second, Real third );
};

// Retail ILT thunks: Drawable's per-unit sound lookup (0x00416FE0, ledgered
// only as a dump) and the SpecialDisguiseUpdate visual swap 0x00267B10 (one
// byte argument, ret 4; Rva00267D00.cpp calls it the same way). Both are
// called through member-pointer unions so the target is named, not aliased.
extern void j_0000fd44();
extern void j_00020847();

class Rva00267B10
{
};

#define BFME_SLOT( n ) virtual void unusedSlot##n();

class DisguiseAI
{
public:
	BFME_SLOT( 0 ) BFME_SLOT( 1 ) BFME_SLOT( 2 ) BFME_SLOT( 3 ) BFME_SLOT( 4 ) BFME_SLOT( 5 )
	BFME_SLOT( 6 ) BFME_SLOT( 7 ) BFME_SLOT( 8 ) BFME_SLOT( 9 ) BFME_SLOT( 10 ) BFME_SLOT( 11 )
	BFME_SLOT( 12 ) BFME_SLOT( 13 ) BFME_SLOT( 14 ) BFME_SLOT( 15 ) BFME_SLOT( 16 ) BFME_SLOT( 17 )
	BFME_SLOT( 18 ) BFME_SLOT( 19 ) BFME_SLOT( 20 ) BFME_SLOT( 21 ) BFME_SLOT( 22 ) BFME_SLOT( 23 )
	BFME_SLOT( 24 ) BFME_SLOT( 25 ) BFME_SLOT( 26 ) BFME_SLOT( 27 ) BFME_SLOT( 28 ) BFME_SLOT( 29 )
	BFME_SLOT( 30 ) BFME_SLOT( 31 ) BFME_SLOT( 32 ) BFME_SLOT( 33 ) BFME_SLOT( 34 ) BFME_SLOT( 35 )
	BFME_SLOT( 36 ) BFME_SLOT( 37 ) BFME_SLOT( 38 ) BFME_SLOT( 39 ) BFME_SLOT( 40 ) BFME_SLOT( 41 )
	BFME_SLOT( 42 ) BFME_SLOT( 43 ) BFME_SLOT( 44 ) BFME_SLOT( 45 ) BFME_SLOT( 46 ) BFME_SLOT( 47 )
	BFME_SLOT( 48 ) BFME_SLOT( 49 ) BFME_SLOT( 50 ) BFME_SLOT( 51 ) BFME_SLOT( 52 ) BFME_SLOT( 53 )
	BFME_SLOT( 54 ) BFME_SLOT( 55 ) BFME_SLOT( 56 ) BFME_SLOT( 57 ) BFME_SLOT( 58 ) BFME_SLOT( 59 )
	BFME_SLOT( 60 ) BFME_SLOT( 61 ) BFME_SLOT( 62 ) BFME_SLOT( 63 ) BFME_SLOT( 64 ) BFME_SLOT( 65 )
	BFME_SLOT( 66 ) BFME_SLOT( 67 ) BFME_SLOT( 68 ) BFME_SLOT( 69 ) BFME_SLOT( 70 ) BFME_SLOT( 71 )
	BFME_SLOT( 72 ) BFME_SLOT( 73 ) BFME_SLOT( 74 ) BFME_SLOT( 75 ) BFME_SLOT( 76 ) BFME_SLOT( 77 )
	BFME_SLOT( 78 ) BFME_SLOT( 79 ) BFME_SLOT( 80 ) BFME_SLOT( 81 ) BFME_SLOT( 82 ) BFME_SLOT( 83 )
	BFME_SLOT( 84 ) BFME_SLOT( 85 ) BFME_SLOT( 86 ) BFME_SLOT( 87 ) BFME_SLOT( 88 ) BFME_SLOT( 89 )
	BFME_SLOT( 90 ) BFME_SLOT( 91 ) BFME_SLOT( 92 ) BFME_SLOT( 93 ) BFME_SLOT( 94 ) BFME_SLOT( 95 )
	virtual Bool isIdle() const;																// slot 96
};

class DisguiseContain
{
public:
	BFME_SLOT( 0 ) BFME_SLOT( 1 ) BFME_SLOT( 2 ) BFME_SLOT( 3 ) BFME_SLOT( 4 ) BFME_SLOT( 5 )
	BFME_SLOT( 6 ) BFME_SLOT( 7 ) BFME_SLOT( 8 ) BFME_SLOT( 9 ) BFME_SLOT( 10 ) BFME_SLOT( 11 )
	BFME_SLOT( 12 ) BFME_SLOT( 13 ) BFME_SLOT( 14 ) BFME_SLOT( 15 ) BFME_SLOT( 16 ) BFME_SLOT( 17 )
	BFME_SLOT( 18 ) BFME_SLOT( 19 ) BFME_SLOT( 20 ) BFME_SLOT( 21 ) BFME_SLOT( 22 ) BFME_SLOT( 23 )
	BFME_SLOT( 24 ) BFME_SLOT( 25 ) BFME_SLOT( 26 ) BFME_SLOT( 27 ) BFME_SLOT( 28 ) BFME_SLOT( 29 )
	BFME_SLOT( 30 ) BFME_SLOT( 31 ) BFME_SLOT( 32 ) BFME_SLOT( 33 ) BFME_SLOT( 34 ) BFME_SLOT( 35 )
	BFME_SLOT( 36 )
	virtual void slot37( Int flags );															// slot 37
	BFME_SLOT( 38 ) BFME_SLOT( 39 ) BFME_SLOT( 40 ) BFME_SLOT( 41 ) BFME_SLOT( 42 ) BFME_SLOT( 43 )
	BFME_SLOT( 44 ) BFME_SLOT( 45 ) BFME_SLOT( 46 ) BFME_SLOT( 47 ) BFME_SLOT( 48 ) BFME_SLOT( 49 )
	BFME_SLOT( 50 ) BFME_SLOT( 51 ) BFME_SLOT( 52 ) BFME_SLOT( 53 ) BFME_SLOT( 54 ) BFME_SLOT( 55 )
	BFME_SLOT( 56 ) BFME_SLOT( 57 ) BFME_SLOT( 58 ) BFME_SLOT( 59 ) BFME_SLOT( 60 ) BFME_SLOT( 61 )
	BFME_SLOT( 62 ) BFME_SLOT( 63 )
	virtual UnsignedInt slot64( Int flags );													// slot 64
};

class Player;

class Object
{
public:
	BFME_SLOT( 0 ) BFME_SLOT( 1 ) BFME_SLOT( 2 ) BFME_SLOT( 3 ) BFME_SLOT( 4 )
	BFME_SLOT( 5 ) BFME_SLOT( 6 ) BFME_SLOT( 7 ) BFME_SLOT( 8 ) BFME_SLOT( 9 )
	virtual Drawable *getDrawable() const;														// slot 10

	Player *getControllingPlayer() const;
	void notifyModelConditionChanged();

	ObjectID getID() const { return m_id; }
	DisguiseAI *getAI() const { return m_ai; }
	DisguiseContain *getContain() const { return m_contain; }

	Bool clearDisguised()
	{
		if( !( m_flags130 & 0x800 ) )
			return false;
		m_flags130 &= ~0x800;
		notifyModelConditionChanged();
		return true;
	}
	void setDisguised()
	{
		if( !( m_flags130 & 0x800 ) )
		{
			m_flags130 |= 0x800;
			notifyModelConditionChanged();
		}
	}

private:
	unsigned char m_unmodelled_004[ 0x74 - 0x004 ];
	ObjectID m_id;
	unsigned char m_unmodelled_078[ 0x130 - 0x078 ];
	UnsignedInt m_flags130;
	unsigned char m_unmodelled_134[ 0x1FC - 0x134 ];
	DisguiseContain *m_contain;
	unsigned char m_unmodelled_200[ 0x204 - 0x200 ];
	DisguiseAI *m_ai;
};

class PlayerList
{
public:
	Player *getLocalPlayer() const { return m_local; }

private:
	unsigned char m_unmodelled_00[ 0x0C ];
	Player *m_local;
};

extern PlayerList *ThePlayerList;

class AudioManager
{
public:
	BFME_SLOT( 0 ) BFME_SLOT( 1 ) BFME_SLOT( 2 ) BFME_SLOT( 3 ) BFME_SLOT( 4 ) BFME_SLOT( 5 )
	BFME_SLOT( 6 ) BFME_SLOT( 7 ) BFME_SLOT( 8 ) BFME_SLOT( 9 ) BFME_SLOT( 10 ) BFME_SLOT( 11 )
	BFME_SLOT( 12 ) BFME_SLOT( 13 ) BFME_SLOT( 14 ) BFME_SLOT( 15 ) BFME_SLOT( 16 )
	virtual AudioHandle addAudioEvent( const AudioEventRTS *event );							// slot 17
};

extern AudioManager *TheAudio;

// 0x002A9850 is defined only under ??1WeaponSetSpecialAbilityUpdate@@UAE@XZ
// (2403-byte row); call it by that defined name. The qualified explicit
// destructor call keeps static thiscall dispatch (receiver in ECX).
class WeaponSetSpecialAbilityUpdate { public: virtual ~WeaponSetSpecialAbilityUpdate(); };

class SpecialDisguiseUpdate
{
protected:
	virtual void triggerAbilityEffect();

private:
	Object *getObject() const { return m_object; }
	void doVisualDisguise( Bool useOwnTemplate )
	{
		union { void ( *raw )(); void ( Rva00267B10::*member )( Bool ); } swap = { j_00020847 };
		( ( (Rva00267B10 *)this )->*swap.member )( useOwnTemplate );
	}

	const void *m_moduleData;
	Object *m_object;
	unsigned char m_unmodelled_0C[ 0x24 - 0x0C ];
	Int m_state;
};

void SpecialDisguiseUpdate::triggerAbilityEffect()
{
	((WeaponSetSpecialAbilityUpdate *)this)->WeaponSetSpecialAbilityUpdate::~WeaponSetSpecialAbilityUpdate();

	Object *obj = getObject();
	if( !obj->getAI()->isIdle() || m_state != 1 )
		return;

	if( obj->clearDisguised() )
	{
		doVisualDisguise( true );
		return;
	}

	DisguiseContain *contain = obj->getContain();
	if( contain && contain->slot64( 0 ) > 0 )
		obj->getContain()->slot37( 0 );

	Drawable *draw = obj->getDrawable();
	if( draw )
		draw->setStealthLook( (StealthLookType)2, 0.2f, 0.7f, 2.0f );

	obj->setDisguised();

	Player *localPlayer = ThePlayerList->getLocalPlayer();
	Bool isLocal = true;
	if( obj->getControllingPlayer() != localPlayer )
		isLocal = false;
	doVisualDisguise( isLocal );

	if( isLocal && draw )
	{
		typedef const AudioEventRTS *( Drawable::*SoundFn )( const AsciiString & ) const;
		union { void ( *raw )(); SoundFn call; } lookup = { j_0000fd44 };
		AudioEventRTS sound( *( draw->*lookup.call )( AsciiString( "DisguiseStarted" ) ) );
		sound.setObjectID( obj->getID() );
		TheAudio->addAudioEvent( &sound );
	}
}
