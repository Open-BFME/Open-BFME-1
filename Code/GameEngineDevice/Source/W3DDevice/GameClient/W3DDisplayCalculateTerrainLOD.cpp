// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// readable body of ?calculateTerrainLOD@W3DDisplay@@IAEXXZ: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplay.cpp
// TU-local layouts because the real W3DDisplay/GlobalData headers carry ZH
// vtable/field offsets that drift from BFME's compiled layout for this body.

typedef int Int;
typedef __int64 Int64;

extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(Int64 *counter);
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceFrequency(Int64 *freq);

class Vector3 { public: float X, Y, Z; Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {} };

enum WW3DErrorType { WW3D_ERROR_OK };

class WW3D
{
public:
	static WW3DErrorType Begin_Render(bool clear, bool clearz, const Vector3 &color, float dest_alpha = 0.0f, void (*network_callback)(void) = 0);
	static WW3DErrorType End_Render(bool flip_frame = true);
};

class RTS3DScene;

#define BFME_W3DDISPLAY_SLOT(n) virtual void slot##n(void);
class __declspec(novtable) W3DDisplay
{
public:
	BFME_W3DDISPLAY_SLOT(00) BFME_W3DDISPLAY_SLOT(01) BFME_W3DDISPLAY_SLOT(02) BFME_W3DDISPLAY_SLOT(03)
	BFME_W3DDISPLAY_SLOT(04) BFME_W3DDISPLAY_SLOT(05) BFME_W3DDISPLAY_SLOT(06) BFME_W3DDISPLAY_SLOT(07)
	BFME_W3DDISPLAY_SLOT(08) BFME_W3DDISPLAY_SLOT(09) BFME_W3DDISPLAY_SLOT(10) BFME_W3DDISPLAY_SLOT(11)
	BFME_W3DDISPLAY_SLOT(12) BFME_W3DDISPLAY_SLOT(13) BFME_W3DDISPLAY_SLOT(14) BFME_W3DDISPLAY_SLOT(15)
	BFME_W3DDISPLAY_SLOT(16) BFME_W3DDISPLAY_SLOT(17) BFME_W3DDISPLAY_SLOT(18) BFME_W3DDISPLAY_SLOT(19)
	BFME_W3DDISPLAY_SLOT(20) BFME_W3DDISPLAY_SLOT(21) BFME_W3DDISPLAY_SLOT(22) BFME_W3DDISPLAY_SLOT(23)
	BFME_W3DDISPLAY_SLOT(24) BFME_W3DDISPLAY_SLOT(25) BFME_W3DDISPLAY_SLOT(26) BFME_W3DDISPLAY_SLOT(27)
	BFME_W3DDISPLAY_SLOT(28) BFME_W3DDISPLAY_SLOT(29) BFME_W3DDISPLAY_SLOT(30)
	virtual void drawViews(void);   // BFME vtable +0x7c
	virtual void updateViews(void); // BFME vtable +0x80

	static RTS3DScene *m_3DScene;

protected:
	void calculateTerrainLOD(void);
};
#undef BFME_W3DDISPLAY_SLOT

