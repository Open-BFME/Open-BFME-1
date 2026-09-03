// cl: /DNDEBUG /MD
//
// Retail 0x004F0760: WOLGameSetupMenu.cpp PopBackToLobby.  ZH deletes TheNAT,
// resets the current staging room and leaves it, then if the GameSpy options
// parent is up stores nextScreen and tail-calls TheShell->pop.  BFME adds a
// second tail-call on a neighbouring global when that parent is gone.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NAT.h
class NAT
{
public:
	virtual ~NAT();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/StagingRoomGameInfo.h
class GameSpyStagingRoom
{
public:
	virtual void slot000();
	virtual void slot004();
	virtual void reset();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/PeerDefs.h
class GameSpyInfoInterface
{
public:
	virtual void slot000();
	virtual void slot004();
	virtual void slot008();
	virtual void slot00C();
	virtual void slot010();
	virtual void slot014();
	virtual void slot018();
	virtual void slot01C();
	virtual void slot020();
	virtual void slot024();
	virtual void slot028();
	virtual void slot02C();
	virtual void slot030();
	virtual void slot034();
	virtual void slot038();
	virtual void slot03C();
	virtual void slot040();
	virtual void slot044();
	virtual void slot048();
	virtual void slot04C();
	virtual void slot050();
	virtual void slot054();
	virtual void slot058();
	virtual void slot05C();
	virtual void slot060();
	virtual void slot064();
	virtual void slot068();
	virtual void slot06C();
	virtual void slot070();
	virtual void slot074();
	virtual void slot078();
	virtual void slot07C();
	virtual void slot080();
	virtual void slot084();
	virtual void slot088();
	virtual void slot08C();
	virtual void slot090();
	virtual void slot094();
	virtual void slot098();
	virtual void slot09C();
	virtual void slot0A0();
	virtual void slot0A4();
	virtual void slot0A8();
	virtual void slot0AC();
	virtual void leaveStagingRoom();
	virtual void slot0B4();
	virtual void slot0B8();
	virtual void slot0BC();
	virtual void slot0C0();
	virtual GameSpyStagingRoom *getCurrentStagingRoom();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Shell.h
class Shell
{
public:
	void pop();
};

class Rva00537C00
{
public:
	void set();
};

extern NAT *TheNAT;
extern GameSpyInfoInterface *TheGameSpyInfo;
extern Shell *TheShell;
extern void *parentWOLGameSetup;
extern Rva00537C00 *s_popBackExtra;

static char *nextScreen;

// ?PopBackToLobby@@YAXXZ
void PopBackToLobby(void)
{
	delete TheNAT;
	TheNAT = 0;

	if (TheGameSpyInfo)
	{
		TheGameSpyInfo->getCurrentStagingRoom()->reset();
		TheGameSpyInfo->leaveStagingRoom();
	}

	if (parentWOLGameSetup)
	{
		nextScreen = "Menus/WOLCustomLobby.wnd";
		TheShell->pop();
		return;
	}

	if (s_popBackExtra)
		s_popBackExtra->set();
}
