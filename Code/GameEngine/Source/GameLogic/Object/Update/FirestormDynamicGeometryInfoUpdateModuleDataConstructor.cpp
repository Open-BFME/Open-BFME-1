// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: FirestormDynamicGeometryInfoUpdateModuleData ctor.

class FirestormDynamicGeometryInfoUpdateModuleDataBase
{
public:
	FirestormDynamicGeometryInfoUpdateModuleDataBase();
	virtual ~FirestormDynamicGeometryInfoUpdateModuleDataBase();

private:
	unsigned char m_pad[0x60];
};

class FirestormDynamicGeometryInfoUpdateModuleData : public FirestormDynamicGeometryInfoUpdateModuleDataBase
{
public:
	FirestormDynamicGeometryInfoUpdateModuleData();
	virtual ~FirestormDynamicGeometryInfoUpdateModuleData();

private:
	unsigned int m_64;
	unsigned int m_68;
	unsigned int m_6c;
	unsigned int m_70;
	float m_74;
	float m_78;
	float m_7c;
	unsigned int m_80;
};

// ??0FirestormDynamicGeometryInfoUpdateModuleData@@QAE@XZ
FirestormDynamicGeometryInfoUpdateModuleData::FirestormDynamicGeometryInfoUpdateModuleData()
	: FirestormDynamicGeometryInfoUpdateModuleDataBase()
{
	m_64 = 0;
	m_68 = 0;
	m_6c = 0;
	m_70 = 0;
	m_80 = 0;
	m_74 = 100.0f;
	m_78 = 10.0f;
	m_7c = 1.0f;
}