#define BFME_TERRAIN_SLOT(n) virtual void tslot##n(void);
class __declspec(novtable) Rva006E8E60TerrainAbi
{
public:
	BFME_TERRAIN_SLOT(000) BFME_TERRAIN_SLOT(001) BFME_TERRAIN_SLOT(002) BFME_TERRAIN_SLOT(003)
	BFME_TERRAIN_SLOT(004) BFME_TERRAIN_SLOT(005) BFME_TERRAIN_SLOT(006) BFME_TERRAIN_SLOT(007)
	BFME_TERRAIN_SLOT(008) BFME_TERRAIN_SLOT(009) BFME_TERRAIN_SLOT(010) BFME_TERRAIN_SLOT(011)
	BFME_TERRAIN_SLOT(012) BFME_TERRAIN_SLOT(013) BFME_TERRAIN_SLOT(014) BFME_TERRAIN_SLOT(015)
	BFME_TERRAIN_SLOT(016) BFME_TERRAIN_SLOT(017) BFME_TERRAIN_SLOT(018) BFME_TERRAIN_SLOT(019)
	BFME_TERRAIN_SLOT(020) BFME_TERRAIN_SLOT(021) BFME_TERRAIN_SLOT(022) BFME_TERRAIN_SLOT(023)
	BFME_TERRAIN_SLOT(024) BFME_TERRAIN_SLOT(025) BFME_TERRAIN_SLOT(026) BFME_TERRAIN_SLOT(027)
	BFME_TERRAIN_SLOT(028) BFME_TERRAIN_SLOT(029) BFME_TERRAIN_SLOT(030) BFME_TERRAIN_SLOT(031)
	BFME_TERRAIN_SLOT(032) BFME_TERRAIN_SLOT(033) BFME_TERRAIN_SLOT(034) BFME_TERRAIN_SLOT(035)
	BFME_TERRAIN_SLOT(036) BFME_TERRAIN_SLOT(037) BFME_TERRAIN_SLOT(038) BFME_TERRAIN_SLOT(039)
	BFME_TERRAIN_SLOT(040) BFME_TERRAIN_SLOT(041) BFME_TERRAIN_SLOT(042) BFME_TERRAIN_SLOT(043)
	BFME_TERRAIN_SLOT(044) BFME_TERRAIN_SLOT(045) BFME_TERRAIN_SLOT(046) BFME_TERRAIN_SLOT(047)
	BFME_TERRAIN_SLOT(048) BFME_TERRAIN_SLOT(049) BFME_TERRAIN_SLOT(050) BFME_TERRAIN_SLOT(051)
	BFME_TERRAIN_SLOT(052) BFME_TERRAIN_SLOT(053) BFME_TERRAIN_SLOT(054) BFME_TERRAIN_SLOT(055)
	BFME_TERRAIN_SLOT(056) BFME_TERRAIN_SLOT(057) BFME_TERRAIN_SLOT(058) BFME_TERRAIN_SLOT(059)
	BFME_TERRAIN_SLOT(060) BFME_TERRAIN_SLOT(061) BFME_TERRAIN_SLOT(062) BFME_TERRAIN_SLOT(063)
	BFME_TERRAIN_SLOT(064) BFME_TERRAIN_SLOT(065) BFME_TERRAIN_SLOT(066) BFME_TERRAIN_SLOT(067)
	BFME_TERRAIN_SLOT(068) BFME_TERRAIN_SLOT(069) BFME_TERRAIN_SLOT(070) BFME_TERRAIN_SLOT(071)
	BFME_TERRAIN_SLOT(072) BFME_TERRAIN_SLOT(073) BFME_TERRAIN_SLOT(074) BFME_TERRAIN_SLOT(075)
	BFME_TERRAIN_SLOT(076) BFME_TERRAIN_SLOT(077) BFME_TERRAIN_SLOT(078) BFME_TERRAIN_SLOT(079)
	BFME_TERRAIN_SLOT(080) BFME_TERRAIN_SLOT(081) BFME_TERRAIN_SLOT(082) BFME_TERRAIN_SLOT(083)
	BFME_TERRAIN_SLOT(084) BFME_TERRAIN_SLOT(085) BFME_TERRAIN_SLOT(086) BFME_TERRAIN_SLOT(087)
	BFME_TERRAIN_SLOT(088) BFME_TERRAIN_SLOT(089) BFME_TERRAIN_SLOT(090) BFME_TERRAIN_SLOT(091)
	BFME_TERRAIN_SLOT(092) BFME_TERRAIN_SLOT(093) BFME_TERRAIN_SLOT(094) BFME_TERRAIN_SLOT(095)
	BFME_TERRAIN_SLOT(096) BFME_TERRAIN_SLOT(097) BFME_TERRAIN_SLOT(098) BFME_TERRAIN_SLOT(099)
	BFME_TERRAIN_SLOT(100) BFME_TERRAIN_SLOT(101) BFME_TERRAIN_SLOT(102) BFME_TERRAIN_SLOT(103)
	BFME_TERRAIN_SLOT(104) BFME_TERRAIN_SLOT(105) BFME_TERRAIN_SLOT(106) BFME_TERRAIN_SLOT(107)
	BFME_TERRAIN_SLOT(108) BFME_TERRAIN_SLOT(109) BFME_TERRAIN_SLOT(110) BFME_TERRAIN_SLOT(111)
	BFME_TERRAIN_SLOT(112) BFME_TERRAIN_SLOT(113) BFME_TERRAIN_SLOT(114) BFME_TERRAIN_SLOT(115)
	BFME_TERRAIN_SLOT(116) BFME_TERRAIN_SLOT(117) BFME_TERRAIN_SLOT(118) BFME_TERRAIN_SLOT(119)
	BFME_TERRAIN_SLOT(120) BFME_TERRAIN_SLOT(121) BFME_TERRAIN_SLOT(122) BFME_TERRAIN_SLOT(123)
	BFME_TERRAIN_SLOT(124) BFME_TERRAIN_SLOT(125) BFME_TERRAIN_SLOT(126) BFME_TERRAIN_SLOT(127)
	BFME_TERRAIN_SLOT(128) BFME_TERRAIN_SLOT(129) BFME_TERRAIN_SLOT(130) BFME_TERRAIN_SLOT(131)
	BFME_TERRAIN_SLOT(132) BFME_TERRAIN_SLOT(133) BFME_TERRAIN_SLOT(134) BFME_TERRAIN_SLOT(135)
	virtual void adjustTerrainLOD(int adj); // BFME vtable +0x220
};
#undef BFME_TERRAIN_SLOT

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
struct GlobalData
{
	char m_unknown[0x54];
	int m_terrainLOD;
	char m_unknown58[4];
	int m_terrainLODTargetTimeMS;
};

