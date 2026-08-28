// cl: /DNDEBUG /MD /EHsc
// Field names come from retail's own INI field table joined to upstream's
// parse table on the key: retail supplies every offset, upstream only the
// word. The offsets were derived from this class's declaration sequence and
// type sizes, never read out of the old placeholder names.
// readable body of ??0OCLUpdateModuleData@@QAE@XZ: Code/GameEngine/Source/GameLogic/Object/Update/OCLUpdate.cpp

// Open-BFME5: OCLUpdateModuleData default ctor.
// Zero order: +0xc, +0x10, +0x8, byte +0x14.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/OCLUpdate.h
class OCLUpdateModuleData
{
public:
	OCLUpdateModuleData();
	virtual ~OCLUpdateModuleData();

private:
	unsigned int m_gap4;
	unsigned int m_ocl;
	unsigned int m_minDelay;
	unsigned int m_maxDelay;
	unsigned char m_isCreateAtEdge;
};

// ??0OCLUpdateModuleData@@QAE@XZ
OCLUpdateModuleData::OCLUpdateModuleData()
{
	m_minDelay = 0;
	m_maxDelay = 0;
	m_ocl = 0;
	m_isCreateAtEdge = 0;
}