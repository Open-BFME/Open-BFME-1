// ?d_0023b7a0@@YAXXZ
// partial score=0.987 date=2026-09-18
// cl: /DNDEBUG /MD /EHsc
// Open-BFME: HordeContain interface slot 87, retail 0x0023B7A0.
//
// The HordeContain constructor at 0x0023EAF0 installs vtable 0x010AED58 at
// container+0xE4, and slot 87 of that vtable reaches this body through the ILT
// thunk at 0x00007A36. `this` is therefore the interface subobject, not the
// container, so every container member is read at a negative offset: the owner
// Object at this-0xDC is container+0x08, and the container itself is this-0xE4.
// ?bfmeReleaseMember@BfmeHordeContainOwner@@QAEXPAVObject@@@Z at 0x002429C0
// names both of those offsets from the other side.
//
// The body builds a replacement object for the horde. It asks the container for
// a ThingTemplate, hands the template and its name to the spawner interface at
// container+0xD4, copies the old object's state onto the new one, and moves the
// remaining LifetimeUpdate time across. The tail runs whether or not a template
// came back, which is why the template test jumps into the middle of the block
// instead of past it.
//
// The name key is a function-local static: retail reads the guard byte at
// 0x012EFAD8, calls nameToKey once, and stores the key at 0x012EFAD4. The
// unwind action that clears that guard bit is the funclet at 0x00C0DB70,
// already landed as ?Rva00C0DB70ClearFlag@@YAIXZ.
//
// Every interface here is opaque apart from the slots this body uses, so the
// earlier slots are placeholders.
//
// This body compiles to retail's 465 bytes and ten of them still differ. Four
// instructions pick a different scratch register. Retail loads the transform
// parameter into eax at +0xAE and this build loads it into ecx. Retail then
// loads the experience tracker into ecx at +0xD8 and the level into edx at
// +0xE4, and this build swaps that pair. The swap leaves ecx busy until the
// subtraction, so retail's early load of TheExperienceLevelSystem lands after
// the two pushes here instead of before them. Every instruction before +0xAE
// matches retail byte for byte.

typedef bool Bool;
typedef unsigned int UnsignedInt;

enum NameKeyType { NAMEKEY_INVALID = 0 };

class AttributeModifierPoolUpdate;
class ContainModuleInterface;
class Matrix3DTN;
class Module;
class Object;
class ThingTemplate;
struct Rva00367E30Sink;

#define BFME_SLOT( N ) virtual int bfmeSlot##N( void ) = 0

