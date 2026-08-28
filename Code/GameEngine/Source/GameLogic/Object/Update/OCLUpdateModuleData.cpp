// cl: /DNDEBUG /MD /EHsc
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
	unsigned int m_08;
	unsigned int m_0c;
	unsigned int m_10;
	unsigned char m_14;
};

// ??0OCLUpdateModuleData@@QAE@XZ
OCLUpdateModuleData::OCLUpdateModuleData()
{
	m_0c = 0;
	m_10 = 0;
	m_08 = 0;
	m_14 = 0;
}