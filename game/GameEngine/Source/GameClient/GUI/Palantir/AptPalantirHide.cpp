class GameWindow
{
public:
	int winHide( bool hide );
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
// Retail calls both members through their ILT thunks (RVA 0x00047B6D and
// RVA 0x0001827D); naming the thunks keeps the references resolvable at link
// time and still encodes each call as retail's call rel32.
extern void j_00047b6d();
extern void j_0001827d();
// Retail 0x012F19E8 is the game-wide manager pointer EA defines as
// `WindowManager *g_rva012F19E8WindowManager` in
// game/GameEngine/Source/GameClient/GUI/WindowManager.cpp. This TU only null-tests
// it, so the forward declaration is all it needs.
class WindowManager;

extern WindowManager *g_rva012F19E8WindowManager;
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

static __forceinline void bfmeRegionClear( AptPalantirRegion *region )
{
	union
	{
		void (*raw)();
		void (AptPalantirRegion::*member)();
	} call;

	call.raw = j_00047b6d;
	(region->*call.member)();
}

static __forceinline void bfmeRadarHide( Radar *radar )
{
	union
	{
		void (*raw)();
		void (Radar::*member)();
	} call;

	call.raw = j_0001827d;
	(radar->*call.member)();
}

// ?hide@AptPalantir@@QAEX_N@Z
void AptPalantir::hide( bool immediate )
{
	if( !g_rva012F19E8WindowManager )
		return;

	if( immediate )
	{
		bfmeGo1071B( 0 );
		if( m_animation )
			m_animation->stop();
		bfmeRegionClear( &m_region );
		m_store.clear();
		if( TheRadar )
			bfmeRadarHide( TheRadar );
	}
	else
	{
		bfmeGo1085A();
	}

	m_window->winHide( immediate );
}
