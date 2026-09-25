// Open-BFME: vtable slot 0 of the class whose vftable is 0x010F74E8
// (??_7Rva00470360@@6B@, installed by the landed destructor at 0x00470360,
// Rva00470360Destructor.cpp), reached only through ILT thunk 0x000446BB.
// The window held at +0x24 is proven a GameWindow by the three ILT calls
// retail makes on it: 0x000482AC -> GameWindow::winSetSize (0x00478250),
// 0x00027F2A -> GameWindow::winHide (0x00478390), 0x0004A1FB ->
// GameWindow::winEnable (0x004782E0). The body reads the Apt movie size
// (Rva00892A00Query), scales it by the float pair the manager global at
// 0x012F19E8 returns from its slot +0x28, resizes and shows the window, and
// registers it with TheWindowManager (slot +0xB0) and the APT window table
// the first time only (flag +0x28). Class and method names not recovered.

class GameWindow
{
public:
	virtual void vslot00();
	virtual void vslot04();
	virtual void vslot08();
	virtual void vslot0c();
	virtual void vslot10();
	virtual void vslot14();
	virtual void vslot18();
	virtual void vslot1c();
	virtual void vslot20();
	virtual void vslot24();
	virtual void vslot28();
	virtual bool vslot2c();
	virtual void vslot30();

	int winSetSize( int width, int height );
	int winHide( bool hide );
	int winEnable( bool enable );

	unsigned char m_pad[ 0x250 - 4 ];
	int m_aptIndex;
};

class GameWindowManager
{
public:
	virtual void vslot00();
	virtual void vslot04();
	virtual void vslot08();
	virtual void vslot0c();
	virtual void vslot10();
	virtual void vslot14();
	virtual void vslot18();
	virtual void vslot1c();
	virtual void vslot20();
	virtual void vslot24();
	virtual void vslot28();
	virtual void vslot2c();
	virtual void vslot30();
	virtual void vslot34();
	virtual void vslot38();
	virtual void vslot3c();
	virtual void vslot40();
	virtual void vslot44();
	virtual void vslot48();
	virtual void vslot4c();
	virtual void vslot50();
	virtual void vslot54();
	virtual void vslot58();
	virtual void vslot5c();
	virtual void vslot60();
	virtual void vslot64();
	virtual void vslot68();
	virtual void vslot6c();
	virtual void vslot70();
	virtual void vslot74();
	virtual void vslot78();
	virtual void vslot7c();
	virtual void vslot80();
	virtual void vslot84();
	virtual void vslot88();
	virtual void vslot8c();
	virtual void vslot90();
	virtual void vslot94();
	virtual void vslot98();
	virtual void vslot9c();
	virtual void vslota0();
	virtual void vslota4();
	virtual void vslota8();
	virtual void vslotac();
	virtual void vslotb0( GameWindow *window );
};

extern GameWindowManager *TheWindowManager;

class WindowManager
{
public:
	virtual void vslot00();
	virtual void vslot04();
	virtual void vslot08();
	virtual void vslot0c();
	virtual void vslot10();
	virtual void vslot14();
	virtual void vslot18();
	virtual void vslot1c();
	virtual void vslot20();
	virtual void vslot24();
	virtual float *vslot28();

	bool showAptWindow( int index );
	void unidentified_0002e9a1( int a );
};

extern WindowManager *g_theWindowManager;

void __cdecl Rva00892A00Query( void **firstResult, void **secondResult );

class Rva00470360
{
public:
	virtual void fitWindow004703F0( int unused );
	virtual void vslot04();
	virtual void vslot08();
	virtual void vslot0c();
	virtual void vslot10( int a );
	virtual void vslot14();

private:
	unsigned char m_pad[ 0x24 - 4 ];
	GameWindow *m_window;
	bool m_registered;
};

// ?fitWindow004703F0@Rva00470360@@UAEXH@Z
void Rva00470360::fitWindow004703F0( int )
{
	if ( m_window && m_window->vslot2c() )
	{
		vslot10( 0 );
		int width;
		int height;
		Rva00892A00Query( (void **)&width, (void **)&height );
		float *scale = g_theWindowManager->vslot28();
		width = (int)( width * scale[ 0 ] );
		height = (int)( height * scale[ 1 ] );
		m_window->winSetSize( width, height );
		m_window->winHide( false );
		m_window->winEnable( true );
		vslot14();
		if ( !m_registered )
		{
			TheWindowManager->vslotb0( m_window );
			g_theWindowManager->showAptWindow( m_window->m_aptIndex );
			g_theWindowManager->unidentified_0002e9a1( m_window->m_aptIndex );
			m_registered = true;
		}
		m_window->vslot30();
	}
}
