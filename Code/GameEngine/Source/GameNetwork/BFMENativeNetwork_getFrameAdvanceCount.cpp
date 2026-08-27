// cl: /DNDEBUG /MD /GX

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime(void);
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(__int64 *counter);
extern int g_networkTimingOverruns;

struct GameLogicFrame
{
	char unknown[0x3C];
	unsigned int frame;
};

class BFMEConnectionManager
{
public:
	bool hasPacketRouterFrameStall(void);
	bool areFrameCommandsComplete(unsigned int frame, bool debugSpewage);

	char unknown[0x1205C];
	int frameCeiling;
};

class BFMENativeNetwork
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual void slot07(void);
	virtual void slot08(void);
	virtual void updateNetwork(bool flush);
	virtual void slot10(void);
	virtual void slot11(void);
	virtual void slot12(void);
	virtual void slot13(void);
	virtual void slot14(void);
	virtual void slot15(void);
	virtual void slot16(void);
	virtual void slot17(void);
	virtual void slot18(void);
	virtual void slot19(void);
	virtual void slot20(void);
	virtual void slot21(void);
	virtual void slot22(void);
	virtual void slot23(void);
	virtual void slot24(void);
	virtual void slot25(void);
	virtual void slot26(void);
	virtual void slot27(void);
	virtual void slot28(void);
	virtual void slot29(void);
	virtual void slot30(void);
	virtual void slot31(void);
	virtual void slot32(void);
	virtual void slot33(void);
	virtual void slot34(void);
	virtual bool isPacketRouter(void);

	int getFrameAdvanceCount(void);

private:
	BFMEConnectionManager *m_conMgr;
	int m_state;
	__int64 m_frequency;
	__int64 m_lastCounter;
	__int64 m_accumulator;
	bool m_stallTimerRunning;
	char m_pad29[3];
	int m_stallCount;
};

#define TheGameLogic (*(GameLogicFrame **)0x012F0898)
#define StallStartTime (*(unsigned int *)0x012F7718)
#define LastAdvanceTime (*(unsigned int *)0x012F771C)
#define LastStallFrame (*(unsigned int *)0x012F7728)

int BFMENativeNetwork::getFrameAdvanceCount(void)
{
	if (m_state != 1)
		return 1;

	if (!isPacketRouter()) {
		if (TheGameLogic->frame == 0)
			return 1;

		if (!m_stallTimerRunning) {
			StallStartTime = timeGetTime();
			m_stallTimerRunning = 1;
		}

		int allowance = m_conMgr->frameCeiling - TheGameLogic->frame + 1;
		if (allowance > 0) {
			if (!m_conMgr->areFrameCommandsComplete(TheGameLogic->frame, 0)) {
				updateNetwork(0);
				return 0;
			}
			m_stallTimerRunning = 0;
			return allowance;
		}

		if (TheGameLogic->frame != LastStallFrame) {
			++m_stallCount;
			LastStallFrame = TheGameLogic->frame;
		}
		return allowance;
	}

	if (m_conMgr->hasPacketRouterFrameStall()) {
		m_accumulator = 0;
		return 0;
	}

	__int64 now;
	QueryPerformanceCounter(&now);
	m_accumulator += now - m_lastCounter;
	m_lastCounter = now;

	__int64 quantum = m_frequency / 5;
	if (m_accumulator < quantum)
		return 0;

	m_accumulator -= quantum;
	if (m_accumulator > m_frequency * 2) {
		++g_networkTimingOverruns;
		m_accumulator = 0;
	} else {
		g_networkTimingOverruns = 0;
	}

	LastAdvanceTime = timeGetTime();
	return 1;
}
