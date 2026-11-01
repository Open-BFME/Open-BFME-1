// ?update@BannerUI@@UAEXXZ
// Retail: 679 bytes at 0x00583680, through RET at +0x2A6.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib

// FILE: BannerUIUpdate.cpp ///////////////////////////////////////////////////
//
// BannerUI::update. Identity: BannerUI's vtable 0x0110B828 sends slot 5,
// SubsystemInterface::update, through ILT 0x00036E80 to this body.
//
// Shape from the Open BFME 2 donor BannerUI::update (Code/GameEngine/Source/
// GameClient/GUI/InGame/Tactical/BannerUI.cpp, donor revision 45afcff3; byte
// matched there at game.dat 0x002167A3). BFME 1's body is the earlier form:
// a banner marked for deletion only reports state 2 (no erase loop), the
// window text setter takes no third argument, and the summary message goes
// to the control bar directly. Fields, callees and literals below are read
// from the BFME 1 retail body:
//   banner entries (28 bytes) at +0x30/+0x34, the hidden flag at +0x3C and the
//   pending summary index at +0x40; entry +0x00 delete flag, +0x04 slot,
//   +0x08 banner object id, +0x10 state, +0x14 progress, +0x18 timer.
//   "APT:BannerTimer%d", L":", L"%d%s%02d" and "BANNERUI:SummaryTitle".
// The game-logic queries, the Apt helpers, the slot-0 handler (0x00583190),
// the text setter and the 12-byte message object (ctor 0x003BD700, inline
// destructor = 0x003BD770's body) keep the names the ledger already carries.
//
///////////////////////////////////////////////////////////////////////////////

#include "ascii_string.h"
#include "unicode_string.h"

