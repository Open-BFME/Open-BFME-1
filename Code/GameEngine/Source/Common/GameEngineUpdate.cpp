// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O2 /GX
// readable body of ?update@GameEngine@@UAEXXZ: Code/GameEngine/Source/Common/GameEngine.cpp

typedef unsigned int UnsignedInt;

extern "C" __declspec(dllimport) UnsignedInt __stdcall timeGetTime(void);

class UpdateSubsystem
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void update(void);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	void _bfme_updateClientDebugFrame(void);
	bool _bfme_isClientFrameFrozen(void);
};

class DebugManager
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
	virtual void slot35(void);
	virtual void finishFrame(void);
};

struct ClientFrameState
{
	char m_unknown00[0xC4];
	unsigned char m_advanceFrame;
};

#define FirstUpdateSubsystem (*(UpdateSubsystem **)0x0134FAA0)
#define SecondUpdateSubsystem (*(UpdateSubsystem **)0x012F1028)
#define TheScriptEngine (*(ScriptEngine **)0x012F076C)
#define TheGameClient (*(ClientFrameState **)0x012F1464)
#define TheDebugManager (*(DebugManager **)0x01336E5C)
#define Zero (*(const float *)0x01075350)
#define One (*(const float *)0x01075334)
#define MillisecondsToSeconds (*(const double *)0x01075D80)

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameEngine.h
class GameEngine
{
public:
	virtual void slot00(void);
	virtual void slot01(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void reset(void);
	virtual void update(void);
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
	virtual void _bfme_updateNetworkAndLogic(int phase);
	virtual void _bfme_updateClientSubsystems(void);

private:
	void _bfme_updateClientFrameRatio(void);

	char m_unknown04[0x2C];
	int m_clientFramePeriod;
	int m_clientFrameCounter;
	float m_clientFrameRatio;
	bool m_clientFrameRatioPending;
	char m_unknown3D[3];
	float m_clientFrameLimit;
	UnsignedInt m_metric44;
	UnsignedInt m_metric48;
	int m_metric4C;
	UnsignedInt m_metric50;
	float m_metric54;
	int m_metric58;
};

// Keeping this body visible lets VC7.1 retain ECX across the call, as retail does.
__declspec(noinline) void GameEngine::_bfme_updateClientFrameRatio(void)
{
	float ratio = (float)m_clientFramePeriod / (float)m_clientFrameCounter;
	m_clientFrameRatio = ratio;
	if (ratio < 0.0f)
		m_clientFrameRatio = 0.0f;
	else if (ratio > 1.0f)
		m_clientFrameRatio = 1.0f;
	else
		m_clientFrameRatio = ratio;
}

void GameEngine::update(void)
{
	FirstUpdateSubsystem->update();
	SecondUpdateSubsystem->update();
	TheScriptEngine->_bfme_updateClientDebugFrame();
	bool skipClientFrame = TheScriptEngine->_bfme_isClientFrameFrozen();
	_bfme_updateClientSubsystems();
	if (skipClientFrame)
	{
		TheGameClient->m_advanceFrame = 0;
		TheDebugManager->finishFrame();
		return;
	}

	TheGameClient->m_advanceFrame = 1;
	int period = m_clientFramePeriod;
	if (period == 6 && m_clientFrameRatioPending)
	{
		m_clientFrameCounter = period;
		m_clientFrameRatioPending = false;
	}

	int newPeriod = period + 1;
	m_clientFramePeriod = newPeriod;
	float ratio = (float)newPeriod / (float)m_clientFrameCounter;
	m_clientFrameRatio = ratio;
	if (ratio < 0.0f)
		ratio = 0.0f;
	else if (ratio > 1.0f)
		ratio = 1.0f;
	m_clientFrameRatio = ratio;

	if (newPeriod > 6)
	{
		if (m_metric4C % 25 == 0)
		{
			UnsignedInt elapsed = timeGetTime();
			elapsed -= m_metric50;
			double elapsedSeconds = (float)elapsed * MillisecondsToSeconds;
			double updateCount = (double)m_metric4C;
			m_metric4C = 0;
			double frameCount = (double)m_metric58;
			m_metric58 = 0;
			m_metric54 = (float)((frameCount / updateCount) *
				(updateCount / elapsedSeconds));
			m_metric50 = timeGetTime();
		}

		m_metric58 += m_clientFrameCounter;
		++m_metric4C;
		int savedPeriod = m_clientFramePeriod;
		m_clientFramePeriod = 1;
		_bfme_updateClientFrameRatio();
		_bfme_updateNetworkAndLogic(1);
		if (TheGameClient->m_advanceFrame)
			m_clientFrameRatioPending = true;
		else
		{
			m_clientFramePeriod = savedPeriod;
			_bfme_updateClientFrameRatio();
		}
	}
	else
		_bfme_updateNetworkAndLogic(newPeriod);

	TheDebugManager->finishFrame();
}
