// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// BfmeAptScreenOnlineHome destructor, retail 0x00545FF0, 293 bytes.
// Named by AptOnlineHome::InitGadgets / OnlineHome gadget string xrefs and
// vtable 0x01107B70 (installed by ctor 0x005484E0 / S4Guarded0055BAA0).

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
	unsigned char m_unmodelled[ 0x3C ];
};

class WindowManager
{
public:
	void _bfme_removeNamedAptGadget( const AsciiString &name );
	void removeAptObject( const AsciiString &name );
};

void _bfme_closeAptScreen( const AsciiString &name );

extern WindowManager *g_theWindowManager;
extern void *TheBfmeOnlineHomeSlot;
extern const char *g_onlineHomeGadgetsImage;
extern const char *g_onlineHomeGadgetsImageLevelIconMain;

class BfmeAptScreenOnlineHome : public BfmeAptGameWindow
{
public:
	virtual ~BfmeAptScreenOnlineHome();
};

BfmeAptScreenOnlineHome::~BfmeAptScreenOnlineHome()
{
	if( this == TheBfmeOnlineHomeSlot )
	{
		{
			AsciiString name( g_onlineHomeGadgetsImage );
			g_theWindowManager->_bfme_removeNamedAptGadget( name );
		}
		{
			AsciiString name( g_onlineHomeGadgetsImageLevelIconMain );
			g_theWindowManager->_bfme_removeNamedAptGadget( name );
		}
		{
			AsciiString name( "OnlineShell/OnlineHome/tooltipPlayerLevelIcon" );
			g_theWindowManager->removeAptObject( name );
		}
		{
			AsciiString name( "AptOnlineHome::InitGadgets" );
			_bfme_closeAptScreen( name );
		}
		TheBfmeOnlineHomeSlot = 0;
	}
}