inline UnicodeString::UnicodeString() { m_text = 0; }
inline UnicodeString::UnicodeString( const wchar_t *text )
{
	((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(
		(const unsigned short *)text );
}
inline UnicodeString::~UnicodeString()
{
	((StringBase<unsigned short> *)this)->releaseBuffer();
}

// One banner as the movie-entry vector stores it (28 bytes).
struct BannerMovieEntry
{
	bool m_pendingDelete;
	int m_id;
	int m_bannerID;
	int m_unmodelled_0C;
	int m_state;
	int m_progress;
	int m_timer;
};

class BannerMovieEntryVector
{
public:
	typedef BannerMovieEntry *iterator;
	iterator begin() { return m_start; }
	iterator end() { return m_finish; }
	unsigned int size() const { return m_finish - m_start; }

private:
	BannerMovieEntry *m_start;
	BannerMovieEntry *m_finish;
	BannerMovieEntry *m_capacity;
};

class BannerUI
{
public:
	virtual ~BannerUI();
	virtual void init();
	virtual void reset();
	virtual void update();

private:
	unsigned char m_unmodelled_04[ 0x30 - 0x04 ];
	BannerMovieEntryVector m_movieEntries;
	bool m_hidden;
	int m_currentLocation;
};

// The game-logic queries, each an 11-byte forwarder on TheGameLogic.
class Rva003838C0
{
public:
	int getState( int id ) const;
};

class Rva003838F0
{
public:
	float valueAt( int id );
};

class Rva00383910
{
public:
	int getRemainingFrames( int id ) const;
};

class GameLogic;
extern GameLogic *TheGameLogic;

void SetBannerState( int id, unsigned int state );
void SetBannerProgress( int id, int progress );

// 0x00583190, reached with this BannerUI in ECX and the banner slot.
class BfmeGlobDXI
{
public:
	void bfmeUseDXI( int slot );
};

class GlobalLanguage
{
public:
	unsigned char m_unmodelled_00[ 0x10 ];
	AsciiString m_at10;
};

extern GlobalLanguage *TheGlobalLanguageData;

class WindowManager
{
public:
	void bfme_setAptText( const AsciiString &name, const UnicodeString &text );
};

extern WindowManager *g_rva012F19E8WindowManager;

class GameTextInterface
{
public:
	virtual void vfn00();
	virtual void vfn01();
	virtual void vfn02();
	virtual void vfn03();
	virtual void vfn04();
	virtual void vfn05();
	virtual void vfn06();
	virtual void vfn07();
	virtual void vfn08();
	// ZH declaration order; VC7.1 gives overloaded virtuals their slots in
	// reverse, so the const char * overload this body calls is slot 10.
	virtual UnicodeString fetch( const char *label, bool *exists = 0 );
	virtual UnicodeString fetch( AsciiString label, bool *exists = 0 );
};

extern GameTextInterface *TheGameText;

// The polymorphic head of the message object; its inline virtual destructor
// leaves the vftable store retail shows at the end of the message's lifetime.
class Inner010EDAA0
{
public:
	virtual ~Inner010EDAA0() {}
};

class Rva003BD700String;

// vptr head, wide string at +4, banner object id at +8 (sizeof 12).
class Rva003BD700
{
public:
	Rva003BD700( const Rva003BD700String &text, int id );

private:
	Inner010EDAA0 m_head;
	UnicodeString m_text;
	int m_id;
};

struct BfmeMsgDN;

class ControlBar
{
public:
	void bfmeShowDN( BfmeMsgDN *msg );
};

extern ControlBar *TheControlBar;

void BannerUI::update()
{
	if( m_hidden )
		return;

	for( BannerMovieEntry *banner = m_movieEntries.begin(); banner != m_movieEntries.end(); ++banner )
	{
		int state;
		if( banner->m_pendingDelete )
			state = 2;
		else
		{
			switch( ((const Rva003838C0 *)TheGameLogic)->getState( banner->m_bannerID ) )
			{
				case 0: state = 0; break;
				case 2: state = 1; break;
				case 3: state = 2; break;
				default: state = 3; break;
			}
		}

		if( state != banner->m_state )
		{
			SetBannerState( banner->m_id, state );
			banner->m_state = state;
		}

		if( banner->m_state == 0 )
			((BfmeGlobDXI *)this)->bfmeUseDXI( banner->m_id );

		int progress;
		int timer;
		if( banner->m_state == 1 )
		{
			progress = (int)( ((Rva003838F0 *)TheGameLogic)->valueAt( banner->m_bannerID ) * 100.0f );
			timer = ((const Rva00383910 *)TheGameLogic)->getRemainingFrames( banner->m_bannerID ) / 5;
		}
		else
		{
			progress = 0;
			timer = -1;
		}

		if( progress != banner->m_progress )
		{
			SetBannerProgress( banner->m_id, progress );
			banner->m_progress = progress;
		}

		if( timer != banner->m_timer )
		{
			AsciiString windowName;
			windowName.format( "APT:BannerTimer%d", banner->m_id );
			UnicodeString text;
			if( timer >= 0 )
			{
				int minutes = timer / 60;
				int seconds = timer % 60;
				UnicodeString separator( L":" );
				if( TheGlobalLanguageData )
					separator.translate( TheGlobalLanguageData->m_at10 );
				text.format( L"%d%s%02d", minutes, separator.str(), seconds );
			}
			g_rva012F19E8WindowManager->bfme_setAptText( windowName, text );
			banner->m_timer = timer;
		}
	}

	if( (unsigned int)m_currentLocation < m_movieEntries.size() )
	{
		TheControlBar->bfmeShowDN( (BfmeMsgDN *)&static_cast<const Rva003BD700 &>( Rva003BD700(
			*(const Rva003BD700String *)&static_cast<const UnicodeString &>(
				TheGameText->fetch( "BANNERUI:SummaryTitle", 0 ) ),
			m_movieEntries.begin()[ m_currentLocation ].m_bannerID ) ) );
		m_currentLocation = -1;
	}
}
