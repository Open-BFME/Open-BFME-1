// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: MissileAIUpdateModuleData ctor.
// Base 0x64; fields at +64..+7c with -1 at +70.

class MissileAIUpdateModuleDataBase
{
public:
	MissileAIUpdateModuleDataBase();
	virtual ~MissileAIUpdateModuleDataBase();

private:
	unsigned char m_pad[0x60];
};

class MissileAIUpdateModuleData : public MissileAIUpdateModuleDataBase
{
public:
	MissileAIUpdateModuleData();
	virtual ~MissileAIUpdateModuleData();

private:
	unsigned int m_64;
	unsigned int m_68;
	unsigned char m_6c;
	unsigned char m_pad6d[3];
	unsigned int m_70;
	unsigned int m_74;
	unsigned int m_78;
	unsigned int m_7c;
};

// ??0MissileAIUpdateModuleData@@QAE@XZ
MissileAIUpdateModuleData::MissileAIUpdateModuleData()
{
	m_64 = 0;
	m_68 = 0;
	m_6c = 0;
	m_7c = 0;
	m_74 = 0;
	m_78 = 0;
	m_70 = 0xffffffff;
}
