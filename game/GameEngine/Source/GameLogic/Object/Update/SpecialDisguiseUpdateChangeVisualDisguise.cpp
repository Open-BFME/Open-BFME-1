// ?changeVisualDisguise@SpecialDisguiseUpdate@@QAEX_N@Z
// Retail: 390 bytes at 0x00267B10, through RET 4 at +0x183.
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Include /Igame/Libraries/Source/WWVegas/WWLib

// FILE: SpecialDisguiseUpdateChangeVisualDisguise.cpp ////////////////////////
//
// SpecialDisguiseUpdate::changeVisualDisguise.
//
// BFME 1 evidence: ilt_oracle CONFIRMS the decorated name at this body
// (exact; the private/protected and argument-less spellings, the
// StealthUpdate owner and the address-derived spellings are contradicted).
// Callers reach it through ILT 0x00020847 with ECX = the module and one byte
// argument: SpecialDisguiseUpdate::triggerAbilityEffect (0x00267D80, twice),
// Rva00267D00 (0x00267D00) and Player::becomingLocalPlayer.
//
// Shape from the Open BFME 2 donor SpecialDisguiseUpdate.cpp (donor revision
// 59e3f8f825, ?rva004B04B2@SpecialDisguiseUpdate@@QAEX_N@Z at BFME 2
// 0x004B04B2, 323 B), itself shaped by Zero Hour's
// StealthUpdate::changeVisualDisguise: remember whether the drawable was
// selected; a disguised owner whose module data forces mounting is mounted
// (condition, AI slot, weapon-set and armor-set flags); when the disguise
// template exists, copy the model-condition flags, destroy the drawable,
// create the owner's own (true) or the disguise template's drawable, bind
// it, copy position, orientation and the module's opacity, re-apply the
// conditions, restore the drawable's +0x3B8 value and reselect it.
// BFME 1 offsets come from this body: module data force-mounted byte +0x268
// and disguise template name +0x25C; owner conditions at Object+0x110
// (disguised bit 267 is +0x130 bit 0x800, mounted bit 203 is +0x128 bit
// 0x800), AI +0x204 slot 127; drawable selected byte +0x3AC, +0x3B8 value,
// +0xB0 opacity; module +0xEC; TheGameClient slot 24, TheInGameUI slot 56.
//
///////////////////////////////////////////////////////////////////////////////

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

#include "Lib/Coord3D.h"
#include "ascii_string.h"

// The owner's 40-byte model-condition mask. The two matched re-apply calls
// are ledgered with different BitFlags spellings (304 and 320 bits; both are
// ten words), so the copy is passed to each under its own spelling.
template <int NUMBITS>
class BitFlags
{
public:
	UnsignedInt m_words[ 10 ];
};

enum DrawableStatus
{
	DRAWABLE_STATUS_NONE = 0
};

// Retail ?getFinalOverride@Overridable@@QBEPBV1@XZ (ILT 0x000022BB).
class Overridable
{
public:
	const Overridable *getFinalOverride() const;
	const Overridable *friend_getFinalOverride() const
	{
		if( m_nextOverride )
			return m_nextOverride->getFinalOverride();
		return this;
	}

	unsigned char m_unmodelled_00[ 4 ];
	Overridable *m_nextOverride;			// +0x04
};

class ThingTemplate : public Overridable
{
};

class Thing
{
public:
	void setOrientation( Real angle );
};

class Drawable : public Thing
{
public:
	void setPosition( const Coord3D *pos );

	unsigned char m_unmodelled_000[ 0xB0 ];
	Real m_opacity;							// +0xB0
	unsigned char m_unmodelled_0B4[ 0x3AC - 0xB4 ];
	Bool m_selected;						// +0x3AC
	unsigned char m_unmodelled_3AD[ 0x3B8 - 0x3AD ];
	void *m_3B8;							// +0x3B8
};

