// ?calculateTerrainLOD@W3DDisplay@@IAEXXZ
// partial score=0.86 date=2026-09-09
// ?calculateTerrainLOD@W3DDisplay@@IAEXXZ
// Retail RVA 0x006E8E60, full boundary 556 bytes.
// This is the complete semantic reconstruction attempted in the owning TU.
// The matched caller is ?bfmeGo1087A@BfmeQ1087@@QAEXXZ at 0x006E9190;
// its retail body performs the W3DDisplay terrain-LOD dynamic call through
// the existing 0x00031F4D thunk.  The proper source identity is
// W3DDisplay::calculateTerrainLOD, not the provisional caller facade.
//
// The two ABI shims are TU-local because the imported Zero Hour declarations
// have different vtable layouts.  Retail uses W3DDisplay slots +0x7c/+0x80,
// terrain slot +0x220, writable-global fields +0x54/+0x5c, and scene byte
// +0x128.  The guard models the W3DRadarResetLock/bfmeUnlock1179 lifetime
// visible in the retail EH cleanup.  The remaining compiler mismatch is the
// stack/register layout around the QPC loop; no retail bytes are lifted.

#define BFME_LOD_DISPLAY_SLOT(n) virtual void bfmeLodDisplaySlot##n(void) = 0;
class __declspec(novtable) Rva006E8E60DisplayAbi
{
public:
	BFME_LOD_DISPLAY_SLOT(00) BFME_LOD_DISPLAY_SLOT(01)
	BFME_LOD_DISPLAY_SLOT(02) BFME_LOD_DISPLAY_SLOT(03)
	BFME_LOD_DISPLAY_SLOT(04) BFME_LOD_DISPLAY_SLOT(05)
	BFME_LOD_DISPLAY_SLOT(06) BFME_LOD_DISPLAY_SLOT(07)
	BFME_LOD_DISPLAY_SLOT(08) BFME_LOD_DISPLAY_SLOT(09)
	BFME_LOD_DISPLAY_SLOT(10) BFME_LOD_DISPLAY_SLOT(11)
	BFME_LOD_DISPLAY_SLOT(12) BFME_LOD_DISPLAY_SLOT(13)
	BFME_LOD_DISPLAY_SLOT(14) BFME_LOD_DISPLAY_SLOT(15)
	BFME_LOD_DISPLAY_SLOT(16) BFME_LOD_DISPLAY_SLOT(17)
	BFME_LOD_DISPLAY_SLOT(18) BFME_LOD_DISPLAY_SLOT(19)
	BFME_LOD_DISPLAY_SLOT(20) BFME_LOD_DISPLAY_SLOT(21)
	BFME_LOD_DISPLAY_SLOT(22) BFME_LOD_DISPLAY_SLOT(23)
	BFME_LOD_DISPLAY_SLOT(24) BFME_LOD_DISPLAY_SLOT(25)
	BFME_LOD_DISPLAY_SLOT(26) BFME_LOD_DISPLAY_SLOT(27)
	BFME_LOD_DISPLAY_SLOT(28) BFME_LOD_DISPLAY_SLOT(29)
	BFME_LOD_DISPLAY_SLOT(30)
	virtual void drawViews(void) = 0; // BFME vtable +0x7c
	virtual void updateViews(void) = 0; // BFME vtable +0x80
};

