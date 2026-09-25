// cl: /DNDEBUG /MD /EHsc
// Open-BFME: GameLODManager::applyStaticLODLevel, retail 0x0007E9B0, 868 bytes.
// readable reference: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/Common/GameLOD.cpp
//
// Identity: setStaticLODLevel (0x0007EDF0, matched in GameLOD.cpp) calls it
// through ILT 0x00036A11. BFME inlines getRecommendedTextureReduction and
// clamps it against the level's own reduction with a const-reference max; the
// out-of-line call is what leaves the recommendation in EAX.

typedef int Int;
typedef unsigned char Bool;

// Names from retail StaticGameLODNames (0x00EA73E4): VeryLow Low Medium High
// UltraHigh Custom.
enum StaticGameLODLevel
{
	STATIC_GAME_LOD_UNKNOWN = -1,
	STATIC_GAME_LOD_VERY_LOW = 0,
	STATIC_GAME_LOD_LOW = 1,
	STATIC_GAME_LOD_MEDIUM = 2,
	STATIC_GAME_LOD_HIGH = 3,
	STATIC_GAME_LOD_ULTRA_HIGH = 4,
	STATIC_GAME_LOD_CUSTOM = 5
};

// 0x30-byte element of GameLODManager::m_staticGameLODInfo; named members are
// the ones the BFME field-parse witness names (tools/name_oracle.py).
struct StaticGameLODInfo
{
	Int m_maxParticleCount;
	Bool m_useShadowVolumes;
	Bool m_useShadowDecals;
	Bool byte_6;
	Bool byte_7;
	Bool m_useLightMap;
	Bool m_showSoftWaterEdge;
	unsigned char m_pad0a[2];
	Int m_maxTankTrackEdges;
	Int m_maxTankTrackOpaqueEdges;
	Int m_maxTankTrackFadeDelay;
	Bool m_useBuildupScaffolds;
	Bool m_useTreeSway;
	Bool byte_1a;
	Bool byte_1b;
	Int m_textureReduction;
	unsigned char byte_20;
	Bool byte_21;
	Bool byte_22;
	Bool byte_23;
	Int dword_24;
	Int dword_28;
	Int dword_2c;
};

struct Rva006C9270GlobalData
{
	unsigned char m_pad00[0x18];
	unsigned char m_field18;
	unsigned char m_pad19[1];
	unsigned char m_field1a;
	unsigned char m_field1b;
	unsigned char m_field1c;
	unsigned char m_field1d;
	unsigned char m_pad1e[1];
	unsigned char m_field1f;
	unsigned char m_pad20[0x08];
	unsigned char m_field28;
	unsigned char m_pad29[0x0f];
	unsigned char m_field38;
	unsigned char m_pad39[0x0b];
	unsigned char m_field44;
	unsigned char m_field45;
	unsigned char m_field46;
	unsigned char m_field47;
	unsigned char m_pad48[0x10];
	unsigned char m_field58;
	unsigned char m_pad59[0x0b];
	unsigned char m_field64;
	unsigned char m_field65;
	unsigned char m_pad66[2];
	Int m_field68;
	unsigned char m_pad6c[0x20];
	unsigned char m_field8c;
	unsigned char m_pad8d[0x167];
	Int m_field1f4;
	Int m_field1f8;
	Int m_field1fc;
	unsigned char m_pad200[0x875];
	unsigned char m_fielda75;
	unsigned char m_padA76[1];
	unsigned char m_fielda77;
	unsigned char m_padA78[0x114];
	Int m_fieldb8c;
	unsigned char m_padB90[0x24];
	Bool m_shellMapOn;
};

extern Rva006C9270GlobalData *TheWritableGlobalData;

class OptionPreferences
{
public:
	OptionPreferences();
	virtual ~OptionPreferences();
	Bool getUnitDecals();
	unsigned char m_preferenceStorage[0x10];
};

// Slots 28-30 follow the Zero Hour twin's TheGameClient calls in order.
class ClientRoot4120
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void adjustLOD(Int value);
	virtual void releaseShadows();
	virtual void allocateShadows();
};

extern ClientRoot4120 *TheGameClient;

// Slots 21-22 follow the Zero Hour twin's TheTerrainVisual calls.
class TerrainVisualDispatch
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20();
	virtual void setTerrainTracksDetail();
	virtual void setShoreLineDetail();
};

