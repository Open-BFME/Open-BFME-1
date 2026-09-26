// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// BfmeAptScreenOptions::_bfme_refreshNat, retail 0x00560030, 466 bytes. The
// already matched constructor at 0x00563370 binds thunk 0x00032768 to the
// selector string "AptOptions::RefreshNat", and that thunk jumps to this body.
// The logic is the Generals firewall detection from WOLWelcomeMenu.cpp run to
// completion in one call: init detects, the update loop spins on
// behaviorDetectionUpdate, and the result goes into the screen's own
// OptionPreferences map at this+0x264 under the two keys writeFirewallBehavior
// uses. Retail calls getFirewallBehavior twice rather than reading the global
// back, and it never writes m_firewallPortAllocationDelta.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	void *m_data;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}

	void format( AsciiString format, ... );
	void set( const AsciiString &other );

	AsciiString &operator=( const AsciiString &other )
	{
		set( other );
		return *this;
	}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UserPreferences.h
class PreferenceMap
{
public:
	AsciiString &operator[]( const AsciiString &key );
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/FirewallHelper.h
class FirewallHelperClass
{
public:
	enum tFirewallBehaviorType
	{
		FIREWALL_TYPE_UNKNOWN = 0
	};

	virtual ~FirewallHelperClass();

	void flagNeedToRefresh( bool refresh );
	bool detectFirewall( void );
	bool behaviorDetectionUpdate( void );
	tFirewallBehaviorType getFirewallBehavior( void );
	short getSourcePortAllocationDelta( void );
	void writeFirewallBehavior( void );
};

FirewallHelperClass *createFirewallHelper( void );

struct Rva006C9270GlobalData
{
	unsigned char m_head[ 0xb14 ];
	int m_firewallBehavior;								///< retail this+0xb14
};

extern FirewallHelperClass *TheFirewallHelper;
extern Rva006C9270GlobalData *TheWritableGlobalData;

// Options.apt screen, retail object 0x310 bytes. Only the OptionPreferences
// member matters here; its map base sits four bytes past the preferences
// vtable pointer.
class BfmeAptScreenOptions
{
public:
	void _bfme_refreshNat( const char *name );

private:
	unsigned char m_unmodelled_00[ 0x264 ];				///< retail this+0x00
	PreferenceMap m_prefs;								///< retail this+0x264
};

// ?_bfme_refreshNat@BfmeAptScreenOptions@@QAEXPBD@Z
void BfmeAptScreenOptions::_bfme_refreshNat( const char *name )
{
	(void)name;

	if ( TheFirewallHelper == 0 )
	{
		TheFirewallHelper = createFirewallHelper();
	}
	TheFirewallHelper->flagNeedToRefresh( true );
	if ( TheFirewallHelper->detectFirewall() == true )
	{
		delete TheFirewallHelper;
		TheFirewallHelper = 0;
	}

	if ( TheFirewallHelper != 0 )
	{
		while ( !TheFirewallHelper->behaviorDetectionUpdate() )
		{
		}

		TheWritableGlobalData->m_firewallBehavior = TheFirewallHelper->getFirewallBehavior();

		AsciiString numstr;
		numstr.format( AsciiString( "%d" ), TheFirewallHelper->getFirewallBehavior() );
		m_prefs[ AsciiString( "FirewallBehavior" ) ] = numstr;

		numstr.format( AsciiString( "%d" ), TheFirewallHelper->getSourcePortAllocationDelta() );
		m_prefs[ AsciiString( "FirewallPortAllocationDelta" ) ] = numstr;

		TheFirewallHelper->writeFirewallBehavior();
		TheFirewallHelper->flagNeedToRefresh( false );
		delete TheFirewallHelper;
		TheFirewallHelper = 0;
	}

	if ( TheFirewallHelper != 0 )
	{
		delete TheFirewallHelper;
		TheFirewallHelper = 0;
	}
}
