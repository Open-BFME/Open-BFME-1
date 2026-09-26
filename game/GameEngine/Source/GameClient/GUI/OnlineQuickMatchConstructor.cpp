// ??0BfmeAptScreenOnlineQuickMatch@@QAE@H@Z
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// BfmeAptScreenOnlineQuickMatch constructor, retail 0x00559400, 755 bytes.
// The vtable, callback selector strings, and guarded 124-byte factory identify
// the class.  The constructor loads the two custom-match images and registers
// the seven OnlineQuickMatch callbacks only for the first instance.

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString( const char *text );
	~BFMERetailAsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();
	void *m_data;
};

class AsciiString
{
	void *m_data;
};

class BfmeAptWindowContext
{
public:
	BfmeAptWindowContext( int context )
		: m_context( context ), m_z38( 0 ) {}

private:
	int m_context;
	int m_z38;
};

class __single_inheritance FunctorTargetSingle
{
};

typedef void (FunctorTargetSingle::*FunctorMethodSingle)( void );

struct FunctorBindingSingle
{
	FunctorBindingSingle( FunctorMethodSingle method,
		FunctorTargetSingle *target )
		: m_target( target ), m_method( method ) {}

	FunctorTargetSingle *m_target;
	FunctorMethodSingle m_method;
};

class Rva0050F8B0FunctorHolder
{
public:
	Rva0050F8B0FunctorHolder( FunctorBindingSingle binding );
	Rva0050F8B0FunctorHolder( const Rva0050F8B0FunctorHolder &other );

private:
	void *m_ptr;
};

class Rva0050F840FunctorHolder
{
public:
	Rva0050F840FunctorHolder( FunctorBindingSingle binding );
	Rva0050F840FunctorHolder( const Rva0050F840FunctorHolder &other );

private:
	void *m_ptr;
};

class _bfme_AptGameWindow
{
public:
	_bfme_AptGameWindow( int context )
		: m_z04( 0 ), m_z08( 0 ), m_z0C( 0 ), m_z10( 0 ), m_z14( 0 ),
		m_z18( 0 ), m_z1C( 0 ), m_z20( 0 ), m_z24( 0 ), m_z28( 0 ),
		m_z2C( 0 ), m_z30( 0 ), m_context( context ) {}

	virtual ~_bfme_AptGameWindow();

	void _bfme_showAptScreenOnlineQuickMatch( const AsciiString &name,
		Rva0050F8B0FunctorHolder callback );

private:
	volatile int m_z04;
	int m_z08;
	int m_z0C;
	int m_z10;
	int m_z14;
	int m_z18;
	int m_z1C;
	int m_z20;
	int m_z24;
	int m_z28;
	int m_z2C;
	int m_z30;
	BfmeAptWindowContext m_context;
};

class Rva0002E802QuickMatchPreferences
{
public:
	Rva0002E802QuickMatchPreferences();
	virtual ~Rva0002E802QuickMatchPreferences();

private:
	unsigned char m_unmodelled[ 0x10 ];
};

class Gen_004b5a50
{
public:
	Gen_004b5a50( int value );
	~Gen_004b5a50();

	int m_5C;
	int m_60;
	int m_64;
	int m_68;
	int m_6C;
};

class QuickMatchFlags
{
public:
	QuickMatchFlags()
		: m_ready( 0 ), m_startRequested( 0 ), m_pad56( 0 ), m_flags( 0 ) {}

	unsigned char m_ready;
	unsigned char m_startRequested;
	unsigned char m_pad56;
	int m_flags;
};

class Image;
class Rva0001D606ImageCollection
{
public:
	const Image *findImageByName( const AsciiString &name );
};

class Rva00018F0CMapCache
{
public:
	void updateCache();
};

class GameSpyStagingRoom
{
public:
	virtual void slot00( int deleting );
	virtual void slot04();
	virtual void slot08();
};

