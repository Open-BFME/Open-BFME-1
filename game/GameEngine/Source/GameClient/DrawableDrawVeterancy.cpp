// cl: /Igame/Libraries/Source/WWVegas/WWLib /DNDEBUG /MD /Ob1
// ?drawVeterancy@Drawable@@AAEXXZ

// Retail 0x00420670, 373 bytes, and its file-local helper 0x00418600, 178
// bytes.
//
// Identity: the matched Drawable::drawIconUI dispatch
// (Drawable_drawIconUI_Dispatch.cpp) calls drawVeterancy() through ILT
// 0x00038AAA, and tools/ilt_oracle.py confirms ?drawVeterancy@Drawable@@AAEXXZ
// at that ILT. BFME dropped the Zero Hour health-bar region argument. The
// body draws through the matched rva00420360 (DrawableVeterancyIcons.cpp),
// which renders the Good_Vet/Evil_Vet icon rows.
//
// The helper takes the Drawable in EAX (compiler-private ABI of a static
// function with one caller): it looks up the PlayerTemplate whose side is
// the template's default owning side and returns its byte at +0x118, which
// drawVeterancy passes on as the Evil-icon selector. KindOf 108 and 10 are
// HORDE and MONSTER in retail's KindOf name table (0x012AA068).

#include "ascii_string.h"

#include "../../Include/Common/ScalarTypes.h"


#ifndef NULL
#define NULL 0
#endif

#include "../../Include/Common/Enums/KindOfType.h"





// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	const Overridable *getFinalOverride() const;

	void *m_vtable;
	Overridable *m_nextOverride;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	unsigned char m_pad008[ 0x28 - 8 ];
	AsciiString m_defaultOwningSide;			// +0x28
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	Bool isKindOf( KindOfType kind ) const;

	const ThingTemplate *getTemplateBfme() const
	{
		// spelled as Thing_isKindOf.cpp's copy, which is retail's 0x00098E50
		const ThingTemplate *thingTemplate = m_template;
		if ( thingTemplate == 0 )
			return 0;
		if ( thingTemplate->m_nextOverride )
			thingTemplate = (const ThingTemplate *)thingTemplate->m_nextOverride->getFinalOverride();
		return thingTemplate;
	}

	void *m_vtable;
	const ThingTemplate *m_template;			// +0x04
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerTemplate.h
class PlayerTemplate
{
public:
	unsigned char m_pad000[ 8 ];
	AsciiString m_side;						// +0x08
	unsigned char m_pad00c[ 0x118 - 0xC ];
	Bool m_flag118;							// +0x118
	unsigned char m_pad119[ 0x124 - 0x119 ];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerTemplate.h
class PlayerTemplateStore
{
public:
	const PlayerTemplate *getNthPlayerTemplate( Int i ) const;
	Int getPlayerTemplateCount() const { return m_playerTemplatesEnd - m_playerTemplates; }

