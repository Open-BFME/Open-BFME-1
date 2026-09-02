// cl: /O2 /Ob0

bool __cdecl rva00592D60Ask();
void __cdecl rva00592D60Notify();
extern void *g_rva00592D60NotifyOwner;

class Rva00592D60Panel
{
public:
	void hide( bool hidden );
};

class Rva00592D60Window
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void refresh();
	void send( int value, int message );
};

class Rva00592D60Owner
{
public:
	void update( int value, int state );

private:
	char                m_pad00[ 0x0C ];
	Rva00592D60Panel   *m_panel;
	Rva00592D60Window  *m_window;
	char                m_pad14[ 0x4F4 ];
	int                 m_state;
	bool                m_available;
};

void Rva00592D60Owner::update( int value, int state )
{
	m_available = !rva00592D60Ask();
	m_state = state;

	if( !rva00592D60Ask() && g_rva00592D60NotifyOwner )
	{
		rva00592D60Notify();
		m_panel->hide( false );
	}

	m_window->refresh();
	m_window->send( value, 0x40 );
}
