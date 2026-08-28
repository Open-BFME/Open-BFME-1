// cl: /DNDEBUG /MD /EHsc
// Field names come from retail's own INI field table joined to upstream's
// parse table on the key: retail supplies every offset, upstream only the
// word. The offsets were derived from this class's declaration sequence and
// type sizes, never read out of the old placeholder names.

// Open-BFME5: HeightDieUpdateModuleData default ctor.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/HeightDieUpdate.h
class HeightDieUpdateModuleData
{
public:
	HeightDieUpdateModuleData();
	virtual ~HeightDieUpdateModuleData();

private:
	unsigned int m_gap4;
	unsigned int m_targetHeightAboveTerrain;
	unsigned char m_targetHeightIncludesStructures;
	unsigned char m_onlyWhenMovingDown;
	unsigned char m_pad0e;
	unsigned char m_pad0f;
	float m_destroyAttachedParticlesAtHeight;
	unsigned char m_snapToGroundOnDeath;
	unsigned char m_pad15;
	unsigned char m_pad16;
	unsigned char m_pad17;
	unsigned int m_initialDelay;
};

// ??0HeightDieUpdateModuleData@@QAE@XZ
HeightDieUpdateModuleData::HeightDieUpdateModuleData()
{
	m_targetHeightAboveTerrain = 0;
	m_targetHeightIncludesStructures = 0;
	m_onlyWhenMovingDown = 0;
	m_destroyAttachedParticlesAtHeight = -1.0f;
	m_snapToGroundOnDeath = 0;
	m_initialDelay = 0;
}