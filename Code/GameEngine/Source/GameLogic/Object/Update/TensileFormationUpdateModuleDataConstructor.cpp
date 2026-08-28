// cl: /DNDEBUG /MD /EHsc

class BaseModuleData
{
public:
	BaseModuleData();
	virtual ~BaseModuleData();

private:
	unsigned char m_pad[0x60];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/TensileFormationUpdate.h
class TensileFormationUpdateModuleData : public BaseModuleData
{
public:
	TensileFormationUpdateModuleData();
	virtual ~TensileFormationUpdateModuleData();

private:
	unsigned int m_64;
	unsigned int m_68;
	unsigned int m_6c;
};

// ??0TensileFormationUpdateModuleData@@QAE@XZ
TensileFormationUpdateModuleData::TensileFormationUpdateModuleData()
{
	m_64 = 0;
	m_68 = 0;
	m_6c = 0;
}
