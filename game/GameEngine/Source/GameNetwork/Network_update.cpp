// cl: /DNDEBUG /MD /GX

enum PlayerLeaveCode
{
	PLAYER_LEAVE_CODE_CLIENT
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/ConnectionManager.h
class ConnectionManager
{
public:
	PlayerLeaveCode disconnectPlayer(int slot);
	__declspec(noinline) void disconnectLocalPlayer(void);

	unsigned char m_unmodelled_00000[0x12028];
	int m_localSlot;
	unsigned char m_unmodelled_1202C[0x1205C - 0x1202C];
	int m_frameCeiling;
};

class BFMEConnectionManager
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void update(bool isInGame, bool phase) = 0;

	bool hasPacketRouterFrameStall(void);
	bool areFrameCommandsComplete(unsigned int frame, bool debugSpewage);
};

class GameMessage;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MessageStream.h
class MessageStream
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual GameMessage *appendMessage(unsigned int type) = 0;
};

extern MessageStream *TheMessageStream;

void ConnectionManager::disconnectLocalPlayer(void)
{
	for (int slot = 0; slot < 8; ++slot)
	{
		if (slot != m_localSlot)
			disconnectPlayer(slot);
	}
}

class Network
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void liteupdate(bool phase) = 0;
	virtual void update(bool phase);
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual int IsFrameReady(void);
	virtual int PeekFrameReady(void);
	virtual void slot17(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot19(void) = 0;
	virtual void slot20(void) = 0;
	virtual void slot21(void) = 0;
	virtual void slot22(void) = 0;
	virtual void slot23(void) = 0;
	virtual void slot24(void) = 0;
	virtual void slot25(void) = 0;
	virtual void slot26(void) = 0;
	virtual void slot27(void) = 0;
	virtual void slot28(void) = 0;
	virtual void slot29(void) = 0;
	virtual void slot30(void) = 0;
	virtual void slot31(void) = 0;
	virtual void slot32(void) = 0;
	virtual void slot33(void) = 0;
	virtual void slot34(void) = 0;
	virtual bool isPacketRouter(void) = 0;

protected:
	void GetCommandsFromCommandList(void);
	void RelayCommandsToCommandList(void);

private:
	// The __int64 members align the class to 8, so MSVC pads the vfptr and
	// m_conMgr sits at +0x08 (init 0x00681E40 hands +0x10 to
	// QueryPerformanceFrequency and +0x18 to QueryPerformanceCounter).
	ConnectionManager *m_conMgr;				// +0x08
	int m_localStatus;					// +0x0C
	__int64 m_perfCountFreq;				// +0x10
	__int64 m_lastCounter;					// +0x18
	__int64 m_accumulator;					// +0x20
	bool m_stallTimerRunning;				// +0x28
	int m_stallCount;					// +0x2C
	unsigned char m_gap30[4];				// +0x30
	bool m_frameDataReady;					// +0x34
};

void Network::liteupdate(bool phase)
{
	if (m_conMgr != 0)
	{
		BFMEConnectionManager *conMgr = (BFMEConnectionManager *)m_conMgr;
		conMgr->update(m_localStatus == 1, phase);
	}
}

void Network::update(bool phase)
{
	m_frameDataReady = false;
	if (m_localStatus == 0)
		m_localStatus = 1;

	GetCommandsFromCommandList();
	liteupdate(phase);

	if (m_localStatus == 2)
	{
		m_conMgr->disconnectLocalPlayer();
		TheMessageStream->appendMessage(0x1D);
		m_localStatus = 3;
	}

	RelayCommandsToCommandList();
}

extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(__int64 *counter);
extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);
extern int g_networkTimingOverruns;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	unsigned int getFrame(void) { return m_frame; }

private:
	char unknown[0x3C];
	unsigned int m_frame;
};

extern GameLogic *TheGameLogic;

extern unsigned int g_012F7718;
extern unsigned int g_012F771C;
extern unsigned int g_012F7728;

#define BFMEStallStartTime g_012F7718
#define BFMELastAdvanceTime g_012F771C
#define BFMELastStallFrame g_012F7728

// Vtable 0x0111A968 slot 15 (+0x3C), EA's Network::IsFrameReady. Returns how
// many logic frames the sim may advance now: 1 outside a network game,
// (frameCeiling - currentFrame + 1) when that is positive and the connection
// manager reports the frame's commands complete, 0 when they are not, and the
// non-positive allowance when starved. As packet router it instead consumes a
// fixed QueryPerformanceFrequency/5 (200ms) quantum.
int Network::IsFrameReady(void)
{
	if (m_localStatus != 1)
		return 1;

	if (!isPacketRouter()) {
		if (TheGameLogic->getFrame() == 0)
			return 1;

		if (!m_stallTimerRunning) {
			BFMEStallStartTime = timeGetTime();
			m_stallTimerRunning = 1;
		}

		int allowance = m_conMgr->m_frameCeiling - TheGameLogic->getFrame() + 1;
		if (allowance > 0) {
			if (!((BFMEConnectionManager *)m_conMgr)->areFrameCommandsComplete(TheGameLogic->getFrame(), 0)) {
				liteupdate(0);
				return 0;
			}
			m_stallTimerRunning = 0;
			return allowance;
		}

		if (TheGameLogic->getFrame() != BFMELastStallFrame) {
			++m_stallCount;
			BFMELastStallFrame = TheGameLogic->getFrame();
		}
		return allowance;
	}

	if (((BFMEConnectionManager *)m_conMgr)->hasPacketRouterFrameStall()) {
		m_accumulator = 0;
		return 0;
	}

	__int64 now;
	QueryPerformanceCounter(&now);
	m_accumulator += now - m_lastCounter;
	m_lastCounter = now;

	__int64 quantum = m_perfCountFreq / 5;
	if (m_accumulator < quantum)
		return 0;

	m_accumulator -= quantum;
	if (m_accumulator > m_perfCountFreq * 2) {
		++g_networkTimingOverruns;
		m_accumulator = 0;
	} else {
		g_networkTimingOverruns = 0;
	}

	BFMELastAdvanceTime = timeGetTime();
	return 1;
}

// Vtable 0x0111A968 slot 16 (+0x40), EA's Network::PeekFrameReady: the same
// readiness test without consuming the router quantum; 2 once 1.5 quanta
// have accumulated.
int Network::PeekFrameReady(void)
{
	if (m_localStatus != 1)
		return 1;

	if (!isPacketRouter())
		return m_conMgr->m_frameCeiling - TheGameLogic->getFrame() + 1;

	__int64 now;
	QueryPerformanceCounter(&now);
	m_accumulator += now - m_lastCounter;
	m_lastCounter = now;

	__int64 quantum = m_perfCountFreq / 5;
	if (m_accumulator < quantum)
		return 0;

	if ((float)m_accumulator < (float)quantum * 1.5f)
		return 1;

	return 2;
}

extern "C" unsigned int __identifier("?g_012F771C@@3IA") = 0;
