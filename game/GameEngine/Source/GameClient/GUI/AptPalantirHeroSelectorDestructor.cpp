// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringinline /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#include <list>

#include "ascii_string.h"

class GameWindow;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowManager.h
// Slot 30 is winDestroy (see AptPalantirHeroSelectorRva00595D40.cpp: slot 29
// is winCreate, 30 winDestroy in upstream declaration order).
class GameWindowManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26();
	virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual int winDestroy( GameWindow *window );
};

extern GameWindowManager *TheWindowManager;

class WindowManager
{
public:
	void removeAptObject( const AsciiString &name );
};

extern WindowManager *g_theWindowManager;
extern void j_00025464();

typedef void (WindowManager::*RemoveNameMember)( const AsciiString * );

union RemoveNameCast
{
	void (*raw)();
	RemoveNameMember member;
};

static __forceinline void removeName( WindowManager *manager,
	void (*function)(), AsciiString *name )
{
	RemoveNameCast cast;
	cast.raw = function;
	(manager->*cast.member)( name );
}

class __single_inheritance FunctorTargetSingle
{
};

struct Gen_p24pod
{
	int a[ 5 ];
	unsigned char first;
	unsigned char second;
};

// Element of the list at +0x4: the body only frees its 0x14-byte nodes, so
// nothing names what an entry holds. Same spelling as the landed sibling
// AptPalantirHeroSelectorResetSlots.cpp.
struct Rva0058D930ListEntry
{
	unsigned char bytes[ 12 ];
};

// Layout witnessed by the constructor at 0x00595AC0, landed as
// ??0AptPalantirHeroSelector@@QAE@XZ. The destructor reads only m_list04 and
// m_window; the other members keep offset spellings because nothing here
// witnesses what they hold.
class AptPalantirHeroSelector : public FunctorTargetSingle
{
public:
	~AptPalantirHeroSelector();

private:
	bool m_field00;
	_STL::list<Rva0058D930ListEntry> m_list04;
	Gen_p24pod m_field08[ 17 ];
	bool m_field1A0;
	GameWindow *m_window;
};

// The destructor role is proven (the GameClient dtor 0x00596500+0x2F6 calls
// ILT 0x60D7 -> 0x00591D60 on esi+0x2B8, and the GameClient ctor builds this
// object at +0x2B8), while the class name AptPalantirHeroSelector is inherited
// from the 2026-09-08 ctor landing and is not independently verified (no RTTI;
// the string "HeroSelector" does not occur in the EXE).
// ??1AptPalantirHeroSelector@@QAE@XZ
AptPalantirHeroSelector::~AptPalantirHeroSelector()
{
	if( m_window != 0 )
		TheWindowManager->winDestroy( m_window );

	if( g_theWindowManager != 0 )
	{
		{
			AsciiString name( "Palantir/HeroSelectUI/SelectAllHeroesBttn/" );
			g_theWindowManager->removeAptObject( name );
		}

		for( int index = 0; index < 17; ++index )
		{
			AsciiString name;
			name.format( "Palantir/HeroSelectUI/Hero%d/", index + 1 );
			g_theWindowManager->removeAptObject( name );
		}

		{
			AsciiString name( "AptPalantir::OnBttnSelectAllHeroes" );
			removeName( g_theWindowManager, j_00025464, &name );
		}
	}
}
