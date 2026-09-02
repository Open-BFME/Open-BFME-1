// cl: /DNDEBUG /MD
// ZH LoadScreen.cpp:1877, with BFME's Bool argument on liteupdate.

#define BFME_VSLOT(n) virtual void slot##n();

class NetworkInterface
{
public:
	BFME_VSLOT(0) BFME_VSLOT(1) BFME_VSLOT(2) BFME_VSLOT(3)
	BFME_VSLOT(4) BFME_VSLOT(5) BFME_VSLOT(6) BFME_VSLOT(7)
	BFME_VSLOT(8)
	virtual void liteupdate( int mode );
	BFME_VSLOT(10) BFME_VSLOT(11) BFME_VSLOT(12) BFME_VSLOT(13)
	BFME_VSLOT(14) BFME_VSLOT(15) BFME_VSLOT(16) BFME_VSLOT(17)
	BFME_VSLOT(18) BFME_VSLOT(19) BFME_VSLOT(20) BFME_VSLOT(21)
	BFME_VSLOT(22) BFME_VSLOT(23) BFME_VSLOT(24) BFME_VSLOT(25)
	BFME_VSLOT(26) BFME_VSLOT(27)
	virtual void updateLoadProgress( int percent );
};

#undef BFME_VSLOT

extern NetworkInterface *TheNetwork;

class LoadScreen
{
public:
	virtual void update( int percent );
};

class GameSpyLoadScreen : public LoadScreen
{
public:
	virtual void update( int percent );
};

void GameSpyLoadScreen::update( int percent )
{
	if( percent <= 100 )
		TheNetwork->updateLoadProgress( percent );
	TheNetwork->liteupdate( 0 );
	LoadScreen::update( percent );
}
