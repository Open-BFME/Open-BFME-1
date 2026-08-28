// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/languagefilter /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it

#include "PreRTS.h"

#include "Common/GameEngine.h"
#include "Common/MessageStream.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/RandomValue.h"
#include "GameClient/Shell.h"
#include "GameClient/MessageBox.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/ScriptActions.h"
#include "GameLogic/ScriptEngine.h"
#include "GameNetwork/NetworkInterface.h"
#include "GameNetwork/Transport.h"
#include "GameNetwork/Udp.h"

class Network : public NetworkInterface
{
public:
	Network();
	~Network();

	virtual void init(void);
	virtual void reset(void);
	virtual void update(void);
	virtual void liteupdate(void);
	Bool deinit(void);

	virtual void setLocalAddress(UnsignedInt ip, UnsignedInt port);
	virtual UnsignedInt getRunAhead(void);		// body needs an offset this TU has not recovered
	virtual UnsignedInt getFrameRate(void);		// likewise
	virtual UnsignedInt getPacketArrivalCushion(void);
	virtual Bool isFrameDataReady(void);
	virtual void parseUserList(const GameInfo *game);
	virtual void startGame(void);

	virtual void sendChat(UnicodeString text, Int playerMask);
	virtual void sendDisconnectChat(UnicodeString text);

	virtual void sendFile(AsciiString path, UnsignedByte playerMask, UnsignedShort commandID);
	virtual UnsignedShort sendFileAnnounce(AsciiString path, UnsignedByte playerMask);
	virtual Int getFileTransferProgress(Int playerID, AsciiString path);
	virtual Bool areAllQueuesEmpty(void);

	virtual void quitGame();
	virtual void selfDestructPlayer(Int index);

	virtual void voteForPlayerDisconnect(Int slot);
	virtual Bool isPacketRouter(void);

	virtual Real getIncomingBytesPerSecond(void);
	virtual Real getIncomingPacketsPerSecond(void);
	virtual Real getOutgoingBytesPerSecond(void);
	virtual Real getOutgoingPacketsPerSecond(void);
	virtual Real getUnknownBytesPerSecond(void);
	virtual Real getUnknownPacketsPerSecond(void);

	virtual void updateLoadProgress(Int percent);
	virtual void loadProgressComplete(void);
	virtual void sendTimeOutGameStart(void);

#if defined(_INTERNAL) || defined(_DEBUG)
	virtual void toggleNetworkOn();
#endif

	virtual UnsignedInt getLocalPlayerID(void);
	virtual UnicodeString getPlayerName(Int playerNum);
	virtual Int getNumPlayers(void);

	virtual Int getAverageFPS() { return m_conMgr->getAverageFPS(); }
	virtual Int getSlotAverageFPS(Int slot);

	virtual void attachTransport(Transport *transport);
	virtual void initTransport();

	virtual void setSawCRCMismatch(void);
	virtual void _bfme_clearSawCRCMismatch(void);	// slot 42, no Zero Hour counterpart
	virtual Bool sawCRCMismatch(void) { return m_sawCRCMismatch; }
	virtual Bool isPlayerConnected(Int playerID);

	virtual void notifyOthersOfCurrentFrame(void);
	virtual void notifyOthersOfNewFrame(UnsignedInt frame);

	virtual Int getExecutionFrame(void);

	virtual UnsignedInt getPingFrame();
	virtual Int getPingsSent();
	virtual Int getPingsRecieved();

protected:
	void GetCommandsFromCommandList(void);
	void SendCommandsToConnectionManager(void);
	Bool AllCommandsReady(UnsignedInt frame);
	void RelayCommandsToCommandList(UnsignedInt frame);
	Bool isTransferCommand(GameMessage *msg);
	Bool processCommand(GameMessage *msg);
	void processFrameSynchronizedNetCommand(NetCommandRef *msg);
	void processRunAheadCommand(NetRunAheadCommandMsg *msg);
	void processDestroyPlayerCommand(NetDestroyPlayerCommandMsg *msg);
	void endOfGameCheck(void);
	Bool timeForNewFrame(void);

	// BFME's layout, not Zero Hour's. Four things fix what is here:
	//   - ~Network (0x006823B0) destroys m_conMgr and nothing else, so the
	//     std::vector<UnsignedInt> m_CRC[MAX_SLOTS] and std::list<Int>
	//     m_playersToDisconnect Zero Hour carries are not members here: their
	//     destructors would have to run.
	//   - init (0x00681E40) hands this+0x10 to QueryPerformanceFrequency and
	//     this+0x18 to QueryPerformanceCounter, and zeroes this+0x0C.
	//   - quitGame (0x006822E0) and isPlayerConnected (0x00681F30) write and
	//     test this+0x0C as the local status.
	//   - vtable slots 40/41/42 read, set and clear the byte at this+0x35.
	// NetworkInterface::createNetwork allocates 0xA8, which is what the two
	// unidentified spans hold the object to.
	ConnectionManager *m_conMgr;				// +0x08
	NetLocalStatus m_localStatus;				// +0x0C
	__int64 m_perfCountFreq;					// +0x10
	__int64 m_nextFrameTime;					// +0x18
	UnsignedByte m_bfmeUnidentifiedA[0x35 - 0x20];		// +0x20, not yet named
	Bool m_sawCRCMismatch;					// +0x35
	UnsignedByte m_bfmeUnidentifiedB[0xA8 - 0x36];		// +0x36, not yet named
};