// the interface ContainModuleInterface::getHordeContainInterface hands back
class HordeContainInterface
{
public:
	BFME_SLOT( 000 ); BFME_SLOT( 001 ); BFME_SLOT( 002 ); BFME_SLOT( 003 );
	virtual void bfmeSetHordeEnabled( Bool enabled ) = 0;			///< slot 4
	BFME_SLOT( 005 ); BFME_SLOT( 006 ); BFME_SLOT( 007 ); BFME_SLOT( 008 );
	BFME_SLOT( 009 ); BFME_SLOT( 010 ); BFME_SLOT( 011 ); BFME_SLOT( 012 );
	BFME_SLOT( 013 ); BFME_SLOT( 014 ); BFME_SLOT( 015 ); BFME_SLOT( 016 );
	BFME_SLOT( 017 ); BFME_SLOT( 018 ); BFME_SLOT( 019 ); BFME_SLOT( 020 );
	BFME_SLOT( 021 ); BFME_SLOT( 022 ); BFME_SLOT( 023 ); BFME_SLOT( 024 );
	BFME_SLOT( 025 ); BFME_SLOT( 026 ); BFME_SLOT( 027 ); BFME_SLOT( 028 );
	BFME_SLOT( 029 ); BFME_SLOT( 030 ); BFME_SLOT( 031 ); BFME_SLOT( 032 );
	BFME_SLOT( 033 ); BFME_SLOT( 034 ); BFME_SLOT( 035 ); BFME_SLOT( 036 );
	BFME_SLOT( 037 ); BFME_SLOT( 038 ); BFME_SLOT( 039 ); BFME_SLOT( 040 );
	BFME_SLOT( 041 ); BFME_SLOT( 042 ); BFME_SLOT( 043 ); BFME_SLOT( 044 );
	BFME_SLOT( 045 ); BFME_SLOT( 046 ); BFME_SLOT( 047 ); BFME_SLOT( 048 );
	BFME_SLOT( 049 ); BFME_SLOT( 050 ); BFME_SLOT( 051 ); BFME_SLOT( 052 );
	BFME_SLOT( 053 ); BFME_SLOT( 054 ); BFME_SLOT( 055 ); BFME_SLOT( 056 );
	BFME_SLOT( 057 ); BFME_SLOT( 058 ); BFME_SLOT( 059 ); BFME_SLOT( 060 );
	BFME_SLOT( 061 ); BFME_SLOT( 062 ); BFME_SLOT( 063 ); BFME_SLOT( 064 );
	BFME_SLOT( 065 ); BFME_SLOT( 066 ); BFME_SLOT( 067 ); BFME_SLOT( 068 );
	BFME_SLOT( 069 ); BFME_SLOT( 070 ); BFME_SLOT( 071 ); BFME_SLOT( 072 );
	BFME_SLOT( 073 ); BFME_SLOT( 074 ); BFME_SLOT( 075 ); BFME_SLOT( 076 );
	BFME_SLOT( 077 ); BFME_SLOT( 078 ); BFME_SLOT( 079 ); BFME_SLOT( 080 );
	BFME_SLOT( 081 ); BFME_SLOT( 082 ); BFME_SLOT( 083 ); BFME_SLOT( 084 );
	BFME_SLOT( 085 ); BFME_SLOT( 086 ); BFME_SLOT( 087 ); BFME_SLOT( 088 );
	BFME_SLOT( 089 ); BFME_SLOT( 090 ); BFME_SLOT( 091 ); BFME_SLOT( 092 );
	BFME_SLOT( 093 ); BFME_SLOT( 094 ); BFME_SLOT( 095 ); BFME_SLOT( 096 );
	BFME_SLOT( 097 ); BFME_SLOT( 098 ); BFME_SLOT( 099 ); BFME_SLOT( 100 );
	BFME_SLOT( 101 ); BFME_SLOT( 102 ); BFME_SLOT( 103 ); BFME_SLOT( 104 );
	BFME_SLOT( 105 ); BFME_SLOT( 106 ); BFME_SLOT( 107 ); BFME_SLOT( 108 );
	BFME_SLOT( 109 ); BFME_SLOT( 110 );
	virtual void bfmeFinish( void ) = 0;							///< slot 111
};

// the module interface at Object+0x1FC
class ContainModuleInterface
{
public:
	BFME_SLOT( 000 ); BFME_SLOT( 001 ); BFME_SLOT( 002 ); BFME_SLOT( 003 );
	BFME_SLOT( 004 ); BFME_SLOT( 005 ); BFME_SLOT( 006 ); BFME_SLOT( 007 );
	BFME_SLOT( 008 ); BFME_SLOT( 009 ); BFME_SLOT( 010 ); BFME_SLOT( 011 );
	BFME_SLOT( 012 ); BFME_SLOT( 013 ); BFME_SLOT( 014 ); BFME_SLOT( 015 );
	BFME_SLOT( 016 ); BFME_SLOT( 017 ); BFME_SLOT( 018 ); BFME_SLOT( 019 );
	BFME_SLOT( 020 ); BFME_SLOT( 021 ); BFME_SLOT( 022 ); BFME_SLOT( 023 );
	BFME_SLOT( 024 ); BFME_SLOT( 025 );
	virtual HordeContainInterface *getHordeContainInterface( void ) = 0;	///< slot 26
};

// the interface at container+0xD4, vtable 0x010AEFC4
class BfmeHordeSpawnerInterface
{
public:
	virtual Object *bfmeSpawn( ThingTemplate *tmpl, ContainModuleInterface *contain,
		Object *owner, const char *name, int flags ) = 0;			///< slot 0
};

