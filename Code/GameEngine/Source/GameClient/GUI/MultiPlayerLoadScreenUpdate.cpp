// cl: /DNDEBUG /MD
// readable body of ?update@MultiPlayerLoadScreen@@: Code/GameEngine/Source/GameClient/GUI/LoadScreen.cpp
// ZH LoadScreen.cpp:1508, with BFME's Bool argument on liteupdate.

#define BFME_VSLOT(n) virtual void slot##n();

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetworkInterface.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameInfo
{
public:
	BFME_VSLOT(0) BFME_VSLOT(1) BFME_VSLOT(2) BFME_VSLOT(3)
	BFME_VSLOT(4)
	virtual int getLocalSlotNum();
};

#undef BFME_VSLOT

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	void processProgress( int player, int percent );
};

extern NetworkInterface *TheNetwork;
extern GameInfo *TheGameInfo;
extern GameLogic *TheGameLogic;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/LoadScreen.h
class LoadScreen
{
public:
	virtual void update( int percent );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/LoadScreen.h
class MultiPlayerLoadScreen : public LoadScreen
{
public:
	virtual void update( int percent );
};

void MultiPlayerLoadScreen::update( int percent )
{
	if( TheNetwork ) {
		if( percent <= 100 )
			TheNetwork->updateLoadProgress( percent );
		TheNetwork->liteupdate( 0 );
	} else {
		if( percent <= 100 )
			TheGameLogic->processProgress( TheGameInfo->getLocalSlotNum(), percent );
	}
	LoadScreen::update( percent );
}
