// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME: GameLODManager::init, retail 0x0007EEB0, 1074 bytes (RET at
// +0x431, INT3 after).
// readable reference: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/Common/GameLOD.cpp
// donor: Open-BFME-2 73898a9634 Code/GameEngine/Source/Common/GameLODManagerInit.cpp
//
// Identity: ilt_oracle CONFIRMS ?init@GameLODManager@@QAEXXZ at this body, and
// the body loads GameLOD.ini and GameLODPresets.ini, writes Benchmark.txt
// with "BenchProfile = %s %d %f %f %f" and walks the bench profiles exactly as
// Zero Hour's GameLODManager::init does.  BFME 1 differences, all read from
// the retail body: the fixed static detail (+0x16C4) is read from the
// preferences and, when unset, seeded with the ideal level and written back
// under "FixedStaticGameLOD"; an unknown audio LOD also forces the
// benchmark; the custom level applies its preferences through 0x0007C8A0;
// and an unknown audio LOD is derived from the CPU speed against +0x1738,
// saved and pushed to TheAudio.
//
// The INI local is BFME's 0x848-byte INI (the frame is 0x87c with the
// OptionPreferences local below it), the same view VideoPlayerInit.cpp uses.

#include <map>
#include <stdio.h>

#include "string_base.h"
#include "ascii_string.h"

#include "../../Include/Common/ScalarTypes.h"



#include "../../Include/Common/Enums/ChipsetType.h"




#include "../../Include/Common/Enums/CpuType.h"





enum StaticGameLODLevel
{
	STATIC_GAME_LOD_UNKNOWN = -1,
	STATIC_GAME_LOD_LOW = 1,
	STATIC_GAME_LOD_HIGH = 3,
	STATIC_GAME_LOD_CUSTOM = 5
};

enum INILoadType
{
	INI_LOAD_OVERWRITE = 1
};

#define PROFILE_ERROR_LIMIT 0.94f

class Xfer;

class INI
{
public:
	INI();
	~INI();
	void load(AsciiString filename, INILoadType loadType, Xfer *pXfer);

private:
	char m_storage[0x848];
};

// W3DShaderManager.cpp's global forwarder to the static
// W3DShaderManager::testMinimumRequirements (0x00717880); retail calls it
// through ILT 0x0001391C, which ilt_oracle confirms under this name.
Bool testMinimumRequirements(ChipsetType *videoChipType, CpuType *cpuType, Int *cpuFreq,
	Int *numRAM, Real *intBenchIndex, Real *floatBenchIndex, Real *memBenchIndex);

typedef std::map<AsciiString, AsciiString> PreferenceMap;

class UserPreferences : public PreferenceMap
{
public:
	virtual ~UserPreferences();
	virtual Bool write(void);

private:
	AsciiString m_filename;
};

class OptionPreferences : public UserPreferences
{
public:
	OptionPreferences();
	virtual ~OptionPreferences();
	Int getStaticGameDetail(void);
	// ilt_oracle confirms getIdealStaticGameDetail at ILT 0x0000D53A; the
	// body 0x00090900 keeps its ledger placeholder until it is renamed.
	Int rva00090900IdealStaticGameDetail(void);
	Int getFixedStaticGameDetail(void);
	Int getAudioLOD(void);
	void setAudioLOD(Int audioLOD);
};

// 0x0007C8A0 applies the custom detail level's preferences (Zero Hour copies
// them into TheWritableGlobalData inline here); its own name is unrecovered.
class BfmeS1148;
void bfmeGo1148(BfmeS1148 *prefs);

class GlobalData;
extern GlobalData *TheWritableGlobalData;

struct Rva0007EEB0GlobalView
{
	char m_pad000[0xaac];
	Bool m_forceBenchmark;
};

