// cl: /DNDEBUG /MD
// Retail 0x0048D2D0 input-method window transition.

extern "C" {
	int __stdcall ImmSetOpenStatus( void *context, int open );
	void *__stdcall ImmAssociateContext( void *window, void *context );
}

extern void *Rva0048CD50WindowHandle;

class GameWindow
{
public:
	unsigned int winGetStatus();
};

class Rva0048D2D0Input
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void leaveWindow();
	virtual void slot11();
	virtual void enterWindow();
	void setWindow( GameWindow *window );

private:
	char m_pad04[8];
	GameWindow *m_window;
	void *m_context;
	char m_pad14[4];
	int m_associated;
};

void Rva0048D2D0Input::setWindow( GameWindow *window )
{
	if( m_window != window ) {
		leaveWindow();
		if( window && (window->winGetStatus() & 2) )
			enterWindow();
		if( !m_associated ) {
			ImmSetOpenStatus( m_context, 1 );
			ImmAssociateContext( Rva0048CD50WindowHandle, m_context );
		}
		m_window = window;
	}
}
