// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// BfmeAptScreenScoreScreen destructor, retail 0x00575050 (290 bytes).
// Unregisters AptScoreScreen::InitGadgets, hides the shell for the
// single-player screen, and clears TheScoreScreen. Members: pair-vector
// at +0x264, 4-byte buffer with eos at +0x2f8, AsciiStrings at
// +0x300/+0x320/+0x330, then the APT window base.

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

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
};

class _bfme_AptGameWindow
{
public:
	virtual ~_bfme_AptGameWindow();

private:
	char m_unmodelled[ 0x214 ];
};

class BfmeAptFunctorMarker
{
public:
	virtual void marker() = 0;
};

void _bfme_closeAptScreen( const AsciiString &name );

class Shell
{
public:
	void hide( bool immediate );
};

extern Shell *TheShell;

namespace _STL
{
template <class T, class U>
struct pair
{
	T first;
	U second;
};

template <class T>
class allocator
{
};

template <class T, class A>
class vector
{
public:
	~vector();
	char m_data[ 12 ];
};

template <bool Threads, int Instance>
class __node_alloc
{
public:
	static void _M_deallocate( void *p, unsigned int bytes );
};
}

class ScoreIntStorage
{
public:
	~ScoreIntStorage()
	{
		if ( m_begin )
		{
			unsigned int bytes = (unsigned int)( m_endOfStorage - m_begin )
				* sizeof( int );
			if ( bytes > 128 )
				::operator delete( m_begin );
			else
				_STL::__node_alloc<true, 0>::_M_deallocate( m_begin, bytes );
		}
	}

private:
	int *m_begin;
	int *m_finish;
	int m_pad[ 2 ];
	int *m_endOfStorage;
};

class __multiple_inheritance BfmeAptScreenScoreScreen
	: public _bfme_AptGameWindow, public BfmeAptFunctorMarker
{
public:
	virtual ~BfmeAptScreenScoreScreen();

private:
	char m_pad21c[ 0x40 ];
	int m_type;
	int m_pad260;
	_STL::vector<_STL::pair<int, AsciiString>,
		_STL::allocator<_STL::pair<int, AsciiString> > > m_pairs;
	char m_pad270[ 0x78 ];
	ScoreIntStorage m_ints;
	int m_pad2fc;
	AsciiString m_str300;
	char m_pad304[ 0x1C ];
	AsciiString m_str320;
	char m_pad324[ 0xC ];
	AsciiString m_str330;
};

extern BfmeAptScreenScoreScreen *TheScoreScreen;

BfmeAptScreenScoreScreen::~BfmeAptScreenScoreScreen()
{
	{
		AsciiString name( "AptScoreScreen::InitGadgets" );
		_bfme_closeAptScreen( name );
	}

	if ( m_type == 0 && TheShell )
		TheShell->hide( false );

	TheScoreScreen = 0;
}