	unsigned char m_pad000[ 8 ];
	PlayerTemplate *m_playerTemplates;			// +0x08, vector begin
	PlayerTemplate *m_playerTemplatesEnd;		// +0x0c, vector end
};

extern PlayerTemplateStore *ThePlayerTemplateStore;

class Drawable;

#define RVA00420670_SLOT(n) virtual void slot##n();

// Returned by the horde contain's slot 26; slot 10 yields the Drawable the
// icons are drawn on.
class Rva00420670Member
{
public:
	RVA00420670_SLOT(00) RVA00420670_SLOT(01) RVA00420670_SLOT(02) RVA00420670_SLOT(03)
	RVA00420670_SLOT(04) RVA00420670_SLOT(05) RVA00420670_SLOT(06) RVA00420670_SLOT(07)
	RVA00420670_SLOT(08) RVA00420670_SLOT(09)
	virtual Drawable *slot10();
};

class Rva00420670Horde
{
public:
	RVA00420670_SLOT(00) RVA00420670_SLOT(01) RVA00420670_SLOT(02) RVA00420670_SLOT(03)
	RVA00420670_SLOT(04) RVA00420670_SLOT(05) RVA00420670_SLOT(06) RVA00420670_SLOT(07)
	RVA00420670_SLOT(08) RVA00420670_SLOT(09) RVA00420670_SLOT(10) RVA00420670_SLOT(11)
	RVA00420670_SLOT(12) RVA00420670_SLOT(13) RVA00420670_SLOT(14) RVA00420670_SLOT(15)
	RVA00420670_SLOT(16) RVA00420670_SLOT(17) RVA00420670_SLOT(18) RVA00420670_SLOT(19)
	RVA00420670_SLOT(20) RVA00420670_SLOT(21) RVA00420670_SLOT(22) RVA00420670_SLOT(23)
	RVA00420670_SLOT(24) RVA00420670_SLOT(25) RVA00420670_SLOT(26) RVA00420670_SLOT(27)
	RVA00420670_SLOT(28) RVA00420670_SLOT(29) RVA00420670_SLOT(30) RVA00420670_SLOT(31)
	RVA00420670_SLOT(32) RVA00420670_SLOT(33) RVA00420670_SLOT(34) RVA00420670_SLOT(35)
	RVA00420670_SLOT(36) RVA00420670_SLOT(37) RVA00420670_SLOT(38) RVA00420670_SLOT(39)
	RVA00420670_SLOT(40) RVA00420670_SLOT(41) RVA00420670_SLOT(42) RVA00420670_SLOT(43)
	RVA00420670_SLOT(44) RVA00420670_SLOT(45) RVA00420670_SLOT(46) RVA00420670_SLOT(47)
	RVA00420670_SLOT(48) RVA00420670_SLOT(49) RVA00420670_SLOT(50) RVA00420670_SLOT(51)
	RVA00420670_SLOT(52) RVA00420670_SLOT(53) RVA00420670_SLOT(54) RVA00420670_SLOT(55)
	RVA00420670_SLOT(56) RVA00420670_SLOT(57) RVA00420670_SLOT(58) RVA00420670_SLOT(59)
	RVA00420670_SLOT(60)
	virtual Rva00420670Member *slot61();
	RVA00420670_SLOT(62)
	virtual Rva00420670Member *slot63();
};

class ContainModuleInterface
{
public:
	RVA00420670_SLOT(00) RVA00420670_SLOT(01) RVA00420670_SLOT(02) RVA00420670_SLOT(03)
	RVA00420670_SLOT(04) RVA00420670_SLOT(05) RVA00420670_SLOT(06) RVA00420670_SLOT(07)
	RVA00420670_SLOT(08) RVA00420670_SLOT(09) RVA00420670_SLOT(10) RVA00420670_SLOT(11)
	RVA00420670_SLOT(12) RVA00420670_SLOT(13) RVA00420670_SLOT(14) RVA00420670_SLOT(15)
	RVA00420670_SLOT(16) RVA00420670_SLOT(17) RVA00420670_SLOT(18) RVA00420670_SLOT(19)
	RVA00420670_SLOT(20) RVA00420670_SLOT(21) RVA00420670_SLOT(22) RVA00420670_SLOT(23)
	RVA00420670_SLOT(24) RVA00420670_SLOT(25)
	virtual Rva00420670Horde *slot26();
};

#undef RVA00420670_SLOT

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object : public Thing
{
public:
	unsigned char m_pad008[ 0x1FC - 8 ];
	ContainModuleInterface *m_contain;			// +0x1fc
	unsigned char m_pad200[ 0x210 - 0x200 ];
	void *m_field210;						// +0x210
	Object *containedBy;						// +0x214

	ContainModuleInterface *getContain() const { return m_contain; }
};

// The experience-level list position the ExperienceLevelSystem queries pass
// by value (see Rva0037F190ExperienceLevelSystem.cpp).
struct Rva0037F220Iterator
{
	Rva0037F220Iterator() {}
	Rva0037F220Iterator( const Rva0037F220Iterator &that ) : m_sentinel( that.m_sentinel ), m_current( that.m_current ) {}

	void *m_sentinel;
	void *m_current;
};

class ExperienceLevelSystem
{
public:
	Rva0037F220Iterator rva0037F220( Rva0037F220Iterator value );
};
extern ExperienceLevelSystem *TheExperienceLevelSystem;

class Drawable : public Thing
{
private:
	void drawVeterancy();