NetworkInterface *NetworkInterface::createNetwork()
{
	return NEW Network;
}

Bool Network::isPacketRouter(void)
{
	return m_conMgr && m_conMgr->isPacketRouter();
}

void Network::sendDisconnectChat(UnicodeString text)
{
	m_conMgr->sendDisconnectChat(text);
}

// BFME inlines ConnectionManager's bandwidth getters into their Network
// forwarders; retail reaches the Transport pointer at +0x12024 of the
// connection manager, which is not where the Zero Hour header puts it.
static Transport *conMgrTransport(ConnectionManager *conMgr)
{
	return *(Transport **)((char *)conMgr + 0x12024);
}

Real Network::getIncomingPacketsPerSecond(void)
{
	if (m_conMgr)
	{
		Transport *transport = conMgrTransport(m_conMgr);
		if (transport)
			return transport->getIncomingPacketsPerSecond();
	}
	return 0.0f;
}

// Retail reaches BFME-native helpers on the connection manager that the Zero
// Hour header does not declare; these carry their own retail symbol names.
class BFMEConnectionManager
{
public:
	void sendProgressCommand(Int percent);

	// BFME grew the connection manager before its disconnect manager pointer;
	// the published Zero Hour header does not describe this offset.
	char m_bfmePad[0x120e0];
	DisconnectManager *m_disconnectManager;
};

void Network::updateLoadProgress(Int percent)
{
	if (m_conMgr != NULL)
		((BFMEConnectionManager *)m_conMgr)->sendProgressCommand(percent);
}

// BFME keeps DisconnectManager at +0x120e0 in ConnectionManager. The null
// checks and tail calls match the retail vtable forwarders at 0x00681ac0 and
// 0x00681af0; the getter bodies themselves are the matched implementations in
// DisconnectManager.cpp.
Int Network::getPingsSent()
{
	if (m_conMgr != NULL)
	{
		BFMEConnectionManager *conMgr = (BFMEConnectionManager *)m_conMgr;
		if (conMgr->m_disconnectManager != NULL)
			return conMgr->m_disconnectManager->getPingsSent();
	}
	return 0;
}

Int Network::getPingsRecieved()
{
	if (m_conMgr != NULL)
	{
		BFMEConnectionManager *conMgr = (BFMEConnectionManager *)m_conMgr;
		if (conMgr->m_disconnectManager != NULL)
			return conMgr->m_disconnectManager->getPingsRecieved();
	}
	return 0;
}

// BFME inlines ConnectionManager::getSlotAverageFPS into this forwarder. The
// per-slot frame metrics live in an array at +0x24 of the connection manager
// with a 0x2000 stride, and the accessor on the element stays out of line at
// 0x006630F0 -- unnamed in the image, so it carries an address-derived
// placeholder rather than a guessed FrameMetrics name.
//
// The residue this row was closed on before -- "retail lea ecx,[eax+ecx+0x24]
// encodes a different SIB base/index order than MSVC emits" -- was a
// misreading: retail is 8d 4c 08 24 and every one of eight indexing spellings
// probed here emits 8d 4c 08 24 too. The real discriminator is the null guard's
// SHAPE: Zero Hour's `if (m_conMgr != NULL) { ... } return -1;` nesting puts
// the fallthrough return at the END of the body, which is where retail's
// `xor eax,eax; ret 4` sits. Spelling it as an early `if (m_conMgr == NULL)
// return 0;` hoists that return to the top and moves five bytes.
class Gen_006630f0
{
public:
	Int m(void);
private:
	char m_retailData[0x2000];
};

Int Network::getSlotAverageFPS(Int slot)
{
	if (m_conMgr != NULL)
	{
		if (slot < 0 || slot >= 9)
			return -1;
		return ((Gen_006630f0 *)((char *)m_conMgr + 0x24))[slot].m();
	}
	return 0;
}

// A ternary, not Zero Hour's if/return: with two return statements MSVC builds
// each result straight into the caller's buffer, and the temporary with its own
// unwind state -- which retail has, tracked in bl and released at 0x008881D0 --
// never appears.
UnicodeString Network::getPlayerName(Int playerNum)
{
	return m_conMgr != NULL ? m_conMgr->getPlayerName(playerNum) : UnicodeString::TheEmptyString;
}

// Retail 0x006823B0. Writes Network's vtable (0x0111A968), releases the
// connection manager, then restores NetworkInterface's (0x0111A850) on the way
// into ??1SubsystemInterface@@UAE@XZ -- the pair of vptr stores that identifies
// both tables.
Network::~Network()
{
	delete m_conMgr;
}

void Network::setSawCRCMismatch(void)
{
	m_sawCRCMismatch = TRUE;
}

// Vtable slot 42, wedged between setSawCRCMismatch and isPlayerConnected with
// no Zero Hour counterpart. Named for what it does, not recovered: it clears
// the same byte slot 41 sets and slot 40 reads.
void Network::_bfme_clearSawCRCMismatch(void)
{
	m_sawCRCMismatch = FALSE;
}