extern "C" TerrainVisualDispatch *g_bfmeTerrainVisual;

#define BFME_A1087_SLOT(n) virtual void slot##n();
class BfmeA1087
{
public:
	BFME_A1087_SLOT(0) BFME_A1087_SLOT(1) BFME_A1087_SLOT(2) BFME_A1087_SLOT(3)
	BFME_A1087_SLOT(4) BFME_A1087_SLOT(5) BFME_A1087_SLOT(6) BFME_A1087_SLOT(7)
	BFME_A1087_SLOT(8) BFME_A1087_SLOT(9) BFME_A1087_SLOT(10) BFME_A1087_SLOT(11)
	BFME_A1087_SLOT(12) BFME_A1087_SLOT(13) BFME_A1087_SLOT(14) BFME_A1087_SLOT(15)
	BFME_A1087_SLOT(16) BFME_A1087_SLOT(17) BFME_A1087_SLOT(18) BFME_A1087_SLOT(19)
	BFME_A1087_SLOT(20) BFME_A1087_SLOT(21) BFME_A1087_SLOT(22) BFME_A1087_SLOT(23)
	BFME_A1087_SLOT(24) BFME_A1087_SLOT(25) BFME_A1087_SLOT(26) BFME_A1087_SLOT(27)
	BFME_A1087_SLOT(28) BFME_A1087_SLOT(29) BFME_A1087_SLOT(30) BFME_A1087_SLOT(31)
	BFME_A1087_SLOT(32) BFME_A1087_SLOT(33) BFME_A1087_SLOT(34) BFME_A1087_SLOT(35)
	BFME_A1087_SLOT(36) BFME_A1087_SLOT(37) BFME_A1087_SLOT(38) BFME_A1087_SLOT(39)
	BFME_A1087_SLOT(40) BFME_A1087_SLOT(41) BFME_A1087_SLOT(42) BFME_A1087_SLOT(43)
	BFME_A1087_SLOT(44) BFME_A1087_SLOT(45) BFME_A1087_SLOT(46) BFME_A1087_SLOT(47)
	BFME_A1087_SLOT(48) BFME_A1087_SLOT(49) BFME_A1087_SLOT(50) BFME_A1087_SLOT(51)
	BFME_A1087_SLOT(52) BFME_A1087_SLOT(53) BFME_A1087_SLOT(54) BFME_A1087_SLOT(55)
	BFME_A1087_SLOT(56) BFME_A1087_SLOT(57) BFME_A1087_SLOT(58) BFME_A1087_SLOT(59)
	BFME_A1087_SLOT(60) BFME_A1087_SLOT(61) BFME_A1087_SLOT(62) BFME_A1087_SLOT(63)
	BFME_A1087_SLOT(64) BFME_A1087_SLOT(65) BFME_A1087_SLOT(66) BFME_A1087_SLOT(67)
	BFME_A1087_SLOT(68) BFME_A1087_SLOT(69) BFME_A1087_SLOT(70) BFME_A1087_SLOT(71)
	BFME_A1087_SLOT(72) BFME_A1087_SLOT(73) BFME_A1087_SLOT(74) BFME_A1087_SLOT(75)
	BFME_A1087_SLOT(76) BFME_A1087_SLOT(77) BFME_A1087_SLOT(78) BFME_A1087_SLOT(79)
	BFME_A1087_SLOT(80) BFME_A1087_SLOT(81) BFME_A1087_SLOT(82) BFME_A1087_SLOT(83)
	BFME_A1087_SLOT(84) BFME_A1087_SLOT(85) BFME_A1087_SLOT(86) BFME_A1087_SLOT(87)
	BFME_A1087_SLOT(88) BFME_A1087_SLOT(89) BFME_A1087_SLOT(90) BFME_A1087_SLOT(91)
	BFME_A1087_SLOT(92) BFME_A1087_SLOT(93) BFME_A1087_SLOT(94) BFME_A1087_SLOT(95)
	BFME_A1087_SLOT(96) BFME_A1087_SLOT(97) BFME_A1087_SLOT(98) BFME_A1087_SLOT(99)
	BFME_A1087_SLOT(100) BFME_A1087_SLOT(101) BFME_A1087_SLOT(102) BFME_A1087_SLOT(103)
	BFME_A1087_SLOT(104) BFME_A1087_SLOT(105) BFME_A1087_SLOT(106) BFME_A1087_SLOT(107)
	BFME_A1087_SLOT(108) BFME_A1087_SLOT(109) BFME_A1087_SLOT(110) BFME_A1087_SLOT(111)
	BFME_A1087_SLOT(112) BFME_A1087_SLOT(113) BFME_A1087_SLOT(114) BFME_A1087_SLOT(115)
	BFME_A1087_SLOT(116) BFME_A1087_SLOT(117) BFME_A1087_SLOT(118) BFME_A1087_SLOT(119)
	BFME_A1087_SLOT(120) BFME_A1087_SLOT(121) BFME_A1087_SLOT(122) BFME_A1087_SLOT(123)
	BFME_A1087_SLOT(124) BFME_A1087_SLOT(125) BFME_A1087_SLOT(126) BFME_A1087_SLOT(127)
	BFME_A1087_SLOT(128) BFME_A1087_SLOT(129) BFME_A1087_SLOT(130) BFME_A1087_SLOT(131)
};
#undef BFME_A1087_SLOT