// Retail ?bfmeSendCF@BfmeThingCF@@QAEXPAX@Z (0x00413FA0): stores its argument
// at Drawable+0x3B8 and forwards it; called on the new drawable.
class BfmeThingCF
{
public:
	void bfmeSendCF( void *what );
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
	BFME_SLOT( 96 ) BFME_SLOT( 97 ) BFME_SLOT( 98 ) BFME_SLOT( 99 ) BFME_SLOT( 100 ) BFME_SLOT( 101 )
	BFME_SLOT( 102 ) BFME_SLOT( 103 ) BFME_SLOT( 104 ) BFME_SLOT( 105 ) BFME_SLOT( 106 )
	BFME_SLOT( 107 ) BFME_SLOT( 108 ) BFME_SLOT( 109 ) BFME_SLOT( 110 ) BFME_SLOT( 111 )
	BFME_SLOT( 112 ) BFME_SLOT( 113 ) BFME_SLOT( 114 ) BFME_SLOT( 115 ) BFME_SLOT( 116 )
	BFME_SLOT( 117 ) BFME_SLOT( 118 ) BFME_SLOT( 119 ) BFME_SLOT( 120 ) BFME_SLOT( 121 )
	BFME_SLOT( 122 ) BFME_SLOT( 123 ) BFME_SLOT( 124 ) BFME_SLOT( 125 ) BFME_SLOT( 126 )
	virtual void slot127( Int mode );															// slot 127
};

// The weapon-set and armor-set flag helpers keep the receiver-typed names
// the ledger carries (as ToggleMountedSpecialAbilityUpdate's override does).
class Gen001C9A10 { public: void handle( Int flag ); };
class Rva001BEEE0GuardedVCall { public: void forward( Int flag ); };

class Object : public Thing
{
public:
	BFME_SLOT( 0 ) BFME_SLOT( 1 ) BFME_SLOT( 2 ) BFME_SLOT( 3 ) BFME_SLOT( 4 )
	BFME_SLOT( 5 ) BFME_SLOT( 6 ) BFME_SLOT( 7 ) BFME_SLOT( 8 ) BFME_SLOT( 9 )
	virtual Drawable *getDrawable() const;														// slot 10

	void notifyModelConditionChanged();
	void clearModelConditionFlags( const BitFlags<304> &clr );
	// Ledgered placeholder for the set-only partner (clearAndSet with an empty
	// clear mask, ObjectModelConditionFlags.cpp).
	void bfmeClearYG( const BitFlags<320> &set );

	const ThingTemplate *getTemplate() const
	{
		return !m_template ? 0 : (const ThingTemplate *)m_template->friend_getFinalOverride();
	}
	const Coord3D *getPosition() const { return &m_pos; }
	Real getOrientation() const { return m_orientation; }
	DisguiseAI *getAI() const { return m_ai; }

	UnsignedInt testModelConditionBit( UnsignedInt bit ) const
	{
		return m_conditions.m_words[ bit >> 5 ] & ( 1U << ( bit & 0x1F ) );
	}
	void setModelConditionBit( UnsignedInt bit )
	{
		if( !testModelConditionBit( bit ) )
		{
			m_conditions.m_words[ bit >> 5 ] |= 1U << ( bit & 0x1F );
			notifyModelConditionChanged();
		}
	}

	const ThingTemplate *m_template;		// +0x04
	unsigned char m_unmodelled_008[ 0x38 - 0x08 ];
	Coord3D m_pos;							// +0x38
	Real m_orientation;						// +0x44
	unsigned char m_unmodelled_048[ 0x110 - 0x48 ];
	BitFlags<320> m_conditions;				// +0x110
	unsigned char m_unmodelled_138[ 0x204 - 0x138 ];
	DisguiseAI *m_ai;						// +0x204
};

class BfmeThingFactory
{
public:
	const ThingTemplate *findTemplate( const AsciiString &name );
};

// The ledger spells the two factory calls on different view classes; one
// derives from the other so TheThingFactory reaches both.
class BFMEThingFactory : public BfmeThingFactory
{
public:
	Drawable *newDrawable( const ThingTemplate *tmplate, DrawableStatus status, Int playerIndex );
};

extern BFMEThingFactory *TheThingFactory;