class GameSpyInfo
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0C(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1C(); virtual void slot20();
	virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38();
	virtual void slot3C(); virtual void slot40(); virtual void slot44();
	virtual void slot48(); virtual void slot4C(); virtual void slot50();
	virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void slot60(); virtual void slot64(); virtual void slot68();
	virtual void slot6C(); virtual void slot70(); virtual void slot74();
	virtual void slot78(); virtual void slot7C(); virtual void slot80();
	virtual void slot84(); virtual void slot88(); virtual void slot8C();
	virtual void slot90(); virtual void slot94(); virtual void slot98();
	virtual void slot9C(); virtual void slotA0(); virtual void slotA4();
	virtual void slotA8(); virtual void slotAC(); virtual void slotB0();
};

class BfmeAptScreenOnlineQuickMatch : public _bfme_AptGameWindow
{
public:
	BfmeAptScreenOnlineQuickMatch( int context );
	virtual ~BfmeAptScreenOnlineQuickMatch();

private:
	int m_z3C;
	Rva0002E802QuickMatchPreferences m_preferences;
	QuickMatchFlags m_flags;
	Gen_004b5a50 m_slot5C;
	int m_slot70;
	int m_slot74;
	int m_slot78;
};

#pragma comment(linker, "/alternatename:??0Rva0002E802QuickMatchPreferences@@QAE@XZ=?j_0002e802@@YAXXZ")
#pragma comment(linker, "/alternatename:??0Gen_004b5a50@@QAE@H@Z=?j_0001fdcf@@YAXXZ")
#pragma comment(linker, "/alternatename:??1Gen_004b5a50@@QAE@XZ=?j_0003eb53@@YAXXZ")
#pragma comment(linker, "/alternatename:??0Rva0050F8B0FunctorHolder@@QAE@UFunctorBindingSingle@@@Z=?j_00013665@@YAXXZ")
#pragma comment(linker, "/alternatename:??0Rva0050F840FunctorHolder@@QAE@UFunctorBindingSingle@@@Z=?j_000367ff@@YAXXZ")
#pragma comment(linker, "/alternatename:?_bfme_showAptScreenOnlineQuickMatch@_bfme_AptGameWindow@@QAEXABVAsciiString@@VRva0050F8B0FunctorHolder@@@Z=?j_000338ed@@YAXXZ")
#pragma comment(linker, "/alternatename:?_bfme_setAptScreenRefOnlineQuickMatch@@YAXABVAsciiString@@VRva0050F840FunctorHolder@@@Z=?j_0003df14@@YAXXZ")
#pragma comment(linker, "/alternatename:?findImageByName@Rva0001D606ImageCollection@@QAEPBVImage@@ABVAsciiString@@@Z=?j_0001d606@@YAXXZ")
#pragma comment(linker, "/alternatename:?updateCache@Rva00018F0CMapCache@@QAEXXZ=?j_00018f0c@@YAXXZ")

#define TheBfmeOnlineQuickMatch (*(BfmeAptScreenOnlineQuickMatch **)0x012F4ABC)
#define TheMappedImageCollection (*(Rva0001D606ImageCollection **)0x012F6924)
#define TheMapCache (*(Rva00018F0CMapCache **)0x012F1594)
#define TheGameSpyGame (*(GameSpyStagingRoom **)0x012F7198)
#define TheGameSpyStagingRoom (*(GameSpyStagingRoom **)0x012F770C)
#define TheGameSpyInfo (*(GameSpyInfo **)0x012F7194)
#define TheWindowManager (*(void **)0x012F19E8)


void _bfme_setAptScreenRefOnlineQuickMatch( const AsciiString &name,
	Rva0050F840FunctorHolder callback );