extern BfmeA1087 *g_bfmeA1087;
extern void W3DRadarResetLock();
extern char bfmeUnlock1179();

// Scoped W3DRadarResetLock / bfmeUnlock1179 pair: EH state 1 covers the two
// slot calls and the unlock runs on unwind.
class RadarResetLockScope
{
public:
	RadarResetLockScope() { W3DRadarResetLock(); }
	~RadarResetLockScope() { bfmeUnlock1179(); }
};

extern Int Rva008FD440Get();

template <class T> inline const T &maxOf(const T &a, const T &b)
{
	return a > b ? a : b;
}

class GameLODManager
{
public:
	Int rva0007E0F0();
	void rva0007C1D0();

protected:
	void applyStaticLODLevel(StaticGameLODLevel level);

	Int getRecommendedTextureReduction()
	{
		if (m_idealDetailLevel == STATIC_GAME_LOD_UNKNOWN)
			rva0007E0F0();
		if (!m_memPassed)
			return m_staticGameLODInfo[STATIC_GAME_LOD_VERY_LOW].m_textureReduction;
		return m_staticGameLODInfo[m_pendingStaticLOD].m_textureReduction;
	}

	Bool isReallyLowMHz() const
	{
		return m_cpuFreq < m_reallyLowMHz;
	}

	StaticGameLODInfo m_staticGameLODInfo[6];
	unsigned char m_pad0120[0x16c0 - 0x0120];
	Int m_currentStaticLOD;
	Int m_pendingStaticLOD;
	unsigned char m_pad16c8[0x16e4 - 0x16c8];
	Int m_field16e4;
	Int m_field16e8;
	unsigned char m_pad16ec[2];
	Bool m_memPassed;
	unsigned char m_pad16ef[0x1708 - 0x16ef];
	Int m_idealDetailLevel;
	Int m_field170c;
	unsigned char m_pad1710[0x171c - 0x1710];
	Int m_cpuFreq;
	unsigned char m_pad1720[0x1734 - 0x1720];
	Int m_reallyLowMHz;
};

