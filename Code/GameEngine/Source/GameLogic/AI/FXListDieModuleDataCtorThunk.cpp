// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: FXListDieModuleData constructor lifted from retail.

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FXListDie.h
class FXListDieModuleData : public DieModuleData
{
public:
	FXListDieModuleData();
	virtual ~FXListDieModuleData();

private:
	unsigned int m_fxList;
	bool m_orientToObject;
};

// ??0FXListDieModuleData@@QAE@XZ
FXListDieModuleData::FXListDieModuleData()
	: DieModuleData()
{
	m_fxList = 0;
	m_orientToObject = true;
}
