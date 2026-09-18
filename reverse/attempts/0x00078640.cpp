// ??0GameEngine@@QAE@XZ
// partial score=0.35 date=2026-09-17
// cl: /O2 /Ob0 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Working reconstruction for the BFME GameEngine constructor at 0x00078640.
// The additional runtime/helper sequence is kept out of this first probe until
// the verified GameEngine field layout is established.

typedef void *HANDLE;
typedef unsigned char EngineBool;

typedef int (__cdecl *BigObfHook)(void *, void *, __int64);

struct BigObfSlot
{
	BigObfHook m_hook;
	BigObfHook m_alt;
	char m_pad[0x80];
	void *m_a;
	void *m_b;
};

#define g_rva012BC544 (*(BigObfSlot *)0x012BC544)

class Obf00076550
{
public:
	Obf00076550(int *a, int *b);
	unsigned int m_bits[8];
};

class Obf00076710
{
public:
	Obf00076710(int *a, int *b);
	unsigned int m_bits[8];
};

class Obf000767F0
{
public:
	Obf000767F0(int *a, int *b);
	unsigned int m_bits[8];
};

extern int __cdecl Rva000771C0(int a, int b);
extern int __cdecl Gen0006EF90(int a, int b);
extern int __cdecl Gen0006F200(int a, int b);
extern int __cdecl Gen0006F330(int a, int b);

struct Rva00077A90Argument
{
	void *m_first;
	void *m_second;
};

class Rva00077A90Owner
{
public:
	void registerArgument(Rva00077A90Argument *argument);
	unsigned char m_flag;
};

static __forceinline int rva00077140(int a, int b)
{
	BigObfHook hook = g_rva012BC544.m_hook;
	if (hook)
		goto hot;
	if (g_rva012BC544.m_alt)
	{
	hot:
		void *pa = g_rva012BC544.m_a;
		void *pb = g_rva012BC544.m_b;
		Obf00076550 state(&a, &b);
		return hook(pa, pb, (__int64)(int)&state);
	}
	return Gen0006EF90(a, b);
}

static __forceinline int rva00077240(int a, int b)
{
	BigObfHook hook = g_rva012BC544.m_hook;
	if (hook)
		goto hot;
	if (g_rva012BC544.m_alt)
	{
	hot:
		void *pa = g_rva012BC544.m_a;
		void *pb = g_rva012BC544.m_b;
		Obf00076710 state(&a, &b);
		return hook(pa, pb, (__int64)(int)&state);
	}
	return Gen0006F200(a, b);
}

static __forceinline int rva000772C0(int a, int b)
{
	BigObfHook hook = g_rva012BC544.m_hook;
	if (hook)
		goto hot;
	if (g_rva012BC544.m_alt)
	{
	hot:
		void *pa = g_rva012BC544.m_a;
		void *pb = g_rva012BC544.m_b;
		Obf000767F0 state(&a, &b);
		return hook(pa, pb, (__int64)(int)&state);
	}
	return Gen0006F330(a, b);
}

extern "C" __declspec(dllimport) unsigned int __stdcall timeBeginPeriod(
	unsigned int period);

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();

	void *m_name;
};

class __declspec(novtable) GameEngine : public SubsystemInterface
{
public:
	GameEngine();
	virtual ~GameEngine();

private:
	int m_maxFPS;                         // 0x08
	EngineBool m_quitting;                // 0x0C
	EngineBool m_isActive;                // 0x0D
	char m_alignment0E[2];
	int m_childProcessCount;              // 0x10
	HANDLE m_childProcesses[7];           // 0x14..0x2F
	int m_clientFramePeriod;              // 0x30
	int m_clientFrameCounter;             // 0x34
	float m_clientFrameRatio;             // 0x38
	EngineBool m_clientFrameRatioPending; // 0x3C
	char m_unknown3D[3];
	float m_clientFrameLimit;             // 0x40
	unsigned int m_metric44;              // 0x44
	unsigned int m_metric48;              // 0x48
	int m_metric4C;                       // 0x4C
	unsigned int m_metric50;              // 0x50, reset initializes it
	float m_metric54;                     // 0x54
	int m_metric58;                       // 0x58
};

GameEngine::GameEngine()
{
	*(volatile unsigned int *)this = 0x01075BC8;
	m_maxFPS = 0;
	m_quitting = 0;
	m_isActive = 0;
	m_childProcessCount = 0;
	m_clientFramePeriod = 0;
	m_clientFrameCounter = 1;
	m_clientFrameRatio = 0.0f;
	m_clientFrameRatioPending = 0;
	m_clientFrameLimit = 1.0f;
	m_metric44 = 0;
	m_metric48 = 0;
	m_metric4C = 0;
	m_metric54 = 0.0f;
	m_metric58 = 0;
	timeBeginPeriod(1);

	int value = Rva000771C0(0, 0);
	for (;;)
	{
		if (rva00077140(value, (int)0xe0092dc0) == (int)0xa590217b)
			break;

		m_childProcesses[rva000772C0(value, value)] = 0;
		rva00077240((int)0x0790a442, value);
	}

	Rva00077A90Owner owner;
	Rva00077A90Argument argument;
	argument.m_first = (void *)0x012A7248;
	argument.m_second = (void *)0x012A7244;
	owner.m_flag = 0;
	owner.registerArgument(&argument);
}