// ?applyStaticLODLevel@GameLODManager@@IAEXW4StaticGameLODLevel@@@Z
void GameLODManager::applyStaticLODLevel(StaticGameLODLevel level)
{
	StaticGameLODInfo prevLodBackup;
	prevLodBackup.m_useShadowVolumes = 1;
	prevLodBackup.m_useShadowDecals = 1;
	prevLodBackup.m_showSoftWaterEdge = 1;
	if (m_currentStaticLOD != STATIC_GAME_LOD_UNKNOWN)
		prevLodBackup = m_staticGameLODInfo[m_currentStaticLOD];

	if (level == STATIC_GAME_LOD_CUSTOM)
		rva0007C1D0();

	StaticGameLODInfo *lodInfo = &m_staticGameLODInfo[level];
	Int requestedTextureReduction;
	if (level == STATIC_GAME_LOD_CUSTOM)
		requestedTextureReduction = lodInfo->m_textureReduction;
	else
		requestedTextureReduction = maxOf(getRecommendedTextureReduction(), lodInfo->m_textureReduction);

	if (TheWritableGlobalData)
	{
		if (level == STATIC_GAME_LOD_VERY_LOW || level == STATIC_GAME_LOD_LOW)
			TheWritableGlobalData->m_field1d = 0;
		if (level == STATIC_GAME_LOD_VERY_LOW || level == STATIC_GAME_LOD_LOW)
			TheWritableGlobalData->m_fielda75 = 0;
		{
			OptionPreferences options;
			TheWritableGlobalData->m_fielda75 = options.getUnitDecals();
			if (level == STATIC_GAME_LOD_MEDIUM)
				TheWritableGlobalData->m_fielda77 = 1;
			else if (level == STATIC_GAME_LOD_HIGH || level == STATIC_GAME_LOD_ULTRA_HIGH)
				TheWritableGlobalData->m_fielda77 = 0;
		}

		TheWritableGlobalData->m_fieldb8c = lodInfo->m_maxParticleCount;
		TheWritableGlobalData->m_field64 = lodInfo->m_useShadowVolumes;
		TheWritableGlobalData->m_field65 = lodInfo->m_useShadowDecals;

		if (requestedTextureReduction != Rva008FD440Get())
		{
			TheWritableGlobalData->m_field68 = requestedTextureReduction;
			if (TheGameClient)
				TheGameClient->adjustLOD(0);
		}

		if (m_currentStaticLOD == STATIC_GAME_LOD_UNKNOWN
			|| lodInfo->m_useShadowVolumes != prevLodBackup.m_useShadowVolumes
			|| lodInfo->m_useShadowDecals != prevLodBackup.m_useShadowDecals)
		{
			if (TheGameClient)
			{
				TheGameClient->releaseShadows();
				TheGameClient->allocateShadows();
			}
		}

		TheWritableGlobalData->m_field47 = lodInfo->byte_6;
		TheWritableGlobalData->m_field28 = !lodInfo->byte_7;
		m_field170c = lodInfo->dword_24;
		TheWritableGlobalData->m_field38 = lodInfo->m_useLightMap;
		TheWritableGlobalData->m_field44 = lodInfo->m_useLightMap;
		if (lodInfo->m_useLightMap)
		{
			TheWritableGlobalData->m_field45 = 1;
			TheWritableGlobalData->m_field46 = 1;
		}
		else
		{
			TheWritableGlobalData->m_field45 = 1;
			TheWritableGlobalData->m_field46 = 0;
		}
		TheWritableGlobalData->m_field8c = lodInfo->m_showSoftWaterEdge;

		if (m_currentStaticLOD == STATIC_GAME_LOD_UNKNOWN
			|| lodInfo->m_showSoftWaterEdge != prevLodBackup.m_showSoftWaterEdge)
		{
			if (g_bfmeTerrainVisual)
				g_bfmeTerrainVisual->setShoreLineDetail();
		}

		TheWritableGlobalData->m_field1f4 = lodInfo->m_maxTankTrackEdges;
		TheWritableGlobalData->m_field1f8 = lodInfo->m_maxTankTrackOpaqueEdges;
		TheWritableGlobalData->m_field1fc = lodInfo->m_maxTankTrackFadeDelay;
		TheWritableGlobalData->m_field1a = lodInfo->m_useTreeSway;
		TheWritableGlobalData->m_field1b = lodInfo->byte_1a;
		TheWritableGlobalData->m_field1c = !lodInfo->m_useBuildupScaffolds;
		TheWritableGlobalData->m_field58 = lodInfo->byte_21;
		TheWritableGlobalData->m_field18 = lodInfo->byte_22;
		TheWritableGlobalData->m_field1f = lodInfo->byte_23;
		m_field16e4 = lodInfo->dword_28;
		m_field16e8 = lodInfo->dword_2c;

		if (g_bfmeA1087)
		{
			RadarResetLockScope lock;
			g_bfmeA1087->slot130();
			g_bfmeA1087->slot131();
		}
	}

	if (!m_memPassed || isReallyLowMHz())
		TheWritableGlobalData->m_shellMapOn = 0;
	if (g_bfmeTerrainVisual)
		g_bfmeTerrainVisual->setTerrainTracksDetail();
}