// the view's own vtable, reached on `this`; slot 44 is the upgrade replay that
// ?bfmeReleaseMember@BfmeHordeContainOwner@@QAEXPAVObject@@@Z also calls
class BfmeHordeContainView
{
public:
	BFME_SLOT( 000 ); BFME_SLOT( 001 ); BFME_SLOT( 002 ); BFME_SLOT( 003 );
	BFME_SLOT( 004 ); BFME_SLOT( 005 ); BFME_SLOT( 006 ); BFME_SLOT( 007 );
	BFME_SLOT( 008 ); BFME_SLOT( 009 ); BFME_SLOT( 010 ); BFME_SLOT( 011 );
	BFME_SLOT( 012 ); BFME_SLOT( 013 ); BFME_SLOT( 014 ); BFME_SLOT( 015 );
	BFME_SLOT( 016 ); BFME_SLOT( 017 ); BFME_SLOT( 018 ); BFME_SLOT( 019 );
	BFME_SLOT( 020 ); BFME_SLOT( 021 ); BFME_SLOT( 022 ); BFME_SLOT( 023 );
	BFME_SLOT( 024 ); BFME_SLOT( 025 ); BFME_SLOT( 026 ); BFME_SLOT( 027 );
	BFME_SLOT( 028 ); BFME_SLOT( 029 ); BFME_SLOT( 030 ); BFME_SLOT( 031 );
	BFME_SLOT( 032 ); BFME_SLOT( 033 ); BFME_SLOT( 034 ); BFME_SLOT( 035 );
	BFME_SLOT( 036 ); BFME_SLOT( 037 ); BFME_SLOT( 038 ); BFME_SLOT( 039 );
	BFME_SLOT( 040 ); BFME_SLOT( 041 ); BFME_SLOT( 042 ); BFME_SLOT( 043 );
	virtual void bfmeApplyUpgrades( UnsignedInt *upgrades, Bool force ) = 0;	///< slot 44
};

#undef BFME_SLOT

// the container method at 0x002369C0, called on this-0xE4
class Rva002369C0HordeContain
{
public:
	ThingTemplate *rva002369C0( void );
};

// the container method at 0x002341C0, called on this-0xE4
class BfmeThingCQB
{
public:
	void bfmeGoCQB( void *object );
};

// Object methods this body reaches under their pinned spellings
class BfmeOwnFDH
{
public:
	char bfmeAskFDH( int bit );
};

class Gen001C9A10
{
public:
	void handle( int bit );
};

class BfmeThingTN
{
public:
	void bfmeSetTransformTN( const Matrix3DTN *transform );
};

class BfmeGlobFEA
{
public:
	void bfmeCallFEA( void *object, int tag );
};

class Rva00367E30Owner
{
public:
	void replayEntries( Rva00367E30Sink *sink );
};

// the ThingTemplate name at +0x20 is read through the AsciiString peek inline:
// the string block holds a refcount and a length before its characters, so the
// characters start eight bytes in and a null block reads as the empty literal
class ThingTemplate
{
public:
	const char *bfmeName( void ) const
	{
		const char *data = *(const char *const *)( (const char *)this + 0x20 );
		const char *text = data + 8;

		if ( !data )
			text = "";

		return text;
	}
};

struct BfmeExperienceCounters
{
	char m_bfmeHead[ 0x28 ];
	int m_bfmeLevel;									///< retail this+0x28
};

class Rva0023B7A0HordeContainView;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
	friend class Rva0023B7A0HordeContainView;

public:
	void bfmeTransferReplacementState( Object *replacement );
	Module *findModule( NameKeyType key ) const;

	char m_bfmeHead[ 0x94 ];
	UnsignedInt m_bfmeStatus;							///< retail this+0x94
	char m_bfmeGap98[ 0x1fc - 0x98 ];
	ContainModuleInterface *m_bfmeContain;				///< retail this+0x1fc
	char m_bfmeGap200[ 0x210 - 0x200 ];
	BfmeExperienceCounters *m_bfmeExperience;			///< retail this+0x210
	char m_bfmeGap214[ 0x224 - 0x214 ];
	UnsignedInt m_bfmeUpgrades[ 6 ];					///< retail this+0x224
	char m_bfmeGap23c[ 0x370 - 0x23c ];
	int m_bfmeLogicTag;									///< retail this+0x370