class GameLogic
{
public:
	void bindObjectAndDrawable( Object *obj, Drawable *draw );
};

extern GameLogic *TheGameLogic;

class GameClient
{
public:
	BFME_SLOT( 0 ) BFME_SLOT( 1 ) BFME_SLOT( 2 ) BFME_SLOT( 3 ) BFME_SLOT( 4 ) BFME_SLOT( 5 )
	BFME_SLOT( 6 ) BFME_SLOT( 7 ) BFME_SLOT( 8 ) BFME_SLOT( 9 ) BFME_SLOT( 10 ) BFME_SLOT( 11 )
	BFME_SLOT( 12 ) BFME_SLOT( 13 ) BFME_SLOT( 14 ) BFME_SLOT( 15 ) BFME_SLOT( 16 ) BFME_SLOT( 17 )
	BFME_SLOT( 18 ) BFME_SLOT( 19 ) BFME_SLOT( 20 ) BFME_SLOT( 21 ) BFME_SLOT( 22 ) BFME_SLOT( 23 )
	virtual void destroyDrawable( Drawable *draw );												// slot 24
};

extern GameClient *TheGameClient;

class InGameUI
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
	BFME_SLOT( 54 ) BFME_SLOT( 55 )
	virtual void selectDrawable( Drawable *draw );												// slot 56
};

extern InGameUI *TheInGameUI;

class SpecialDisguiseUpdateModuleData
{
public:
	unsigned char m_unmodelled_000[ 0x25C ];
	AsciiString m_disguiseAsTemplate;		// +0x25C
	unsigned char m_unmodelled_260[ 0x268 - 0x260 ];
	Bool m_forceMounted;					// +0x268
};

class SpecialDisguiseUpdate
{
public:
	void changeVisualDisguise( Bool useOwnTemplate );

private:
	// The disguise template lookup (BFME 2 keeps it out of line as
	// rva004B031E; BFME 1 inlines it at both uses).
	const ThingTemplate *getDisguiseTemplate() const
	{
		const SpecialDisguiseUpdateModuleData *data = m_moduleData;
		return TheThingFactory->findTemplate( data->m_disguiseAsTemplate );
	}

	void *m_vptr;
	const SpecialDisguiseUpdateModuleData *m_moduleData;	// +0x04
	Object *m_object;										// +0x08
	unsigned char m_unmodelled_0C[ 0xEC - 0x0C ];
	Real m_opacity;											// +0xEC
};

void SpecialDisguiseUpdate::changeVisualDisguise( Bool useOwnTemplate )
{
	Object *obj = m_object;
	Drawable *draw = obj->getDrawable();
	Bool wasSelected = draw->m_selected != 0;

	if( m_moduleData->m_forceMounted && obj->testModelConditionBit( 267 ) )
	{
		obj->setModelConditionBit( 203 );
		obj->getAI()->slot127( 7 );
		( (Gen001C9A10 *)obj )->handle( 0x15 );
		( (Rva001BEEE0GuardedVCall *)obj )->forward( 6 );
	}

	if( !getDisguiseTemplate() )
		return;

	BitFlags<320> conditions = obj->m_conditions;
	void *saved3B8 = draw->m_3B8;
	TheGameClient->destroyDrawable( draw );

	if( useOwnTemplate )
		draw = TheThingFactory->newDrawable( obj->getTemplate(), DRAWABLE_STATUS_NONE, -1 );
	else
		draw = TheThingFactory->newDrawable( getDisguiseTemplate(), DRAWABLE_STATUS_NONE, -1 );

	if( !draw )
		return;

	TheGameLogic->bindObjectAndDrawable( obj, draw );
	draw->setPosition( obj->getPosition() );
	draw->setOrientation( obj->getOrientation() );
	draw->m_opacity = m_opacity;
	obj->clearModelConditionFlags( *(const BitFlags<304> *)&conditions );
	obj->bfmeClearYG( conditions );
	( (BfmeThingCF *)draw )->bfmeSendCF( saved3B8 );
	if( wasSelected )
		TheInGameUI->selectDrawable( draw );
}
