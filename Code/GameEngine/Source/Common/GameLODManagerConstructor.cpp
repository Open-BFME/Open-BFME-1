// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

typedef int Int;
typedef float Real;
typedef bool Bool;

struct BfmeStaticGameLODInfo
{
	BfmeStaticGameLODInfo()
		: m_maxParticleCount(2500), m_useShadowVolumes(true),
		  m_useShadowDecals(true), m_useAnisotropic(false),
		  m_usePixelShaders(true), m_useLightMap(true),
		  m_showSoftWaterEdge(true), m_maxTankTrackEdges(100),
		  m_maxTankTrackOpaqueEdges(25), m_maxTankTrackFadeDelay(300000),
		  m_useBuildupScaffolds(true), m_useTreeSway(true),
		  m_grassDrawSkip(true), m_textureReduction(0),
		  m_flag20(true), m_flag21(true), m_showProps(true),
		  m_useHighQualityVideo(true), m_animationDetail(1),
		  m_minParticlePriority(1), m_minParticleSkipPriority(1) {}

	Int m_maxParticleCount;
	Bool m_useShadowVolumes;
	Bool m_useShadowDecals;
	Bool m_useAnisotropic;
	Bool m_usePixelShaders;
	Bool m_useLightMap;
	Bool m_showSoftWaterEdge;
	Int m_maxTankTrackEdges;
	Int m_maxTankTrackOpaqueEdges;
	Int m_maxTankTrackFadeDelay;
	Bool m_useBuildupScaffolds;
	Bool m_useTreeSway;
	Bool m_grassDrawSkip;
	Int m_textureReduction;
	Bool m_flag20;
	Bool m_flag21;
	Bool m_showProps;
	Bool m_useHighQualityVideo;
	Int m_animationDetail;
	Int m_minParticlePriority;
	Int m_minParticleSkipPriority;
};

struct BfmeDynamicGameLODInfo
{
	BfmeDynamicGameLODInfo()
		: m_minFPS(0), m_dynamicParticleSkipMask(0),
		  m_dynamicDebrisSkipMask(0), m_slowDeathScale(1.0f) {}

	Int m_minFPS;
	Int m_dynamicParticleSkipMask;
	Int m_dynamicDebrisSkipMask;
	Real m_slowDeathScale;
};

struct BfmeAudioLODInfo
{
	BfmeAudioLODInfo()
		: m_maximumAmbientStreams(2), m_allowDolby(true),
		  m_allowReverb(true) {}

	Int m_maximumAmbientStreams;
	Bool m_allowDolby;
	Bool m_allowReverb;
};

struct BfmeLODPresetInfo
{
	BfmeLODPresetInfo()
		: m_cpuType(0), m_mhz(1), m_cpuPerfIndex(1.0f),
		  m_videoType(0), m_memory(1), m_unknown14(1),
		  m_width(800), m_height(600) {}

	Int m_cpuType;
	Int m_mhz;
	Real m_cpuPerfIndex;
	Int m_videoType;
	Int m_memory;
	Int m_unknown14;
	Int m_width;
	Int m_height;
};

struct BfmeBenchProfile
{
	BfmeBenchProfile()
		: m_cpuType(0), m_mhz(1), m_intBenchIndex(1.0f),
		  m_floatBenchIndex(1.0f), m_memBenchIndex(1.0f) {}

	Int m_cpuType;
	Int m_mhz;
	Real m_intBenchIndex;
	Real m_floatBenchIndex;
	Real m_memBenchIndex;
};

class GameLODManager
{
public:
	GameLODManager();

	BfmeStaticGameLODInfo m_staticGameLODInfo[6];
	BfmeDynamicGameLODInfo m_dynamicGameLODInfo[5];
	BfmeAudioLODInfo m_audioLODInfo[2];
	BfmeLODPresetInfo m_lodPresets[5][32];
	BfmeBenchProfile m_benchProfiles[16];

	Int m_currentStaticLOD;
	Int m_pendingStaticLOD;
	Int m_currentDynamicLOD;
	Int m_pendingDynamicLOD;
	Int m_numParticleGenerations;
	Int m_dynamicParticleSkipMask;
	Int m_numDebrisGenerations;
	Int m_dynamicDebrisSkipMask;
	Real m_slowDeathScale;
	Int m_minDynamicParticlePriority;
	Int m_minDynamicParticleSkipPriority;
	Bool m_videoPassed;
	Bool m_cpuPassed;
	Bool m_memPassed;
	char m_pad16ef;
	Int m_numLevelPresets[5];
	Int m_numBenchProfiles;
	Int m_idealDetailLevel;
	Int m_videoChipType;
	Int m_field1710;
	Int m_field1714;
	Int m_field1718;
	Int m_cpuFreq;
	Int m_field1720;
	Int m_field1724;
	Int m_field1728;
	Int m_field172c;
	Int m_field1730;
	Int m_reallyLowMHz;
	Int m_audioLowMHz;
};

// ??0GameLODManager@@QAE@XZ
GameLODManager::GameLODManager()
{
	m_currentStaticLOD = -1;
	m_pendingStaticLOD = -1;
	m_currentDynamicLOD = 3;
	m_pendingDynamicLOD = -1;
	m_numParticleGenerations = 0;
	m_dynamicParticleSkipMask = 0;
	m_numDebrisGenerations = 0;
	m_dynamicDebrisSkipMask = 0;
	m_slowDeathScale = 1.0f;
	m_minDynamicParticlePriority = 0;
	m_minDynamicParticleSkipPriority = 0;
	m_videoPassed = false;
	m_cpuPassed = false;
	m_memPassed = false;
	m_numBenchProfiles = 0;
	m_idealDetailLevel = -1;
	m_videoChipType = -1;
	m_field1710 = 12;
	m_field1714 = 0;
	m_field1718 = 0;
	m_cpuFreq = 0;
	m_field1720 = 0;
	m_field1724 = 0;
	m_field1728 = 0;
	m_field172c = 0;
	m_field1730 = 0;
	m_reallyLowMHz = 400;
	m_audioLowMHz = 1500;

	for (Int i = 0; i < 5; ++i)
		m_numLevelPresets[i] = 0;
}


