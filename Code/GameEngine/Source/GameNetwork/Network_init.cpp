// cl: /DNDEBUG /MD /EHsc

// Retail 0x00681E40, Network vtable 0x0111A968 slot 1. BFME inlines ZH's
// deinit() as destructor+delete of m_conMgr, then new 0x12190 ConnectionManager,
// virtual init at slot 0, PREGAME status, QPF/QPC, stall fields, timeGetTime
// into StallStartTime, GameLogic::resetPlayerLeaveStatus, +0x38 = -1.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef bool Bool;

enum NetLocalStatus
{
	NETLOCALSTATUS_PREGAME = 0,
	NETLOCALSTATUS_INGAME,
	NETLOCALSTATUS_LEAVING,
	NETLOCALSTATUS_LEFT
};

extern "C" __declspec(dllimport) int __stdcall QueryPerformanceFrequency(UnsignedInt *freq);
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(UnsignedInt *counter);
extern "C" __declspec(dllimport) UnsignedInt __stdcall timeGetTime(void);

void __cdecl operator delete(void *p);

class GameLogic
{
public:
	void resetPlayerLeaveStatus(void);
};

extern GameLogic *TheGameLogic;

class ConnectionManager
{
public:
	ConnectionManager();
	~ConnectionManager();
	virtual void init(void);

private:
	unsigned char m_bfmePad[0x12190 - 4];
};

class Network
{
public:
	virtual void _bfme_slot0(void) = 0;
	virtual void init(void);

protected:
	void *m_subsystemName;
	ConnectionManager *m_conMgr;
	NetLocalStatus m_localStatus;
	UnsignedInt m_perfCountFreq[2];
	UnsignedInt m_nextFrameTime[2];
	UnsignedInt m_accumulator[2];
	Bool m_stallTimerRunning;
	UnsignedByte m_pad29[3];
	Int m_stallCount;
	UnsignedByte m_pad30[4];
	UnsignedByte m_byte34;
	Bool m_sawCRCMismatch;
	UnsignedByte m_pad36[2];
	Int m_field38;
};

#define StallStartTime (*(UnsignedInt *)0x012F7718)

void Network::init(void)
{
	ConnectionManager *old = m_conMgr;
	if (old != 0)
	{
		old->~ConnectionManager();
		operator delete(old);
	}

	m_conMgr = new ConnectionManager;
	m_conMgr->init();
	m_localStatus = NETLOCALSTATUS_PREGAME;
	QueryPerformanceFrequency(m_perfCountFreq);
	QueryPerformanceCounter(m_nextFrameTime);
	m_accumulator[0] = 0;
	m_accumulator[1] = 0;
	m_byte34 = 0;
	{
		UnsignedInt now = timeGetTime();
		m_stallTimerRunning = 0;
		m_stallCount = 0;
		GameLogic *logic = TheGameLogic;
		StallStartTime = now;
		logic->resetPlayerLeaveStatus();
	}
	m_field38 = -1;
}
