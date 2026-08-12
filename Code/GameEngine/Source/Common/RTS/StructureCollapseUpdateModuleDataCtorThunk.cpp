// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: retail-layout C++ conversion of StructureCollapseUpdateModuleData.

class Snapshot
{
public:
	Snapshot() {}
	virtual ~Snapshot() {}

private:
	unsigned int m_pad;
};

class StructureCollapseBaseData
{
public:
	StructureCollapseBaseData();

private:
	unsigned char m_data[0x2c];
};

class StructureCollapseFXVector
{
public:
	StructureCollapseFXVector();
	~StructureCollapseFXVector();

private:
	unsigned char m_data[0x0c];
};

class StructureCollapseOCLVector
{
public:
	StructureCollapseOCLVector();
	~StructureCollapseOCLVector();

private:
	unsigned char m_data[0x0c];
};

class StructureCollapseUpdateModuleData : public Snapshot
{
public:
	StructureCollapseUpdateModuleData();
	virtual ~StructureCollapseUpdateModuleData();

private:
	StructureCollapseBaseData m_baseData;	// +0x08
	volatile unsigned int m_minCollapseDelay;	// +0x34
	volatile unsigned int m_maxCollapseDelay;	// +0x38
	volatile unsigned int m_minBurstDelay;		// +0x3c
	unsigned int m_maxBurstDelay;			// +0x40
	volatile float m_collapseDamping;		// +0x44
	volatile float m_maxShudder;			// +0x48
	volatile int m_bigBurstFrequency;		// +0x4c
	StructureCollapseFXVector m_fxs[5];	// +0x50
	StructureCollapseOCLVector m_ocls[5]; // +0x8c
	volatile unsigned int m_dieData0;		// +0xc8
	volatile unsigned int m_dieData1;
	volatile unsigned int m_dieData2;
	volatile unsigned int m_dieData3;
	volatile unsigned int m_dieData4;
	volatile unsigned int m_dieData5;
	volatile unsigned int m_dieData6;
	volatile unsigned int m_dieData7;
	volatile unsigned int m_dieData8;
	volatile unsigned int m_dieData9;		// +0xec
	volatile unsigned char m_dieDataFlag;	// +0xf0
	unsigned char m_padF1[3];
	volatile unsigned int m_dieDataTail;	// +0xf4
};

// ??0StructureCollapseUpdateModuleData@@QAE@XZ
StructureCollapseUpdateModuleData::StructureCollapseUpdateModuleData()
{
	m_minCollapseDelay = 0;
	m_maxCollapseDelay = 0;
	m_bigBurstFrequency = 0;
	m_maxShudder = 0.0f;
	m_collapseDamping = 0.0f;
	m_dieDataTail = 0;
	m_minBurstDelay = 9999;
	m_dieDataFlag = 0;
	m_dieData0 = 1;
	m_dieData5 = 1;
	m_dieData1 = 1;
	m_dieData6 = 1;
	m_dieData2 = 1;
	m_dieData7 = 1;
	m_dieData3 = 1;
	m_dieData8 = 1;
	m_dieData4 = 1;
	m_dieData9 = 1;
}
