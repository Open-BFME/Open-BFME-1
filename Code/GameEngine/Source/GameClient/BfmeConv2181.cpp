// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// BfmeAptScreenScoreScreen destructor, retail 0x00575050, 290 bytes.
// Resets its own vtable (0x0110AAB8) and the secondary base vtable at
// +0x218 (0x0110AAB4), unregisters the "AptScoreScreen::InitGadgets" apt
// gadget group through _bfme_closeAptScreen (same ILT 0x00036485 used by
// BfmeAptScreenLanLobbyDestructor.cpp), then -- unconditionally, no
// singleton-identity guard unlike the sibling dtors -- when this is a
// single-player screen (+0x25c == 0) and TheShell is set, hides the shell
// (Shell::hide, ILT 0x000428ED, pinned as ?hide@Shell@@QAEX_N@Z). It clears
// the TheScoreScreen global (0x012F4B50), destructs three BFMERetailAsciiString
// members (+0x330, +0x320, +0x300), inline-frees a raw pointer buffer member
// (+0x2e8/+0x2f8: start/end, node-alloc under 0x80 bytes else operator
// delete -- same shape as Q3VectorStorageRelease.cpp but the fields are
// 0x10 apart instead of 8), destructs the vector<Gen00574BC0> row member at
// +0x264 through the ILT thunk 0x00045E8F (real body already landed at
// 0x00574BC0 as Q4VectorDtorMemberOffset.cpp, but retail's call here goes
// through the incremental-link thunk, so the member destructor is pinned to
// the thunk address directly), then chains to the _bfme_AptGameWindow base
// destructor through ILT 0x000204C3 exactly like BfmeAptScreenLanLobbyDestructor.cpp.

class AsciiString
{
private:
	void *m_data;
};

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString( const char *text );
	~BFMERetailAsciiString() { releaseBuffer(); }
	void releaseBuffer();

private:
	void *m_data;
};

class _bfme_AptGameWindow
{
public:
	virtual ~_bfme_AptGameWindow();

private:
	char m_unmodelled[ 0x214 ];
};

class BfmeAptScreenScoreSecondary
{
public:
	virtual void slot00() = 0;

private:
	char m_unmodelled[ 0x40 ];
};

class Shell
{
public:
	void hide( bool doHide );
};

extern Shell *TheShell;

void _bfme_closeAptScreen( const AsciiString &name );

void Gen0082E5F0( void *p, unsigned int n );

struct ScoreRowVector
{
	~ScoreRowVector();
};

struct RawVecBuffer
{
	char *m_start;
	char m_unused[ 0xc ];
	char *m_end;

	~RawVecBuffer()
	{
		if( m_start != 0 )
		{
			int shifted = (int)( m_end - m_start ) >> 2;
			unsigned int n = (unsigned int)( shifted << 2 );
			if( n > 128 )
				::operator delete( m_start );
			else
				Gen0082E5F0( m_start, n );
		}
	}
};

class BfmeAptScreenScoreScreen;
#define TheScoreScreen (*(BfmeAptScreenScoreScreen **)0x012f4b50)

class BfmeAptScreenScoreScreen : public _bfme_AptGameWindow, public BfmeAptScreenScoreSecondary
{
public:
	virtual ~BfmeAptScreenScoreScreen();

private:
	int m_gameType;
	char m_pad260[ 0x264 - 0x260 ];
	ScoreRowVector m_rows;
	char m_pad265[ 0x2e8 - 0x265 ];
	RawVecBuffer m_rawBuffer;
	char m_pad2fc[ 0x300 - 0x2fc ];
	BFMERetailAsciiString m_s300;
	char m_pad304[ 0x320 - 0x304 ];
	BFMERetailAsciiString m_s320;
	char m_pad324[ 0x330 - 0x324 ];
	BFMERetailAsciiString m_s330;
};

BfmeAptScreenScoreScreen::~BfmeAptScreenScoreScreen()
{
	{
		BFMERetailAsciiString name( "AptScoreScreen::InitGadgets" );
		_bfme_closeAptScreen( reinterpret_cast<const AsciiString &>( name ) );
	}

	if( m_gameType == 0 )
	{
		if( TheShell )
			TheShell->hide( false );
	}

	TheScoreScreen = 0;
}