BfmeAptScreenOnlineQuickMatch::BfmeAptScreenOnlineQuickMatch( int context )
	: _bfme_AptGameWindow( context ), m_z3C( 0 ), m_preferences(), m_flags(),
	  m_slot5C( 0 )
{
	m_slot5C.m_60 = 0;
	m_slot5C.m_64 = 0;
	m_slot5C.m_68 = 0;
	m_slot5C.m_6C = 0;
	m_slot70 = 0;
	m_slot74 = 0;
	m_slot78 = 0;
	if( TheWindowManager != 0 && TheBfmeOnlineQuickMatch == 0 )
	{
		TheBfmeOnlineQuickMatch = this;

		{
			BFMERetailAsciiString name( "AptCustomMatchSelected" );
			m_slot70 = (int)TheMappedImageCollection->findImageByName(
				reinterpret_cast<const AsciiString &>( name ) );
		}
		{
			BFMERetailAsciiString name( "AptCustomMatchUnselected" );
			m_slot74 = (int)TheMappedImageCollection->findImageByName(
				reinterpret_cast<const AsciiString &>( name ) );
		}
		{
			union
			{
				void (*raw)( void );
				FunctorMethodSingle member;
			} callback;
			callback.raw = (void (*)( void ))0x00436C64;
			BFMERetailAsciiString name( "AptOnline::OnlineQuickMatch::PlayGame" );
			_bfme_showAptScreenOnlineQuickMatch(
				reinterpret_cast<const AsciiString &>( name ),
				Rva0050F8B0FunctorHolder(
					FunctorBindingSingle( callback.member,
						(FunctorTargetSingle *)this ) ) );
		}
		{
			union
			{
				void (*raw)( void );
				FunctorMethodSingle member;
			} callback;
			callback.raw = (void (*)( void ))0x00411E14;
			BFMERetailAsciiString name( "AptOnline::OnlineQuickMatch::Cancel" );
			_bfme_showAptScreenOnlineQuickMatch(
				reinterpret_cast<const AsciiString &>( name ),
				Rva0050F8B0FunctorHolder(
					FunctorBindingSingle( callback.member,
						(FunctorTargetSingle *)this ) ) );
		}
		{
			union
			{
				void (*raw)( void );
				FunctorMethodSingle member;
			} callback;
			callback.raw = (void (*)( void ))0x0043730D;
			BFMERetailAsciiString name( "AptOnline::OnlineQuickMatch::WidenSearch" );
			_bfme_showAptScreenOnlineQuickMatch(
				reinterpret_cast<const AsciiString &>( name ),
				Rva0050F8B0FunctorHolder(
					FunctorBindingSingle( callback.member,
						(FunctorTargetSingle *)this ) ) );
		}
		{
			union
			{
				void (*raw)( void );
				FunctorMethodSingle member;
			} callback;
			callback.raw = (void (*)( void ))0x00423015;
			BFMERetailAsciiString name( "AptOnline::OnlineQuickMatch::StartSimple" );
			_bfme_showAptScreenOnlineQuickMatch(
				reinterpret_cast<const AsciiString &>( name ),
				Rva0050F8B0FunctorHolder(
					FunctorBindingSingle( callback.member,
						(FunctorTargetSingle *)this ) ) );
		}
		{
			union
			{
				void (*raw)( void );
				FunctorMethodSingle member;
			} callback;
			callback.raw = (void (*)( void ))0x0042F5E0;
			BFMERetailAsciiString name( "AptOnline::OnlineQuickMatch::OnFoundMovieDone" );
			_bfme_showAptScreenOnlineQuickMatch(
				reinterpret_cast<const AsciiString &>( name ),
				Rva0050F8B0FunctorHolder(
					FunctorBindingSingle( callback.member,
						(FunctorTargetSingle *)this ) ) );
		}
		{
			union
			{
				void (*raw)( void );
				FunctorMethodSingle member;
			} callback;
			callback.raw = (void (*)( void ))0x004178DC;
			BFMERetailAsciiString name( "AptOnlineQuickMatch::InitGadgets" );
			_bfme_setAptScreenRefOnlineQuickMatch(
				reinterpret_cast<const AsciiString &>( name ),
				Rva0050F840FunctorHolder(
					FunctorBindingSingle( callback.member,
						(FunctorTargetSingle *)this ) ) );
		}

		TheMapCache->updateCache();
		TheGameSpyGame->slot08();
		if( GameSpyStagingRoom *room = TheGameSpyStagingRoom )
		{
			room->slot00( 1 );
			TheGameSpyStagingRoom = 0;
		}
		if( GameSpyInfo *info = TheGameSpyInfo )
			info->slotB0();
	}
}