#define BFME_LOD_TERRAIN_SLOT(n) virtual void bfmeLodTerrainSlot##n(void) = 0;
class __declspec(novtable) Rva006E8E60TerrainAbi
{
public:
	BFME_LOD_TERRAIN_SLOT(000) BFME_LOD_TERRAIN_SLOT(001)
	BFME_LOD_TERRAIN_SLOT(002) BFME_LOD_TERRAIN_SLOT(003)
	BFME_LOD_TERRAIN_SLOT(004) BFME_LOD_TERRAIN_SLOT(005)
	BFME_LOD_TERRAIN_SLOT(006) BFME_LOD_TERRAIN_SLOT(007)
	BFME_LOD_TERRAIN_SLOT(008) BFME_LOD_TERRAIN_SLOT(009)
	BFME_LOD_TERRAIN_SLOT(010) BFME_LOD_TERRAIN_SLOT(011)
	BFME_LOD_TERRAIN_SLOT(012) BFME_LOD_TERRAIN_SLOT(013)
	BFME_LOD_TERRAIN_SLOT(014) BFME_LOD_TERRAIN_SLOT(015)
	BFME_LOD_TERRAIN_SLOT(016) BFME_LOD_TERRAIN_SLOT(017)
	BFME_LOD_TERRAIN_SLOT(018) BFME_LOD_TERRAIN_SLOT(019)
	BFME_LOD_TERRAIN_SLOT(020) BFME_LOD_TERRAIN_SLOT(021)
	BFME_LOD_TERRAIN_SLOT(022) BFME_LOD_TERRAIN_SLOT(023)
	BFME_LOD_TERRAIN_SLOT(024) BFME_LOD_TERRAIN_SLOT(025)
	BFME_LOD_TERRAIN_SLOT(026) BFME_LOD_TERRAIN_SLOT(027)
	BFME_LOD_TERRAIN_SLOT(028) BFME_LOD_TERRAIN_SLOT(029)
	BFME_LOD_TERRAIN_SLOT(030) BFME_LOD_TERRAIN_SLOT(031)
	BFME_LOD_TERRAIN_SLOT(032) BFME_LOD_TERRAIN_SLOT(033)
	BFME_LOD_TERRAIN_SLOT(034) BFME_LOD_TERRAIN_SLOT(035)
	BFME_LOD_TERRAIN_SLOT(036) BFME_LOD_TERRAIN_SLOT(037)
	BFME_LOD_TERRAIN_SLOT(038) BFME_LOD_TERRAIN_SLOT(039)
	BFME_LOD_TERRAIN_SLOT(040) BFME_LOD_TERRAIN_SLOT(041)
	BFME_LOD_TERRAIN_SLOT(042) BFME_LOD_TERRAIN_SLOT(043)
	BFME_LOD_TERRAIN_SLOT(044) BFME_LOD_TERRAIN_SLOT(045)
	BFME_LOD_TERRAIN_SLOT(046) BFME_LOD_TERRAIN_SLOT(047)
	BFME_LOD_TERRAIN_SLOT(048) BFME_LOD_TERRAIN_SLOT(049)
	BFME_LOD_TERRAIN_SLOT(050) BFME_LOD_TERRAIN_SLOT(051)
	BFME_LOD_TERRAIN_SLOT(052) BFME_LOD_TERRAIN_SLOT(053)
	BFME_LOD_TERRAIN_SLOT(054) BFME_LOD_TERRAIN_SLOT(055)
	BFME_LOD_TERRAIN_SLOT(056) BFME_LOD_TERRAIN_SLOT(057)
	BFME_LOD_TERRAIN_SLOT(058) BFME_LOD_TERRAIN_SLOT(059)
	BFME_LOD_TERRAIN_SLOT(060) BFME_LOD_TERRAIN_SLOT(061)
	BFME_LOD_TERRAIN_SLOT(062) BFME_LOD_TERRAIN_SLOT(063)
	BFME_LOD_TERRAIN_SLOT(064) BFME_LOD_TERRAIN_SLOT(065)
	BFME_LOD_TERRAIN_SLOT(066) BFME_LOD_TERRAIN_SLOT(067)
	BFME_LOD_TERRAIN_SLOT(068) BFME_LOD_TERRAIN_SLOT(069)
	BFME_LOD_TERRAIN_SLOT(070) BFME_LOD_TERRAIN_SLOT(071)
	BFME_LOD_TERRAIN_SLOT(072) BFME_LOD_TERRAIN_SLOT(073)
	BFME_LOD_TERRAIN_SLOT(074) BFME_LOD_TERRAIN_SLOT(075)
	BFME_LOD_TERRAIN_SLOT(076) BFME_LOD_TERRAIN_SLOT(077)
	BFME_LOD_TERRAIN_SLOT(078) BFME_LOD_TERRAIN_SLOT(079)
	BFME_LOD_TERRAIN_SLOT(080) BFME_LOD_TERRAIN_SLOT(081)
	BFME_LOD_TERRAIN_SLOT(082) BFME_LOD_TERRAIN_SLOT(083)
	BFME_LOD_TERRAIN_SLOT(084) BFME_LOD_TERRAIN_SLOT(085)
	BFME_LOD_TERRAIN_SLOT(086) BFME_LOD_TERRAIN_SLOT(087)
	BFME_LOD_TERRAIN_SLOT(088) BFME_LOD_TERRAIN_SLOT(089)
	BFME_LOD_TERRAIN_SLOT(090) BFME_LOD_TERRAIN_SLOT(091)
	BFME_LOD_TERRAIN_SLOT(092) BFME_LOD_TERRAIN_SLOT(093)
	BFME_LOD_TERRAIN_SLOT(094) BFME_LOD_TERRAIN_SLOT(095)
	BFME_LOD_TERRAIN_SLOT(096) BFME_LOD_TERRAIN_SLOT(097)
	BFME_LOD_TERRAIN_SLOT(098) BFME_LOD_TERRAIN_SLOT(099)
	BFME_LOD_TERRAIN_SLOT(100) BFME_LOD_TERRAIN_SLOT(101)
	BFME_LOD_TERRAIN_SLOT(102) BFME_LOD_TERRAIN_SLOT(103)
	BFME_LOD_TERRAIN_SLOT(104) BFME_LOD_TERRAIN_SLOT(105)
	BFME_LOD_TERRAIN_SLOT(106) BFME_LOD_TERRAIN_SLOT(107)
	BFME_LOD_TERRAIN_SLOT(108) BFME_LOD_TERRAIN_SLOT(109)
	BFME_LOD_TERRAIN_SLOT(110) BFME_LOD_TERRAIN_SLOT(111)
	BFME_LOD_TERRAIN_SLOT(112) BFME_LOD_TERRAIN_SLOT(113)
	BFME_LOD_TERRAIN_SLOT(114) BFME_LOD_TERRAIN_SLOT(115)
	BFME_LOD_TERRAIN_SLOT(116) BFME_LOD_TERRAIN_SLOT(117)
	BFME_LOD_TERRAIN_SLOT(118) BFME_LOD_TERRAIN_SLOT(119)
	BFME_LOD_TERRAIN_SLOT(120) BFME_LOD_TERRAIN_SLOT(121)
	BFME_LOD_TERRAIN_SLOT(122) BFME_LOD_TERRAIN_SLOT(123)
	BFME_LOD_TERRAIN_SLOT(124) BFME_LOD_TERRAIN_SLOT(125)
	BFME_LOD_TERRAIN_SLOT(126) BFME_LOD_TERRAIN_SLOT(127)
	BFME_LOD_TERRAIN_SLOT(128) BFME_LOD_TERRAIN_SLOT(129)
	BFME_LOD_TERRAIN_SLOT(130) BFME_LOD_TERRAIN_SLOT(131)
	BFME_LOD_TERRAIN_SLOT(132) BFME_LOD_TERRAIN_SLOT(133)
	BFME_LOD_TERRAIN_SLOT(134) BFME_LOD_TERRAIN_SLOT(135)
	virtual void adjustTerrainLOD(int adj) = 0; // BFME vtable +0x220
};

