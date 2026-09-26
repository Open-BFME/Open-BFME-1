// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

class GameWindow;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/WinInstanceData.h
class WinInstanceData
{
public:
	char m_unmodelled[ 0x14 ];
	GameWindow *m_owner;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	WinInstanceData *winGetInstanceData();
	void winSetUserData( void *userData );
};

// The block GameWindowManager::winCreate (0x0047EDE0) reads: it takes the
// creation parameters BFME's winCreate no longer takes one by one.  +0x00 is
// the parent, because winCreate passes it to addWindowToParent; +0x18 is an
// allocator, because winCreate calls it when it is set and falls back to
// allocateNewWindow when it is not.  The rest is named by offset.
struct Rva0047EDE0CreateInfo
{
	Rva0047EDE0CreateInfo()
		: m_parent( 0 )
		, m_field04( 0 )
		, m_field08( 0 )
		, m_field0C( 0 )
		, m_field10( 0 )
		, m_field14( 0 )
		, m_allocator( 0 )
		, m_field1C( 0 )
		, m_field20( 0 )
		, m_field24( 0 )
		, m_field28( 0 )
		, m_field2C( 0 )
		, m_field30( 0 ) {}

	GameWindow *m_parent;
	unsigned int m_field04;
	int m_field08;
	int m_field0C;
	int m_field10;
	int m_field14;
	void *m_allocator;
	void *m_field1C;
	int m_field20;
	int m_field24;
	int m_field28;
	int m_field2C;
	int m_field30;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowManager.h
// Slot 29 is winCreate: slot 26 is winCreateFromScript, 27 winCreateLayout,
// 28 freeStaticStrings and 30 winDestroy, which is the upstream declaration
// order, and the body behind slot 29 calls linkWindow and addWindowToParent.
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
	virtual void slot27(); virtual void slot28();
	virtual GameWindow *winCreate( Rva0047EDE0CreateInfo *info );
};

extern GameWindowManager *TheWindowManager;

class __single_inheritance FunctorTargetSingle
{
};
typedef void (FunctorTargetSingle::*FunctorMethodSingle)( void );

struct FunctorBindingSingle
{
	FunctorBindingSingle( FunctorMethodSingle method, FunctorTargetSingle *target )
		: m_target( target ), m_method( method ) {}

	FunctorTargetSingle *m_target;
	FunctorMethodSingle m_method;
};

class Rva0058D0A0FunctorSingleWrapper;

// game/GameEngine/Source/Common/FunctorBindSingleWrapperCtors.cpp owns this
// constructor at 0x00590EF0; it takes the binding by value and allocates the
// wrapper, so the holder itself is one pointer.
class Rva00590EF0FunctorSingleHolder
{
public:
	Rva00590EF0FunctorSingleHolder( FunctorBindingSingle binding );

	Rva0058D0A0FunctorSingleWrapper *m_ptr;
};

struct Gen_p24pod
{
	int a[ 5 ];
	unsigned char first;
	unsigned char second;
};

// Layout witnessed by the constructor at 0x00595AC0, landed as
// ??0AptPalantirHeroSelector@@QAE@XZ: it writes false to +0x1A0 and null to
// +0x1A4 as its last two stores.
class AptPalantirHeroSelector : public FunctorTargetSingle
{
public:
	void rva00595d40();

private:
	struct HeroListEntry
	{
		unsigned char bytes[ 12 ];
	};

	bool m_active;
	void *m_heroes;
	Gen_p24pod m_slots[ 17 ];
	bool m_selectAll;
	GameWindow *m_window;
};

// @?rva00595d40@AptPalantirHeroSelector@@QAEXXZ 0x00595D40
void AptPalantirHeroSelector::rva00595d40()
{
	if( m_window == 0 )
	{
		union
		{
			void (*raw)( void );
			FunctorMethodSingle member;
		} callback;

		Rva0047EDE0CreateInfo info;
		info.m_field04 = 0x08000400;
		info.m_field08 = -128;
		info.m_field0C = -128;
		info.m_field10 = -128;
		info.m_field14 = -128;
		info.m_field1C = (void *)0x00437E89;

		m_window = TheWindowManager->winCreate( &info );
		if( m_window != 0 )
		{
			m_window->winGetInstanceData()->m_owner = m_window;

			callback.raw = (void (*)( void ))0x00412FC6;
			m_window->winSetUserData( new Rva00590EF0FunctorSingleHolder(
				FunctorBindingSingle( callback.member, this ) ) );
		}
	}
}
