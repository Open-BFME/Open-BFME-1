// ?execute@GameEngine@@UAEXXZ
// partial score=0.89 date=2026-08-28
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include

#include <string.h>
#include "Common/INIException.h"

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

typedef unsigned char Bool;
typedef unsigned int UnsignedInt;

enum RecorderModeType
{
	RECORDER_MODE_RECORD = 0
};

extern "C" UnsignedInt __stdcall bfme_timeGetTime(void);
extern "C" __declspec(dllimport) void __stdcall Sleep(UnsignedInt milliseconds);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Recorder.h
class RecorderClass
{
public:
	RecorderModeType getMode(void);
	bool isMultiplayer(void);
	void cleanUpReplayFile(void);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StatsCollector.h
class StatsCollector
{
public:
	void update(void);
	void writeFileEnd(void);
};

extern StatsCollector *RetailStatsCollector;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/ScriptEngine.h
class ScriptEngine
{
public:
	bool isTimeFast(void);
};

class TacticalView
{
public:
	virtual void slot00(void); virtual void slot01(void); virtual void slot02(void);
	virtual void slot03(void); virtual void slot04(void); virtual void slot05(void);
	virtual void slot06(void); virtual void slot07(void); virtual void slot08(void);
	virtual void slot09(void); virtual void slot10(void); virtual void slot11(void);
	virtual void slot12(void); virtual void slot13(void); virtual void slot14(void);
	virtual void slot15(void); virtual void slot16(void); virtual void slot17(void);
	virtual void slot18(void); virtual void slot19(void); virtual void slot20(void);
	virtual void slot21(void); virtual void slot22(void); virtual void slot23(void);
	virtual void slot24(void); virtual void slot25(void); virtual void slot26(void);
	virtual void slot27(void); virtual void slot28(void); virtual void slot29(void);
	virtual void slot30(void); virtual void slot31(void); virtual void slot32(void);
	virtual void slot33(void); virtual void slot34(void); virtual void slot35(void);
	virtual void slot36(void); virtual void slot37(void); virtual void slot38(void);
	virtual void slot39(void); virtual void slot40(void); virtual void slot41(void);
	virtual void slot42(void); virtual void slot43(void); virtual void slot44(void);
	virtual void slot45(void); virtual void slot46(void); virtual void slot47(void);
	virtual void slot48(void); virtual void slot49(void); virtual void slot50(void);
	virtual void slot51(void); virtual void slot52(void); virtual void slot53(void);
	virtual int getTimeMultiplier(void);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetworkInterface.h
class NetworkInterface
{
public:
	virtual void slot00(void); virtual void slot01(void); virtual void slot02(void);
	virtual void slot03(void); virtual void slot04(void); virtual void slot05(void);
	virtual void slot06(void); virtual void slot07(void); virtual void slot08(void);
	virtual void slot09(void); virtual void slot10(void); virtual void slot11(void);
	virtual void slot12(void); virtual void slot13(void); virtual void slot14(void);
	virtual void slot15(void);
	virtual int getFramePacingStatus(void);
	virtual int getFrameHeadroom(void);
	virtual void slot18(void); virtual void slot19(void); virtual void slot20(void);
	virtual void slot21(void); virtual void slot22(void); virtual void slot23(void);
	virtual void slot24(void); virtual void slot25(void); virtual void slot26(void);
	virtual void slot27(void); virtual void slot28(void); virtual void slot29(void);
	virtual void slot30(void); virtual void slot31(void); virtual void slot32(void);
	virtual void slot33(void); virtual void slot34(void);
	virtual bool isPacketRouter(void);
	virtual void slot36(void);
	virtual int getNumPlayers(void);
};

extern NetworkInterface *TheNetwork;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameClient.h
class GameClient
{
public:
	virtual void slot00(void); virtual void slot01(void); virtual void slot02(void);
	virtual void slot03(void); virtual void slot04(void); virtual void slot05(void);
	virtual void slot06(void); virtual void slot07(void); virtual void slot08(void);
	virtual void slot09(void); virtual void slot10(void); virtual void slot11(void);
	virtual void slot12(void); virtual void slot13(void); virtual void slot14(void);
	virtual void slot15(void); virtual void slot16(void); virtual void slot17(void);
	virtual void slot18(void); virtual void slot19(void); virtual void slot20(void);
	virtual void slot21(void); virtual void slot22(void); virtual void slot23(void);
	virtual void slot24(void); virtual void slot25(void);
	virtual UnsignedInt getFrame(void);
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GlobalLanguage.h
class GlobalLanguage
{
public:
	void onGameEngineExit(void);
};

class CrashMessage
{
public:
	virtual void slot00(void); virtual void slot01(void); virtual void slot02(void);
	virtual void slot03(void); virtual void slot04(void); virtual void slot05(void);
	virtual void slot06(void); virtual void slot07(void); virtual void slot08(void);
	virtual void slot09(void); virtual void slot10(void); virtual void slot11(void);
	virtual void slot12(void); virtual void slot13(void);
	virtual CrashMessage *setText(const char *text);
	virtual void slot15(void); virtual void slot16(void); virtual void slot17(void);
	virtual void slot18(void);
	virtual void show(bool visible);
};

class DebugManager
{
public:
	virtual void slot00(void); virtual void slot01(void); virtual void slot02(void);
	virtual void slot03(void); virtual void slot04(void); virtual void slot05(void);
	virtual void slot06(void); virtual void slot07(void); virtual void slot08(void);
	virtual void slot09(void); virtual void slot10(void); virtual void slot11(void);
	virtual void slot12(void); virtual void slot13(void); virtual void slot14(void);
	virtual void slot15(void); virtual void slot16(void); virtual void slot17(void);
	virtual void slot18(void); virtual void slot19(void); virtual void slot20(void);
	virtual void slot21(void); virtual void slot22(void); virtual void slot23(void);
	virtual void beginReport(void);
	virtual void slot25(void); virtual void slot26(void);
	virtual CrashMessage *getCrashMessage(void *a, void *b);
};

void _bfme_debugRecordCallsite(int kind);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameEngine.h
class GameEngine
{
public:
	virtual void slot00(void); virtual void slot01(void); virtual void slot02(void);
	virtual void slot03(void); virtual void slot04(void);
	virtual void update(void);
	virtual void execute(void);

private:
	void *m_unknown04;
	int m_maxFPS;
	bool m_quitting;
	char m_gap0D[0x23];
	int m_clientFramePeriod;
};

struct GlobalDataLayout
{
	char gap00[0x1E];
	bool useFpsLimit;
	char gap1F[0xC59 - 0x1F];
	bool fastMode;
};

#define TheRecorder (*(RecorderClass **)0x012ED62C)
#define TheStatsCollector (*(StatsCollector **)0x012EF18C)
#define TheScriptEngine (*(ScriptEngine **)0x012F076C)
#define TheTacticalView (*(TacticalView **)0x012F1600)
#define TheGameClient (*(GameClient **)0x012F1464)
#define TheGlobalLanguageData (*(GlobalLanguage **)0x012F1484)
#define TheGlobalData (*(GlobalDataLayout **)0x012ED5C8)
#define TheDebugManager (*(DebugManager **)0x01336E5C)

#define LogicTimeScale (*(float *)0x012A72A4)
#define LogicFrameAdjustment (**(int **)0x012A7244)
#define SavedClientFrame (*(int *)0x012ED508)
#define SleepTimeTotal (*(UnsignedInt *)0x012ED50C)
#define SleepTimeRemaining (*(UnsignedInt *)0x012ED510)
#define FrameElapsedTime (*(UnsignedInt *)0x012ED514)
#define PreviousFrameTime (*(UnsignedInt *)0x012ED518)
#define InitialFrameTime (*(UnsignedInt *)0x012ED51C)
#define LimitFrameRate (*(bool *)0x012ED520)
#define DisablePacingA (*(bool *)0x012ED4E5)
#define DisablePacingB (*(bool *)0x012ED4E6)

#define REPORT_CRASH(reason) do { \
	_bfme_debugRecordCallsite(1); \
	DebugManager *manager = TheDebugManager; \
	manager->beginReport(); \
	manager = TheDebugManager; \
	CrashMessage *message = manager->getCrashMessage(0, 0); \
	message->setText(reason)->show(true); \
} while (0)

// ?execute@GameEngine@@UAEXXZ present-unmatched
void GameEngine::execute(void)
{
	if (InitialFrameTime == 0)
		InitialFrameTime = bfme_timeGetTime();
	// Retail retains this otherwise-unused profiler singleton load before the loop.
	__asm
	{
		mov ecx, RetailStatsCollector
		nop
	}

	while (!m_quitting)
	{
		float oldScale;
		try
		{
			update();
		}
		catch (INIException *e)
		{
			char *failure = e->mFailureMessage;
			if (failure)
			{
				_bfme_debugRecordCallsite(1);
				DebugManager *manager = TheDebugManager;
				manager->beginReport();
				manager = TheDebugManager;
				CrashMessage *message = manager->getCrashMessage(0, 0);
				message->setText("\n\n")->setText(e->mFailureMessage)->show(true);
			}
			else
				REPORT_CRASH("\n\nUncaught INI exception in GameEngine::update");
		}
		catch (...)
		{
			try
			{
				RecorderClass *recorder = TheRecorder;
				if (recorder && recorder->getMode() == RECORDER_MODE_RECORD && TheRecorder->isMultiplayer())
					TheRecorder->cleanUpReplayFile();
			}
			catch (...)
			{
			}
			REPORT_CRASH("Uncaught Exception in GameEngine::update");
		}

		TacticalView *view = TheTacticalView;
		LimitFrameRate = false;
		if (view->getTimeMultiplier() <= 1 && !TheScriptEngine->isTimeFast())
			LimitFrameRate = TheGlobalData->useFpsLimit;
		if (TheGlobalData->fastMode)
			LimitFrameRate = false;

		oldScale = LogicTimeScale;
		NetworkInterface *network = TheNetwork;
		if (!network)
			goto force_normal_speed;
		if (DisablePacingA)
			goto force_normal_speed;
		if (DisablePacingB)
			goto force_normal_speed;
		if (m_clientFramePeriod != 1)
			goto pacing_done;

		LogicTimeScale = 1.0f;
		if (network->getNumPlayers() == 1)
		{
	force_normal_speed:
			LogicTimeScale = 1.0f;
			goto pacing_done;
		}

	multiplayer_pacing:
		float desired;
		if (TheNetwork->isPacketRouter())
		{
			network = TheNetwork;
			LimitFrameRate = true;
			int headroom = network->getFrameHeadroom();
			if (headroom > 10)
				headroom = 10;
			if (headroom <= 5)
				goto pacing_done;
			desired = (10.0f - (float)headroom) * 0.1f + 0.5f;
		}
		else
		{
			network = TheNetwork;
			desired = (float)network->getFramePacingStatus() * 0.1f + 0.7f;
			if (!(desired < 1.0f))
				desired = 1.0f;
		}

		_ReadWriteBarrier();
		LogicTimeScale = (desired + oldScale) * 0.5f;

	pacing_done:
		if (1.0f != *(volatile float *)0x012A72A4)
			LimitFrameRate = true;

		if ((UnsignedInt)SavedClientFrame + 6 > TheGameClient->getFrame())
		{
			LimitFrameRate = false;

	unlimited_frame:
			{
				UnsignedInt now = bfme_timeGetTime();
				FrameElapsedTime = now - PreviousFrameTime;
				SleepTimeRemaining = 0;
				PreviousFrameTime = now;
			}

	frame_complete:
			StatsCollector *stats = TheStatsCollector;
			if (stats)
				stats->update();
			continue;
		}

		if (!LimitFrameRate)
			goto unlimited_frame;

		{
			UnsignedInt now = bfme_timeGetTime();
			int limit = (int)(1000.0f / ((float)m_maxFPS * LogicTimeScale) + (float)LogicFrameAdjustment);
			UnsignedInt elapsed = now - PreviousFrameTime;
			FrameElapsedTime = elapsed;
			UnsignedInt remaining = 0;
			if (elapsed < (UnsignedInt)limit)
				remaining = (UnsignedInt)limit - elapsed;
			SleepTimeTotal += remaining;
			SleepTimeRemaining = remaining;
			while (elapsed < (UnsignedInt)limit)
			{
				Sleep(0);
				now = bfme_timeGetTime();
				elapsed = now - PreviousFrameTime;
			}
			PreviousFrameTime = now;
		}
		goto frame_complete;
	}

	StatsCollector *stats = TheStatsCollector;
	if (stats)
		stats->writeFileEnd();
	GlobalLanguage *language = TheGlobalLanguageData;
	if (language)
		language->onGameEngineExit();
}
