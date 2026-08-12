// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: CreateObjectDieModuleData constructor lifted from retail.

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
