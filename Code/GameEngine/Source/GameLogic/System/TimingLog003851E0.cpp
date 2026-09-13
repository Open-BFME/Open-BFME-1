// cl: /O2 /DNDEBUG /MD /EHsc
// Retail 0x003851E0, 468 bytes.
// thiscall on the unit-timing state at 0x012F08A0; sole caller is
// GameLogic::startNewGame (0x00395B6B) after the enable-byte test.

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct SYSTEMTIME
{
	unsigned short wYear;
	unsigned short wMonth;
	unsigned short wDayOfWeek;
	unsigned short wDay;
	unsigned short wHour;
	unsigned short wMinute;
	unsigned short wSecond;
	unsigned short wMilliseconds;
};

struct TimingLogGlobalData
{
	unsigned char m_pad000[0x1E];
	unsigned char m_useFpsLimit;
	unsigned char m_pad01F[0x45];
	unsigned char m_useShadowVolumes;
	unsigned char m_useShadowDecals;
	unsigned char m_pad066[0xC8E];
	unsigned char m_unk0CF4;
};

struct TimingLogThingFactory
{
	unsigned char m_pad[8];
	void *m_firstTemplate;
};

class TimingView
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void lookAt(const Coord3D *pos) = 0;
};

struct FILE;

class TimingLog003851E0
{
public:
	void start();

private:
	unsigned char m_enabled;
	unsigned char m_pad01[3];
	void *m_unitName;
	unsigned char m_pad08[4];
	unsigned char m_gotUnit;
	unsigned char m_pad0D[3];
	void *m_curThing;
	unsigned char m_startTiming;
	unsigned char m_pad15[3];
	void *m_timingLog;
	unsigned char m_pad1C[8];
	unsigned int m_unk24;
	unsigned char m_unk28;
	unsigned char m_pad29[0x23];
	unsigned int m_unk4C;
};

extern TimingLogGlobalData *TheWritableGlobalData;
extern TimingLogThingFactory *TheThingFactory;
extern TimingView *TheTacticalView;

void Rva009EBC00(int value);
void rva00889690Set();
void HideControlBar(bool immediate);

extern "C"
{
	__declspec(dllimport) void __stdcall GetLocalTime(SYSTEMTIME *);
	__declspec(dllimport) int __stdcall GetDateFormatA(unsigned long, unsigned long, const SYSTEMTIME *, const char *, char *, int);
	__declspec(dllimport) int __stdcall GetTimeFormatA(unsigned long, unsigned long, const SYSTEMTIME *, const char *, char *, int);
	__declspec(dllimport) FILE *__cdecl fopen(const char *, const char *);
	__declspec(dllimport) int __cdecl fputs(const char *, FILE *);
	__declspec(dllimport) int __cdecl fflush(FILE *);
	char *__cdecl strcpy(char *, const char *);
	char *__cdecl strcat(char *, const char *);
	unsigned int __cdecl strlen(const char *);
}

void TimingLog003851E0::start()
{
	Coord3D thePos;
	SYSTEMTIME now;
	char dateBuf[0x104];
	char fileName[0x104];

	Rva009EBC00(0);
	TheWritableGlobalData->m_unk0CF4 = 0;
	TheWritableGlobalData->m_useFpsLimit = 0;
	TheWritableGlobalData->m_useShadowVolumes = 0;
	TheWritableGlobalData->m_useShadowDecals = 0;
	rva00889690Set();
	HideControlBar(true);

	m_curThing = TheThingFactory->m_firstTemplate;
	m_startTiming = 1;
	m_gotUnit = 0;

	GetLocalTime(&now);
	GetDateFormatA(0x800, 1, &now, 0, dateBuf, 0x104);
	{
		int n = (int)strlen(dateBuf);
		dateBuf[n] = '-';
		++n;
		dateBuf[n] = 0;
		GetTimeFormatA(0x800, 2, &now, 0, dateBuf + n, 0x104 - n);
	}

	if (dateBuf[0])
	{
		char *p = dateBuf;
		do
		{
			if (*p == '/' || *p == ':')
				*p = '_';
		} while (*++p);
	}

	strcpy(fileName, "TimingLog");
	strcat(fileName, dateBuf);
	strcat(fileName, ".csv");

	m_timingLog = fopen(fileName, "w");
	if (m_timingLog)
	{
		fputs("Full,TotalVerts/Skin/Sort,Less Fill,NoParticles,No Spawn-NoPart,Logic,Thing,Model,Kind,Side,DrawCalls All,DrawCalls NoPart-NoSpawn,DrawCalls NoSpawn\n", (FILE *)m_timingLog);
		fflush((FILE *)m_timingLog);
	}

	TheWritableGlobalData->m_useShadowVolumes = 0;
	thePos.x = 50.0f;
	thePos.y = 50.0f;
	thePos.z = 0.0f;
	TheTacticalView->lookAt(&thePos);

	m_unk24 = 0;
	m_unk4C = 0;
	m_unk28 = 1;
}
