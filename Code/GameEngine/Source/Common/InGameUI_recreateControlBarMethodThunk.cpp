// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: clean C++ conversion of InGameUI::recreateControlBar.

typedef int Int;
typedef unsigned int UnsignedInt;

// Retail's AsciiString is a one-pointer StringBase<char> view.  Keeping the
// constructors and release operation out of line leaves the calls at the
// already matched retail string bodies (0x00888BC0 and 0x00887940).
template <typename T> class StringBase
{
private:
	StringBase( const T *text );
	StringBase( const StringBase<T> &that );
	void releaseBuffer();
	friend class AsciiString;
};

class AsciiString
{
public:
	AsciiString( const char *text )
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase( text );
	}

	AsciiString( const AsciiString &that )
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&that );
	}

	~AsciiString()
	{
		((StringBase<char> *)this)->releaseBuffer();
	}

	const char *str() const
	{
		return m_text ? m_text + 8 : (const char *)0x0107388B;
	}

private:
	char *m_text;
};

class GameWindow
{
public:
	virtual void deleteInstance( UnsignedInt flags );
};

class WindowLayoutInfo;

class GameWindowManager
{
public:
	virtual void slot000(); virtual void slot004(); virtual void slot008();
	virtual void slot00C(); virtual void slot010(); virtual void slot014();
	virtual void slot018(); virtual void slot01C(); virtual void slot020();
	virtual void slot024(); virtual void slot028(); virtual void slot02C();
	virtual void slot030(); virtual void slot034(); virtual void slot038();
	virtual void slot03C(); virtual void slot040(); virtual void slot044();
	virtual void slot048(); virtual void slot04C(); virtual void slot050();
	virtual void slot054(); virtual void slot058(); virtual void slot05C();
	virtual void slot060(); virtual void slot064();
	virtual GameWindow *winCreateFromScript( AsciiString file,
		WindowLayoutInfo *info, void *extra );
	virtual void slot06C(); virtual void slot070(); virtual void slot074();
	virtual void slot078(); virtual void slot07C(); virtual void slot080();
	virtual void slot084(); virtual void slot088(); virtual void slot08C();
	virtual void slot090(); virtual void slot094(); virtual void slot098();
	virtual void slot09C(); virtual void slot0A0(); virtual void slot0A4();
	virtual void slot0A8(); virtual void slot0AC();
	virtual void slot0B0(); virtual void slot0B4(); virtual void slot0B8();
	virtual void slot0BC(); virtual void slot0C0(); virtual void slot0C4();
	virtual void slot0C8(); virtual void slot0CC(); virtual void slot0D0();
	virtual void slot0D4(); virtual void slot0D8();
	virtual GameWindow *winGetWindowFromId( GameWindow *window, Int id );
};

class NameKeyGenerator
{
public:
	Int nameToKey( const char *name );
};

class ControlBar
{
public:
	ControlBar();
	virtual ~ControlBar();
	virtual void init();

private:
	char m_unreconstructed[0x2F4];
};

extern GameWindowManager *TheWindowManager;
extern NameKeyGenerator *TheNameKeyGenerator;
extern ControlBar *TheControlBar;

void HideControlBar( bool immediate );

class InGameUI
{
public:
	virtual void recreateControlBar();

	void createControlBar()
	{
		TheWindowManager->winCreateFromScript(
			AsciiString( "ControlBar.wnd" ), 0, 0 );
		HideControlBar( true );
	}

private:
	char m_unreconstructed[0x1398];
	GameWindow *m_idleWorkerWin;
};

// ?recreateControlBar@InGameUI@@UAEXXZ
void InGameUI::recreateControlBar()
{
	GameWindow *window = TheWindowManager->winGetWindowFromId(
		0, TheNameKeyGenerator->nameToKey(
			AsciiString( "ControlBar.wnd" ).str() ) );
	if (window)
		window->deleteInstance( 1 );

	m_idleWorkerWin = 0;
	createControlBar();

	if (TheControlBar)
	{
		delete TheControlBar;
		TheControlBar = new ControlBar;
		TheControlBar->init();
	}
}