private:
	AttributeModifierPoolUpdate *findAttributeModifierPoolUpdate( void ) const;
};

class LifetimeUpdate
{
public:
	void setLifetimeRange( UnsignedInt minFrames, UnsignedInt maxFrames );

	char m_bfmeHead[ 0x20 ];
	UnsignedInt m_bfmeDieFrame;							///< retail this+0x20
};

class ExperienceLevelSystem
{
public:
	void gainLevels( Object *object, int levels, Bool provideFeedback );
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey( const char *name );
};

struct Rva00367E30Logic
{
	char m_bfmeHead[ 0x3c ];
	UnsignedInt m_bfmeFrame;							///< retail this+0x3c
};

extern Rva00367E30Logic *TheBfmeGameLogic;
extern ExperienceLevelSystem *TheExperienceLevelSystem;
extern NameKeyGenerator *TheNameKeyGenerator;

class Rva0023B7A0HordeContainView
{
public:
	Object *rva0023B7A0( const Matrix3DTN *transform );

private:
	Object *bfmeOwner( void ) const
	{
		return *(Object *const *)( (const char *)this - 0xdc );
	}

	BfmeHordeSpawnerInterface &bfmeSpawner( void )
	{
		return *(BfmeHordeSpawnerInterface *)( (char *)this - 0x10 );
	}
};

// ?rva0023B7A0@Rva0023B7A0HordeContainView@@QAEPAVObject@@PBVMatrix3DTN@@@Z
Object *Rva0023B7A0HordeContainView::rva0023B7A0( const Matrix3DTN *transform )
{
	Object *owner = bfmeOwner();

	if ( !owner )
		return 0;

	ContainModuleInterface *contain = owner->m_bfmeContain;
	Object *replacement = 0;

	if ( contain )
	{
		char *container = (char *)this - 0xe4;
		ThingTemplate *tmpl = ( (Rva002369C0HordeContain *)container )->rva002369C0();

		if ( tmpl )
		{
			const char *name = tmpl->bfmeName();

			replacement = bfmeSpawner().bfmeSpawn( tmpl, contain, owner, name, 0 );

			if ( owner->m_bfmeStatus & 0x20000000 )
				owner->bfmeTransferReplacementState( replacement );

			( (BfmeGlobFEA *)TheBfmeGameLogic )->bfmeCallFEA( replacement, owner->m_bfmeLogicTag );
			( (BfmeThingTN *)replacement )->bfmeSetTransformTN( transform );
			( (BfmeThingCQB *)container )->bfmeGoCQB( replacement );

			if ( ( (BfmeOwnFDH *)owner )->bfmeAskFDH( 0x18 ) )
				( (Gen001C9A10 *)replacement )->handle( 0x18 );

			BfmeExperienceCounters *freshCounters = replacement->m_bfmeExperience;
			BfmeExperienceCounters *heldCounters = owner->m_bfmeExperience;
			int fresh = freshCounters->m_bfmeLevel;
			int held = heldCounters->m_bfmeLevel;

			TheExperienceLevelSystem->gainLevels( replacement, held - fresh, false );

			( (BfmeHordeContainView *)this )->bfmeApplyUpgrades( owner->m_bfmeUpgrades, false );

			Rva00367E30Owner *pool = (Rva00367E30Owner *)owner->findAttributeModifierPoolUpdate();

			if ( pool )
				pool->replayEntries( (Rva00367E30Sink *)replacement );

			static NameKeyType key = TheNameKeyGenerator->nameToKey( "LifetimeUpdate" );

			LifetimeUpdate *previous = (LifetimeUpdate *)owner->findModule( key );

			if ( previous )
			{
				LifetimeUpdate *fresh = (LifetimeUpdate *)replacement->findModule( key );

				if ( fresh )
				{
					UnsignedInt remaining = previous->m_bfmeDieFrame - TheBfmeGameLogic->m_bfmeFrame;

					fresh->setLifetimeRange( remaining, remaining );
				}
			}
		}

		HordeContainInterface *horde = contain->getHordeContainInterface();

		if ( horde )
		{
			horde->bfmeSetHordeEnabled( false );
			horde->bfmeFinish();
		}
	}

	return replacement;
}
