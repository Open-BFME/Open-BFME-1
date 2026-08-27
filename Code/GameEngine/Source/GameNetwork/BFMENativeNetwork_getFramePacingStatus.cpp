// cl: /DNDEBUG /MD /GX

extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(__int64 *counter);

struct GameLogicFrame
{
	char unknown[0x3C];
	unsigned int frame;
};

class BFMEConnectionManager
{
public:
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
	virtual void slot09(void);
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

	int getFramePacingStatus(void);

private:
	BFMEConnectionManager *m_conMgr;
	int m_state;
	__int64 m_frequency;
	__int64 m_lastCounter;
	__int64 m_accumulator;
};

#define TheGameLogic (*(GameLogicFrame **)0x012F0898)

int BFMENativeNetwork::getFramePacingStatus(void)
{
	if (m_state != 1)
		return 1;

	if (!isPacketRouter())
		return m_conMgr->frameCeiling - TheGameLogic->frame + 1;

	__int64 now;
	QueryPerformanceCounter(&now);
	m_accumulator += now - m_lastCounter;
	m_lastCounter = now;

	__int64 quantum = m_frequency / 5;
	if (m_accumulator < quantum)
		return 0;

	if ((float)m_accumulator < (float)quantum * 1.5f)
		return 1;

	return 2;
}