extern GlobalData *TheWritableGlobalData;
extern Rva006E8E60TerrainAbi *TheTerrainRenderObject;

void W3DRadarResetLock(void);
char bfmeUnlock1179(void);

class W3DDisplayRadarResetGuard
{
public:
	W3DDisplayRadarResetGuard(void) { W3DRadarResetLock(); }
	~W3DDisplayRadarResetGuard(void) { bfmeUnlock1179(); }
};

typedef int (__stdcall *W3DDisplayQueryCounterProc)(Int64 *);

void W3DDisplay::calculateTerrainLOD(void)
{
	const Int NUM_SAMPLES = 20;
	const Int NUM_TO_DISCARD = 5;

	Int64 freq64;
	QueryPerformanceFrequency(&freq64);
	W3DDisplayQueryCounterProc queryCounter =
		reinterpret_cast<W3DDisplayQueryCounterProc>(QueryPerformanceCounter);
	float maxTimeLimit = TheWritableGlobalData->m_terrainLODTargetTimeMS / 1000.0f;
	int goodLOD = 1;
	int curLOD = 8;
	Int count = 0;
	float frameTime = 0;

	do
	{
		Int i;
		float timeForFrame = 0;
		frameTime = 0;
		switch (curLOD)
		{
			default: curLOD = 0; break;
			case 8: curLOD = 7; break;
			case 7: curLOD = 6; break;
			case 3: curLOD = 0; break;
			case 6: curLOD = 3; break;
		}
		if (curLOD == 0)
			break;

		TheWritableGlobalData->m_terrainLOD = curLOD;
		*reinterpret_cast<volatile unsigned char *>(reinterpret_cast<unsigned char *>(W3DDisplay::m_3DScene) + 0x128) = 1;
		TheTerrainRenderObject->adjustTerrainLOD(0);

		volatile double frequency = (double)freq64;

		for (i = 0; i < NUM_SAMPLES; i++)
		{
			Int64 startTime64;
			queryCounter(&startTime64);
			updateViews();
			{
				W3DDisplayRadarResetGuard guard;
				if ((unsigned char)WW3D::Begin_Render(true, true, Vector3(0.0f, 0.0f, 0.0f)) == 1)
				{
					drawViews();
					WW3D::End_Render(true);
				}
				Int64 time64;
				queryCounter(&time64);
				timeForFrame = (float)((double)(time64 - startTime64) / frequency);
				if (i >= NUM_TO_DISCARD)
				{
					frameTime += timeForFrame;
					if (i > NUM_TO_DISCARD + 1 &&
						(timeForFrame / ((i + 1) - NUM_TO_DISCARD)) > 2 * maxTimeLimit)
					{
						i++;
						break;
					}
				}
			}
		}
		frameTime /= (i - NUM_TO_DISCARD);
		count++;
		if (frameTime < maxTimeLimit && goodLOD < curLOD)
			goodLOD = curLOD;
		if (frameTime < maxTimeLimit)
			break;
	} while (count < 10);

	TheWritableGlobalData->m_terrainLOD = goodLOD;
	*reinterpret_cast<volatile unsigned char *>(reinterpret_cast<unsigned char *>(W3DDisplay::m_3DScene) + 0x128) = 0;
	TheTerrainRenderObject->adjustTerrainLOD(0);
}
