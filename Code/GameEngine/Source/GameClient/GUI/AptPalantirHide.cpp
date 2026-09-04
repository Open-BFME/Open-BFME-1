class GameWindow
{
public:
	void winHide( bool hide );
};

class PalantirAnimation
{
public:
	virtual void unused0();
	virtual void unused1();
	virtual void unused2();
	virtual void unused3();
	virtual void stop();
};

class AptPalantirRegion
{
public:
	void clear();
};

class AptPalantirStore
{
public:
	void clear();
};

class Radar
{
public:
	void hide();
};

extern void bfmeGo1071B( char hidden );
extern void bfmeGo1085A();
extern void *g_theWindowManager;
extern Radar *TheRadar;

class AptPalantir
{
public:
	void hide( bool immediate );

private:
	unsigned char m_unmodelled00[ 0x0c ];
	GameWindow *m_window;
	PalantirAnimation *m_animation;
	unsigned char m_unmodelled14[ 0x54 ];
	AptPalantirRegion m_region;
	unsigned char m_unmodelled69[ 0xeb ];
	AptPalantirStore m_store;
};

// ?hide@AptPalantir@@QAEX_N@Z
void AptPalantir::hide( bool immediate )
{
	if( !g_theWindowManager )
		return;

	if( immediate )
	{
		bfmeGo1071B( 0 );
		if( m_animation )
			m_animation->stop();
		m_region.clear();
		m_store.clear();
		if( TheRadar )
			TheRadar->hide();
	}
	else
	{
		bfmeGo1085A();
	}

	m_window->winHide( immediate );
}
