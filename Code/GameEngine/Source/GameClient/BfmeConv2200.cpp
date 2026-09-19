// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// BfmeOnlineProfileScreen destructor, retail 0x00553EE0, 702 bytes.
// Mirrors createAptScreenOnlineProfile (AptScreenFactories.cpp, retail
// 0x0055BBA0 / object ctor 0x00557C00, still gen_asm): the singleton lives at
// 0x012F4AB4 (TheBfmeOnlineProfileSlot). If this instance is the live
// singleton and g_theWindowManager (0x012F19E8) is set, it unregisters 8
// image gadgets (through _bfme_removeNamedAptGadget, already pinned by
// OnlineHomeDestructor.cpp) and 4 player-level-icon tooltips (through
// removeAptObject) by name, then clears the singleton. The base class
// destructor call (vfptr reset to ??_7BfmeAptGameWindow@@6B@ then
// bfmeDestroy(), pinned 0x00021FC1, reaching ??1S4Owner@@UAE@XZ) runs
// unconditionally, same shape as OnlineHomeDestructor.cpp / OnlineChatDestructor.cpp.

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase( const T *text );
	~StringBase();

	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	~AsciiString() {}
};

class BfmeAptGameWindow
{
public:
	virtual ~BfmeAptGameWindow()
	{
		bfmeDestroy();
	}
	void bfmeDestroy();

private:
	unsigned char m_unmodelled[ 0x38 ];
};

class WindowManager
{
public:
	void _bfme_removeNamedAptGadget( const AsciiString &name );
	void removeAptObject( const AsciiString &name );
};

extern WindowManager *g_theWindowManager;

class BfmeOnlineProfileScreen;
extern BfmeOnlineProfileScreen *TheBfmeOnlineProfileSlot;

extern const char *g_bfmeOnlineProfileImageA;
extern const char *g_bfmeOnlineProfileImageB;
extern const char *g_bfmeOnlineProfileImageC;
extern const char *g_bfmeOnlineProfileImageD;
extern const char *g_bfmeOnlineProfileImageLevelIconA;
extern const char *g_bfmeOnlineProfileImageLevelIconB;
extern const char *g_bfmeOnlineProfileImageLevelIconC;
extern const char *g_bfmeOnlineProfileImageLevelIconD;

class BfmeOnlineProfileScreen : public BfmeAptGameWindow
{
public:
	virtual ~BfmeOnlineProfileScreen();
};

BfmeOnlineProfileScreen::~BfmeOnlineProfileScreen()
{
	if( TheBfmeOnlineProfileSlot == this )
	{
		if( g_theWindowManager )
		{
			{
				AsciiString name( g_bfmeOnlineProfileImageA );
				g_theWindowManager->_bfme_removeNamedAptGadget( name );
			}
			{
				AsciiString name( g_bfmeOnlineProfileImageB );
				g_theWindowManager->_bfme_removeNamedAptGadget( name );
			}
			{
				AsciiString name( g_bfmeOnlineProfileImageC );
				g_theWindowManager->_bfme_removeNamedAptGadget( name );
			}
			{
				AsciiString name( g_bfmeOnlineProfileImageD );
				g_theWindowManager->_bfme_removeNamedAptGadget( name );
			}
			{
				AsciiString name( g_bfmeOnlineProfileImageLevelIconA );
				g_theWindowManager->_bfme_removeNamedAptGadget( name );
			}
			{
				AsciiString name( g_bfmeOnlineProfileImageLevelIconB );
				g_theWindowManager->_bfme_removeNamedAptGadget( name );
			}
			{
				AsciiString name( g_bfmeOnlineProfileImageLevelIconC );
				g_theWindowManager->_bfme_removeNamedAptGadget( name );
			}
			{
				AsciiString name( g_bfmeOnlineProfileImageLevelIconD );
				g_theWindowManager->_bfme_removeNamedAptGadget( name );
			}
			{
				AsciiString name( "OnlineShell/OnlineProfile/tooltipPlayerLevelIconGondor" );
				g_theWindowManager->removeAptObject( name );
			}
			{
				AsciiString name( "OnlineShell/OnlineProfile/tooltipPlayerLevelIconRohan" );
				g_theWindowManager->removeAptObject( name );
			}
			{
				AsciiString name( "OnlineShell/OnlineProfile/tooltipPlayerLevelIconIsengard" );
				g_theWindowManager->removeAptObject( name );
			}
			{
				AsciiString name( "OnlineShell/OnlineProfile/tooltipPlayerLevelIconMordor" );
				g_theWindowManager->removeAptObject( name );
			}
		}
		TheBfmeOnlineProfileSlot = 0;
	}
}