#undef BFME_LOD_TERRAIN_SLOT
#undef BFME_LOD_DISPLAY_SLOT

struct Rva006E8E60GlobalData
{
	unsigned char m_pad000[0x54];
	volatile int m_terrainLOD;
	unsigned char m_pad058[4];
	volatile int m_terrainLODTargetTimeMS;
};

typedef int (__stdcall *Rva006E8E60QueryCounterProc)(__int64 *counter);

extern void __cdecl W3DRadarResetLock(void);
extern char __cdecl bfmeUnlock1179(void);

class Rva006E8E60RadarResetGuard
{
public:
	Rva006E8E60RadarResetGuard(void) { W3DRadarResetLock(); }
	~Rva006E8E60RadarResetGuard(void) { bfmeUnlock1179(); }
};

void W3DDisplay::calculateTerrainLOD(void)
{
	const Int NUM_SAMPLES = 20;
	const Int NUM_TO_DISCARD = 5;
	__int64 freq64;
	QueryPerformanceFrequency((LARGE_INTEGER *)&freq64);
	Rva006E8E60QueryCounterProc queryCounter =
		reinterpret_cast<Rva006E8E60QueryCounterProc>(QueryPerformanceCounter);
	float maxTimeLimit = reinterpret_cast<volatile Rva006E8E60GlobalData *>(TheWritableGlobalData)->m_terrainLODTargetTimeMS *
		*(volatile float *)0x010766EC;
	Int goodLOD = TERRAIN_LOD_MIN;
	Int curLOD = TERRAIN_LOD_AUTOMATIC;
	Int count = 0;
	float frameTime = 0;
	double frequency = (double)freq64;
	do {
		Int i;
		float timeForFrame = 0;
		frameTime = 0;
		switch(curLOD) {
			default: curLOD = TERRAIN_LOD_DISABLE; break;
			case TERRAIN_LOD_AUTOMATIC: curLOD = TERRAIN_LOD_MAX; break;
			case TERRAIN_LOD_MAX: curLOD = TERRAIN_LOD_NO_WATER; break;
			case TERRAIN_LOD_HALF_CLOUDS: curLOD = TERRAIN_LOD_DISABLE; break;
			case TERRAIN_LOD_NO_WATER: curLOD = TERRAIN_LOD_HALF_CLOUDS; break;
		}
		if (curLOD == TERRAIN_LOD_DISABLE) break;
		reinterpret_cast<volatile Rva006E8E60GlobalData *>(TheWritableGlobalData)->m_terrainLOD = curLOD;
		*reinterpret_cast<volatile unsigned char *>(reinterpret_cast<unsigned char *>(m_3DScene) + 0x128) = 1;
		reinterpret_cast<Rva006E8E60TerrainAbi *>(TheTerrainRenderObject)->adjustTerrainLOD(0);
		for (i = 0; i < NUM_SAMPLES; i++) {
			__int64 startTime64;
			queryCounter(&startTime64);
			reinterpret_cast<Rva006E8E60DisplayAbi *>(this)->updateViews();
			{
				Rva006E8E60RadarResetGuard radarResetGuard;
				if ((unsigned char)WW3D::Begin_Render(true, true, Vector3(0.0f, 0.0f, 0.0f)) == 1) {
					reinterpret_cast<Rva006E8E60DisplayAbi *>(this)->drawViews();
					WW3D::End_Render(true);
				}
				__int64 time64;
				queryCounter(&time64);
				timeForFrame = (float)((double)(time64 - startTime64) / frequency);
			}
			if (i >= NUM_TO_DISCARD) {
				frameTime += timeForFrame;
				if (i > NUM_TO_DISCARD + 1 &&
					(timeForFrame / ((i + 1) - NUM_TO_DISCARD)) > 2 * maxTimeLimit) {
					i++;
					break;
				}
			}
		}
		frameTime /= (i - NUM_TO_DISCARD);
		count++;
		if (frameTime < maxTimeLimit && goodLOD < curLOD) goodLOD = curLOD;
		if (frameTime < maxTimeLimit) break;
	} while (count < 10);
	reinterpret_cast<volatile Rva006E8E60GlobalData *>(TheWritableGlobalData)->m_terrainLOD = goodLOD;
	*reinterpret_cast<volatile unsigned char *>(reinterpret_cast<unsigned char *>(m_3DScene) + 0x128) = 0;
	reinterpret_cast<Rva006E8E60TerrainAbi *>(TheTerrainRenderObject)->adjustTerrainLOD(0);
}
