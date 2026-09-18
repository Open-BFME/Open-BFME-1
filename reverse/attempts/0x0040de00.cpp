// ?d_0040de00@@YAXXZ
// partial score=0.4 date=2026-09-17
// cl: /O2 /Ob0
//
// The owner of this 502-byte body is not identified in the available BFME
// evidence.  The layout below is limited to the fields and virtual slots
// witnessed by the retail body and by the landed neighbours.

extern "C" __declspec(dllimport) int __cdecl sprintf(
	char *, const char *, ...);
extern "C" __declspec(dllimport) void __stdcall Rva01358EA8(
	const char *);

int j_000481e4(void);

class Rva0040DE00Subobject
{
public:
	virtual int slot00();
	virtual int slot04();
	virtual int slot08();
	virtual int slot0C();
	virtual int slot10();
	virtual int slot14();
	virtual int slot18(int);
	virtual int slot1C();
	virtual int slot20();
	virtual int slot24();
	virtual int slot28();
	virtual int slot2C();
	virtual int slot30();
	virtual int slot34();
	virtual int slot38();
	virtual int slot3C();
	virtual int slot40();
	virtual void slot44(float);
	virtual float slot48();
};

class Rva0040DE00OwnerVtable
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
};

class Rva0040DE00Owner
{
public:
	void update();
	void bfmeGoDC();

	void *m_vtable;
	char m_pad04[0x30];
	Rva0040DE00Subobject *m_34;
	int m_38;
	int m_3C;
	int m_40;
	char m_pad44[0x14];
	unsigned char m_58;
	char m_pad59[0x83];
	int m_DC;
	int m_E0;
	int m_E4;
	int m_E8;
	char m_padEC[0x20];
	int m_10C;
};

#pragma comment(linker, "/alternatename:?bfmeGoDC@Rva0040DE00Owner@@QAEXXZ=?j_0003eeaf@@YAXXZ")

static long long *const g_frameStart = (long long *)0x012F1280;
static long long *const g_frameEnd = (long long *)0x012F1288;
static int *const g_frameOwner = (int *)0x012F1268;
static unsigned char *const g_frameEnabled = (unsigned char *)0x012F126C;
static long long *const g_frameStamp = (long long *)0x012F1278;
static long long *const g_frameDelta = (long long *)0x012F1298;
static double *const g_frameAverage = (double *)0x012F12A0;
static double *const g_frameValue = (double *)0x012F12A8;
static int *const g_frameCount = (int *)0x012F12B0;

static double *const g_frameScale = (double *)0x010F0D58;
static double *const g_frameFactor = (double *)0x010EE5F0;
static double *const g_zeroDouble = (double *)0x01085F58;
static float *const g_frameBias = (float *)0x010BA670;
static float *const g_zeroFloat = (float *)0x01075350;

void Rva0040DE00Owner::update()
{
	if (m_34 == 0 || m_40 != 0)
		return;

	*g_frameOwner = (int)m_34;
	long long frameDelta = *g_frameEnd - *g_frameStart;
	*g_frameDelta = frameDelta;

	int result = m_34->slot18(m_38);
	if ((result & 4) != 0)
	{
		__asm
		{
			__emit 0FFh
			__emit 005h
			__emit 0B8h
			__emit 012h
			__emit 02Fh
			__emit 001h
		}
	}
	bfmeGoDC();

	if (*g_frameEnabled != 0)
	{
		long long zero = 0;
		*g_frameStart = *g_frameEnd;
		*g_frameAverage = (double)zero + *g_frameAverage;
		++*g_frameCount;
		if (*g_frameCount > 0x1E)
		{
			*g_frameValue = (double)*g_frameStamp / *g_frameScale *
				*g_frameFactor;
			char buffer[0x28];
			sprintf(buffer, "Avg frame time %4.4f\n",
				*g_frameValue * *g_frameAverage);
			Rva01358EA8(buffer);
			*g_frameAverage = *g_zeroDouble;
			*g_frameCount = 0;
		}
	}

	if ((result & 2) == 0)
		return;
	if (m_E0 < 0 && m_DC < 0)
	{
		m_58 = 1;
		if ((signed char)m_38 >= 0)
		{
			((Rva0040DE00OwnerVtable *)this)->slot59();
			return;
		}

		if ((m_38 & 0x200000) == 0)
			return;

		if (m_10C > 0)
		{
			--m_10C;
			return;
		}

		float value = m_34->slot48() - *g_frameBias;
		if (value >= *g_zeroFloat)
			((Rva0040DE00OwnerVtable *)this)->slot59();
		else
			m_34->slot44(value);
		return;
	}

	if (m_E8 == 0)
	{
		m_E8 = (int)j_000481e4();
	}
	int now = (int)j_000481e4();
	if ((unsigned)(m_E4 + m_DC) < (unsigned)now)
	{
		if ((unsigned)(m_E8 + m_E0) < (unsigned)now)
		{
			m_DC = -1;
			m_E4 = 0;
			m_E8 = 0;
			m_E0 = -1;
		}
	}
}
