// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: CrushDieModuleData constructor lifted from retail.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	Snapshot() {}
	virtual ~Snapshot() {}

private:
	unsigned char m_data[4];
};

class InstantDeathDieMuxData
{
public:
	InstantDeathDieMuxData();

private:
	unsigned char m_data[0x2c];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DieModule.h
class DieModuleData : public Snapshot
{
public:
	DieModuleData() {}
	virtual ~DieModuleData();

private:
	InstantDeathDieMuxData m_dieMuxData;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS
{
public:
	AudioEventRTS();
	~AudioEventRTS();

private:
	unsigned char m_data[0x70];
};

enum CrushType
{
	TOTAL_CRUSH,
	BACK_END_CRUSH,
	FRONT_END_CRUSH,
	NO_CRUSH,
	CRUSH_COUNT
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CrushDie.h
class CrushDieModuleData : public DieModuleData
{
public:
	CrushDieModuleData();
	virtual ~CrushDieModuleData();

private:
	AudioEventRTS m_crushSounds[CRUSH_COUNT];
	int m_crushSoundPercent[CRUSH_COUNT];
};

// ??0CrushDieModuleData@@QAE@XZ
CrushDieModuleData::CrushDieModuleData()
	: DieModuleData()
{
	for (int i = 0; i < CRUSH_COUNT; ++i)
		m_crushSoundPercent[i] = 100;
}
