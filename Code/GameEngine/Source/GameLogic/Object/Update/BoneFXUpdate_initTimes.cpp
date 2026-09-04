// cl: /DNDEBUG /MD /EHs-c- /Oi
// BoneFXUpdateInitTimesShim::initTimes — ILT target of BoneFXUpdate::initTimes,
// retail 0x00288540 / 614B.
// Dump sibling of awardInitialCaptureBonus in Code/gen_asm/d_0027db50.asm.
// upstream: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/BoneFXUpdate.cpp

extern "C" int __cdecl memcmp(const void *buf1, const void *buf2, unsigned int count);
#pragma intrinsic(memcmp)

struct AsciiStringHeader
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	char data[1];
};

class AsciiString
{
public:
	static const AsciiString TheEmptyString;

	int compare(const AsciiString &stringSrc) const
	{
		int thatLen = stringSrc.m_data ? stringSrc.m_data->length : 0;
		const char *thatData = stringSrc.m_data ? &stringSrc.m_data->data[0] : (const char *)"";
		int thisLen = m_data ? m_data->length : 0;
		const char *thisData = m_data ? &m_data->data[0] : (const char *)"";
		int n = thisLen < thatLen ? thisLen : thatLen;
		int c = memcmp(thisData, thatData, n);
		if (c != 0)
			return c;
		return thisLen - thatLen;
	}

private:
	AsciiStringHeader *m_data;
};

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

class GameLogic
{
public:
	unsigned int getFrame() const { return m_frame; }

private:
	char m_pad[0x3C];
	unsigned int m_frame;
};

GameLogic *TheGameLogic;

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
	int now = TheGameLogic->getFrame();

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