	unsigned char m_pad008[ 0xFC - 8 ];
	Object *m_object;						// +0xfc
};

typedef void (ExperienceLevelSystem::*Rva0037F190Call)( Rva0037F220Iterator *, Object * );
typedef Bool (ExperienceLevelSystem::*Rva0037E810Call)( Rva0037F220Iterator );
typedef Int (ExperienceLevelSystem::*Rva0037D810Call)( Rva0037F220Iterator );
typedef Int (ExperienceLevelSystem::*Rva0037D840Call)( Rva0037F220Iterator );
typedef Rva0037F220Iterator (ExperienceLevelSystem::*Rva0037F220Call)( Rva0037F220Iterator );
typedef void (Drawable::*Rva00420360Call)( Bool, Int );

union Rva0037F190CallValue { void (*freeFunction)(); Rva0037F190Call memberFunction; };
union Rva0037E810CallValue { void (*freeFunction)(); Rva0037E810Call memberFunction; };
union Rva0037D810CallValue { void (*freeFunction)(); Rva0037D810Call memberFunction; };
union Rva0037D840CallValue { void (*freeFunction)(); Rva0037D840Call memberFunction; };
union Rva0037F220CallValue { void (*freeFunction)(); Rva0037F220Call memberFunction; };
union Rva00420360CallValue { void (*freeFunction)(); Rva00420360Call memberFunction; };

extern void j_0000edc7();
extern void j_0000dfc1();
extern void j_000012a8();
extern void j_0000bc21();
extern void j_00041295();
extern void j_0001fc53();

// ?drawableSideFlag@@YA_NPBVThing@@@Z
static Bool drawableSideFlag( const Thing *thing )
{
	if ( thing->getTemplateBfme() )
	{
		const AsciiString &side = thing->getTemplateBfme()->m_defaultOwningSide;
		for ( Int i = 0; i < ThePlayerTemplateStore->getPlayerTemplateCount(); ++i )
		{
			const PlayerTemplate *playerTemplate = ThePlayerTemplateStore->getNthPlayerTemplate( i );
			if ( playerTemplate && side.StringBase<char>::compare( playerTemplate->m_side ) == 0 )
				return playerTemplate->m_flag118;
		}
	}
	return false;
}

void Drawable::drawVeterancy()
{
	Object *obj = m_object;
	if ( obj == NULL || obj->m_field210 == NULL )
		return;
	if ( !obj->isKindOf( KINDOF_HORDE ) && !obj->isKindOf( KINDOF_MONSTER ) )
		return;

	Rva0037F190CallValue find = { j_0000edc7 };
	Rva0037E810CallValue isValid = { j_0000dfc1 };
	Rva0037D810CallValue getLevel = { j_000012a8 };
	Rva0037D840CallValue getRank = { j_0000bc21 };
	Rva0037F220CallValue next = { j_00041295 };

	Rva0037F220Iterator pos;
	(TheExperienceLevelSystem->*find.memberFunction)( &pos, obj );
	if ( !(TheExperienceLevelSystem->*isValid.memberFunction)( pos ) )
		return;
	Int level = (TheExperienceLevelSystem->*getLevel.memberFunction)( pos );
	if ( level <= 1 )
		return;
	if ( (TheExperienceLevelSystem->*getRank.memberFunction)( pos ) <= 1 &&
		!(TheExperienceLevelSystem->*isValid.memberFunction)(
			TheExperienceLevelSystem->rva0037F220( pos ) ) )
		return;

	Bool flag = drawableSideFlag( this );

	Drawable *draw;
	if ( obj->isKindOf( KINDOF_HORDE ) && obj->getContain() )
	{
		Rva00420670Horde *horde = obj->getContain()->slot26();
		if ( horde == NULL )
			return;
		Rva00420670Member *member = horde->slot63();
		if ( member == NULL )
		{
			member = horde->slot61();
			if ( member == NULL )
				return;
		}
		draw = member->slot10();
	}
	else
	{
		Object *container = obj->containedBy;
		if ( container && container->isKindOf( KINDOF_HORDE ) )
			return;
		draw = this;
	}

	if ( draw )
	{
		Rva00420360CallValue drawIcons = { j_0001fc53 };
		(draw->*drawIcons.memberFunction)( flag, level );
	}
}
