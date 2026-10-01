// cl: /DNDEBUG /MD /EHs-c- /Oi /Igame/Libraries/Source/WWVegas/WWLib
// BoneFXUpdateInitTimesShim::initTimes — ILT target of BoneFXUpdate::initTimes,
// retail 0x00288540 / 614B.
// Dump sibling of awardInitialCaptureBonus in game/gen_asm/d_0027db50.asm.
// upstream: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/BoneFXUpdate.cpp

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2, unsigned int count);
#pragma intrinsic(memcmp)

struct AsciiStringHeader
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	char data[1];
};

#include "ascii_string.h"

const AsciiString AsciiString::TheEmptyString;

class GameClientRandomVariable
{
public:
	float getValue() const;

private:
	int m_type;
	float m_low;
	float m_high;
};

class GameLogicRandomVariable
{
public:
	float getValue() const;

private:
	int m_type;
	float m_low;
	float m_high;
};

// The retail global is EA's `GameLogic *TheGameLogic`, defined once in
// game/GameEngine/Source/GameLogic/System/GameLogic.cpp. Declare it here with
// that spelling so the linker sees one symbol; the frame field is read through
// this TU-local view of the retail layout.
class GameLogic;

extern GameLogic *TheGameLogic;

struct BoneFXGameLogicView
{
	char m_pad[0x3C];
	unsigned int m_frame;

	unsigned int getFrame() const { return m_frame; }
};

static __forceinline BoneFXGameLogicView *boneFXGameLogic()
{
	return (BoneFXGameLogicView *)TheGameLogic;
}

enum { BONE_FX_MAX_BONES = 8 };
enum { BODYDAMAGETYPE_COUNT = 4 };

struct BoneFXListInfo
{
	AsciiString boneName;
	GameClientRandomVariable gameClientDelay;
	GameLogicRandomVariable gameLogicDelay;
	int onlyOnce;
	void *payload;
};

class BoneFXUpdateModuleData
{
public:
	char m_hdr[0x0C];
	BoneFXListInfo m_fxList[BODYDAMAGETYPE_COUNT][BONE_FX_MAX_BONES];
	int m_damageOCLTypes;
	BoneFXListInfo m_OCL[BODYDAMAGETYPE_COUNT][BONE_FX_MAX_BONES];
	int m_damageParticleTypes;
	BoneFXListInfo m_particleSystem[BODYDAMAGETYPE_COUNT][BONE_FX_MAX_BONES];
};

class BoneFXUpdateInitTimesShim
{
public:
	void initTimes();

	const BoneFXUpdateModuleData *getBoneFXUpdateModuleData() const
	{
		return m_moduleData;
	}

private:
	void *m_vptr;
	const BoneFXUpdateModuleData *m_moduleData;
	char m_beforeFrames[0x2C - 8];
	int m_nextFXFrame[BODYDAMAGETYPE_COUNT][BONE_FX_MAX_BONES];
	int m_nextOCLFrame[BODYDAMAGETYPE_COUNT][BONE_FX_MAX_BONES];
	int m_nextParticleSystemFrame[BODYDAMAGETYPE_COUNT][BONE_FX_MAX_BONES];
	char m_positions[0x62C - 0x1AC];
	int m_curBodyState;
};

void BoneFXUpdateInitTimesShim::initTimes()
{
	int i;
	const BoneFXUpdateModuleData *d = getBoneFXUpdateModuleData();
	int now = boneFXGameLogic()->getFrame();

	for (i = 0; i < BONE_FX_MAX_BONES; ++i) {
		if (d->m_fxList[m_curBodyState][i].boneName.compare(AsciiString::TheEmptyString) != 0) {
			m_nextFXFrame[m_curBodyState][i] = now + (int)d->m_fxList[m_curBodyState][i].gameLogicDelay.getValue();
		} else {
			m_nextFXFrame[m_curBodyState][i] = -1;
		}
		if (d->m_OCL[m_curBodyState][i].boneName.compare(AsciiString::TheEmptyString) != 0) {
			m_nextOCLFrame[m_curBodyState][i] = now + (int)d->m_OCL[m_curBodyState][i].gameLogicDelay.getValue();
		} else {
			m_nextOCLFrame[m_curBodyState][i] = -1;
		}
		if (d->m_particleSystem[m_curBodyState][i].boneName.compare(AsciiString::TheEmptyString) != 0) {
			m_nextParticleSystemFrame[m_curBodyState][i] = now + (int)d->m_particleSystem[m_curBodyState][i].gameClientDelay.getValue();
		} else {
			m_nextParticleSystemFrame[m_curBodyState][i] = -1;
		}
	}
}
