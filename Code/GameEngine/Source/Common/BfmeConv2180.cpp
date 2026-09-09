// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// BfmeAptScreenSkirmish destructor, retail 0x005668C0, 300 bytes.
// Mirrors BfmeOnlineProfileScreen (BfmeConv2200.cpp): the Skirmish
// game-options APT screen singleton lives at 0x012F4B3C; when this instance
// is the live singleton and g_theWindowManager (0x012F19E8) is set, it
// unregisters 4 player-level-icon tooltips (Gondor/Rohan/Isengard/Mordor,
// strings read at retail 0x0110A2E4/0x0110A2B8/0x0110A288/0x0110A258) via
// removeAptObject, then clears the singleton. The embedded SkirmishPreferences
// member (already pinned, real body 0x0009F7A0 / ILT 0x00046B82) is
// destructed unconditionally at scope exit -- lea ecx,[esi+4] before the call
// puts the member at offset 4, right after the vfptr. This class's own
// vtable at 0x0110A314 has no recovered identity yet (its 3 slots are still
// gen-dtor/gen-thunk placeholders at 0x00566AE0/0x00566AA0/0x00566A90), so it
// is pinned as an opaque data blob rather than modelled as a real C++ vtable.

extern "C" unsigned char bfmeSkirmishOptionsVft[];

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

class SkirmishPreferences
{
public:
	virtual ~SkirmishPreferences();
};

class WindowManager
{
public:
	void removeAptObject( const AsciiString &name );
};

extern WindowManager *g_theWindowManager;

class BfmeAptScreenSkirmish;
extern BfmeAptScreenSkirmish *TheBfmeSkirmishOptionsSlot;

class BfmeAptScreenSkirmish
{
public:
	~BfmeAptScreenSkirmish();

private:
	void *m_vfptr;
	SkirmishPreferences m_prefs;
};

BfmeAptScreenSkirmish::~BfmeAptScreenSkirmish()
{
	m_vfptr = bfmeSkirmishOptionsVft;

	if( TheBfmeSkirmishOptionsSlot == this )
	{
		if( g_theWindowManager )
		{
			{
				AsciiString name( "Skirmish/tooltipPlayerLevelIconGondor" );
				g_theWindowManager->removeAptObject( name );
			}
			{
				AsciiString name( "Skirmish/tooltipPlayerLevelIconRohan" );
				g_theWindowManager->removeAptObject( name );
			}
			{
				AsciiString name( "Skirmish/tooltipPlayerLevelIconIsengard" );
				g_theWindowManager->removeAptObject( name );
			}
			{
				AsciiString name( "Skirmish/tooltipPlayerLevelIconMordor" );
				g_theWindowManager->removeAptObject( name );
			}
		}
		TheBfmeSkirmishOptionsSlot = 0;
	}
}