// TheAudio, called through its vtable slot 92 when the audio LOD changes.
class AudioManager
{
public:
#define RVA0007EEB0_SLOTS4(n) virtual void slot##n##a(); virtual void slot##n##b(); virtual void slot##n##c(); virtual void slot##n##d();
	RVA0007EEB0_SLOTS4(0) RVA0007EEB0_SLOTS4(1) RVA0007EEB0_SLOTS4(2) RVA0007EEB0_SLOTS4(3)
	RVA0007EEB0_SLOTS4(4) RVA0007EEB0_SLOTS4(5) RVA0007EEB0_SLOTS4(6) RVA0007EEB0_SLOTS4(7)
	RVA0007EEB0_SLOTS4(8) RVA0007EEB0_SLOTS4(9) RVA0007EEB0_SLOTS4(10) RVA0007EEB0_SLOTS4(11)
	RVA0007EEB0_SLOTS4(12) RVA0007EEB0_SLOTS4(13) RVA0007EEB0_SLOTS4(14) RVA0007EEB0_SLOTS4(15)
	RVA0007EEB0_SLOTS4(16) RVA0007EEB0_SLOTS4(17) RVA0007EEB0_SLOTS4(18) RVA0007EEB0_SLOTS4(19)
	RVA0007EEB0_SLOTS4(20) RVA0007EEB0_SLOTS4(21) RVA0007EEB0_SLOTS4(22)
#undef RVA0007EEB0_SLOTS4
	virtual void audioLODChanged(void);	// slot 92, +0x170
};
extern AudioManager *TheAudio;

// GameLOD.cpp's static CPUNames table (retail 0x012A7418: XX P3 P4 K7 NULL);
// it is file-static there, so this unit reaches it by address.
extern char *g_Va012A7418[];
#define CPUNames g_Va012A7418
extern const char *StaticGameLODNames[];

struct LODPresetInfo
{
	CpuType m_cpuType;
	Int m_mhz;
	char m_pad08[0x20 - 0x08];
};

struct BenchProfile
{
	CpuType m_cpuType;
	Int m_mhz;
	Real m_intBenchIndex;
	Real m_floatBenchIndex;
	Real m_memBenchIndex;
};

class GameLODManager
{
public:
	void init(void);
	const char *getStaticGameLODLevelName(StaticGameLODLevel level) { return StaticGameLODNames[level]; }
	Bool setStaticLODLevel(StaticGameLODLevel level);

	// Zero Hour's refreshCustomStaticLODLevel: ilt_oracle confirms that name
	// at ILT 0x00023DAD; the pinned placeholder is kept until the body
	// 0x0007C1D0 is renamed.
	void rva0007C1D0(void);

private:
	char m_pad0000[0x180];
	LODPresetInfo m_lodPresets[5][32];		// +0x180
	BenchProfile m_benchProfiles[16];		// +0x1580
	Int m_field16C0;
	Int m_field16C4;						// fixed static detail level
	Int m_field16C8;
	Int m_field16CC;						// current audio LOD
	char m_pad16D0[0x16EE - 0x16D0];
	Bool m_memPassed;						// +0x16EE
	char m_pad16EF;
	Int m_numLevelPresets[5];				// +0x16F0
	Int m_numBenchProfiles;					// +0x1704
	StaticGameLODLevel m_idealDetailLevel;	// +0x1708
	char m_pad170C[0x1714 - 0x170C];
	CpuType m_cpuType;						// +0x1714
	Int m_numRAM;							// +0x1718
	Int m_cpuFreq;							// +0x171C
	Real m_intBenchIndex;					// +0x1720
	Real m_floatBenchIndex;
	Real m_memBenchIndex;
	Real m_compositeBenchIndex;				// +0x172C
	char m_pad1730[0x1738 - 0x1730];
	Int m_field1738;						// CPU MHz threshold for the high audio LOD
};

