// cl: /DNDEBUG /MD
// Retail 0x0048CD50 input-method teardown and window notification.

extern "C" {
	int __stdcall ImmNotifyIME( void *context,
		unsigned int action, unsigned int index, unsigned int value );
	int __stdcall ImmSetOpenStatus( void *context,
		int open );
	void *__stdcall ImmAssociateContext( void *window,
		void *context );
}

extern void *Rva0048CD50WindowHandle;

class GameWindow
{
public:
	unsigned int winGetStatus();
};

class Rva0048CD50Input
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
	virtual void slot10();
	virtual void notifyWindow();
	void deactivate();

private:
	char m_pad04[8];
	GameWindow *m_window;
	void *m_context;
	char m_pad14[8];
	unsigned char m_active;
};

void Rva0048CD50Input::deactivate()
{
	if( m_context ) {
		ImmNotifyIME( m_context, 0x15, 4, 0 );
		ImmSetOpenStatus( m_context, 0 );
	}
	ImmAssociateContext( Rva0048CD50WindowHandle, 0 );
	m_active = 0;
	if( m_window && (m_window->winGetStatus() & 2) )
		notifyWindow();
	m_window = 0;
}
