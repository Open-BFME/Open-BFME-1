// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME1: isolated port of WOLLobbyMenu.cpp's static refreshGameList() for
// retail 0x004F9620. The shared WOLLobbyMenu.cpp TU already reproduces every
// byte of this function except one immediate: it resolves TheGameSpyInfo against
// the vanilla Zero Hour GameSpyInfoInterface (37 virtuals ahead of
// hasStagingRoomListChanged), while retail's vtable call displacement (0xac)
// proves BFME's interface carries seven extra virtuals ahead of that slot (see
// inputs/reference/shims/peerdefs/GameNetwork/GameSpy/PeerDefs.h). Rather than touch
// the shared, already-matched WOLLobbyMenu.cpp include path, this TU replicates
// just the pieces refreshGameList needs with a local stand-in interface whose
// vtable layout puts hasStagingRoomListChanged at the correct slot (43).

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);

extern void RefreshGameListBoxes(void);

// Stand-in for GameSpyInfoInterface: only the slot COUNT ahead of
// hasStagingRoomListChanged matters for codegen, not the real signatures.
class GameSpyInfoInterfaceStub
{
public:
	virtual void _pad00();
	virtual void _pad01();
	virtual void _pad02();
	virtual void _pad03();
	virtual void _pad04();
	virtual void _pad05();
	virtual void _pad06();
	virtual void _pad07();
	virtual void _pad08();
	virtual void _pad09();
	virtual void _pad10();
	virtual void _pad11();
	virtual void _pad12();
	virtual void _pad13();
	virtual void _pad14();
	virtual void _pad15();
	virtual void _pad16();
	virtual void _pad17();
	virtual void _pad18();
	virtual void _pad19();
	virtual void _pad20();
	virtual void _pad21();
	virtual void _pad22();
	virtual void _pad23();
	virtual void _pad24();
	virtual void _pad25();
	virtual void _pad26();
	virtual void _pad27();
	virtual void _pad28();
	virtual void _pad29();
	virtual void _pad30();
	virtual void _pad31();
	virtual void _pad32();
	virtual void _pad33();
	virtual void _pad34();
	virtual void _pad35();
	virtual void _pad36();
	virtual void _pad37();
	virtual void _pad38();
	virtual void _pad39();
	virtual void _pad40();
	virtual void _pad41();
	virtual void _pad42();
	virtual bool hasStagingRoomListChanged(void);
};

static GameSpyInfoInterfaceStub *TheGameSpyInfo = 0;

static unsigned long gameListRefreshTime = 0;
static const unsigned long gameListRefreshInterval = 10000;

static void refreshGameList( bool forceRefresh = false );

//-------------------------------------------------------------------------------------------------
/** refreshGameList
		The Bool is used to force refresh if the refresh button was hit.*/
//-------------------------------------------------------------------------------------------------
static void refreshGameList( bool forceRefresh )
{
	unsigned long refreshInterval = gameListRefreshInterval;

	if (forceRefresh || ((gameListRefreshTime == 0) || ((gameListRefreshTime + refreshInterval) <= timeGetTime())))
	{
		if (TheGameSpyInfo->hasStagingRoomListChanged())
		{
			RefreshGameListBoxes();
			gameListRefreshTime = timeGetTime();
		}
	}
}

// Synthetic call sites mirroring retail's two call shapes (forced and
// unforced), so the optimizer sees refreshGameList used exactly as it is in
// the real WOLLobbyMenu.cpp and keeps it around with the same internal
// calling convention.
void WOLLobbyMenuRefreshGameListThunk_CallSiteForced()
{
	refreshGameList(true);
}

void WOLLobbyMenuRefreshGameListThunk_CallSiteDefault()
{
	refreshGameList();
}