void GameLODManager::init(void)
{
	INI ini;
	ini.load( AsciiString( "Data\\INI\\GameLOD.ini" ), INI_LOAD_OVERWRITE, NULL );
	ini.load( AsciiString( "Data\\INI\\GameLODPresets.ini" ), INI_LOAD_OVERWRITE, NULL );

	rva0007C1D0();

	OptionPreferences optionPref;

	StaticGameLODLevel userSetDetail = (StaticGameLODLevel)optionPref.getStaticGameDetail();

	m_idealDetailLevel = (StaticGameLODLevel)optionPref.rva00090900IdealStaticGameDetail();
	m_field16C4 = optionPref.getFixedStaticGameDetail();
	if (m_field16C4 == STATIC_GAME_LOD_UNKNOWN && m_idealDetailLevel != STATIC_GAME_LOD_UNKNOWN)
	{
		optionPref["FixedStaticGameLOD"] = getStaticGameLODLevelName(m_idealDetailLevel);
		m_field16C4 = m_idealDetailLevel;
	}

	Int audioLOD = optionPref.getAudioLOD();

	testMinimumRequirements( NULL, &m_cpuType, &m_cpuFreq, &m_numRAM, NULL, NULL, NULL );

	if ((Real)(m_numRAM)/(Real)(256*1024*1024) >= PROFILE_ERROR_LIMIT)
		m_memPassed = true;

	if (m_idealDetailLevel == STATIC_GAME_LOD_UNKNOWN || ((Rva0007EEB0GlobalView *)TheWritableGlobalData)->m_forceBenchmark || audioLOD == -1)
	{
		if (m_cpuType == XX || ((Rva0007EEB0GlobalView *)TheWritableGlobalData)->m_forceBenchmark)
		{
			testMinimumRequirements( NULL, NULL, NULL, NULL, &m_intBenchIndex, &m_floatBenchIndex, &m_memBenchIndex );

			if (((Rva0007EEB0GlobalView *)TheWritableGlobalData)->m_forceBenchmark)
			{
				FILE *fp = fopen( "Benchmark.txt", "w" );
				if (fp)
				{
					fprintf( fp, "BenchProfile = %s %d %f %f %f", CPUNames[m_cpuType], m_cpuFreq, m_intBenchIndex, m_floatBenchIndex, m_memBenchIndex );
					fclose( fp );
				}
			}

			m_compositeBenchIndex = m_intBenchIndex + m_floatBenchIndex;

			StaticGameLODLevel currentLevel = STATIC_GAME_LOD_LOW;
			BenchProfile *prof = m_benchProfiles;
			m_cpuType = P3;
			m_cpuFreq = 1000;
			for (Int k = 0; k < m_numBenchProfiles; k++)
			{
				if (m_intBenchIndex/prof->m_intBenchIndex >= PROFILE_ERROR_LIMIT && m_floatBenchIndex/prof->m_floatBenchIndex >= PROFILE_ERROR_LIMIT && m_memBenchIndex/prof->m_memBenchIndex >= PROFILE_ERROR_LIMIT)
				{
					for (Int i = STATIC_GAME_LOD_HIGH; i >= STATIC_GAME_LOD_LOW; i--)
					{
						LODPresetInfo *preset = &m_lodPresets[i][0];
						for (Int j = 0; j < m_numLevelPresets[i]; j++)
						{
							if (prof->m_cpuType == preset->m_cpuType && ((Real)prof->m_mhz/(Real)preset->m_mhz >= PROFILE_ERROR_LIMIT))
							{
								currentLevel = (StaticGameLODLevel)i;
								m_cpuType = prof->m_cpuType;
								m_cpuFreq = prof->m_mhz;
								break;
							}
							preset++;
						}
						if (currentLevel >= i)
							break;
					}
				}
				prof++;
			}
		}
	}

	if (userSetDetail == STATIC_GAME_LOD_CUSTOM)
		bfmeGo1148( (BfmeS1148 *)&optionPref );

	setStaticLODLevel( userSetDetail );

	if (audioLOD == -1)
	{
		audioLOD = m_cpuFreq >= m_field1738;
		optionPref.setAudioLOD( audioLOD );
		optionPref.write();
	}

	if (audioLOD >= 0 && audioLOD < 2 && m_field16CC != audioLOD)
	{
		m_field16CC = audioLOD;
		if (TheAudio)
			TheAudio->audioLODChanged();
	}
}
