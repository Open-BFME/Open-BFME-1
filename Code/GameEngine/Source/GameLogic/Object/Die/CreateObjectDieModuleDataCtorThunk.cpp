// cl: /DNDEBUG /MD /EHsc
// readable body of ??0CreateObjectDieModuleData@@: Code/GameEngine/Source/GameLogic/Object/Die/CreateObjectDie.cpp

// Open-BFME5: CreateObjectDieModuleData constructor lifted from retail.

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

class CreateObjectDieOCLName
{
public:
	CreateObjectDieOCLName()
		: m_data(0)
	{
	}

	~CreateObjectDieOCLName();
	void releaseBuffer();

private:
	char *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CreateObjectDie.h
class CreateObjectDieModuleData : public DieModuleData
{
public:
	CreateObjectDieModuleData();
	virtual ~CreateObjectDieModuleData();

private:
	unsigned int m_transferPreviousHealth;
	CreateObjectDieOCLName m_ocl;
};

// ??0CreateObjectDieModuleData@@QAE@XZ
CreateObjectDieModuleData::CreateObjectDieModuleData()
	: DieModuleData(), m_ocl()
{
	m_transferPreviousHealth = 0;
	m_ocl.releaseBuffer();
}
