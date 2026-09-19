// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: clean C++ reconstruction of the retail ModuleData destructor.

class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();
	char *m_data;
};

class RadiusDecalTemplate
{
public:
	~RadiusDecalTemplate() {}

private:
	BFMERetailAsciiString m_name;
	BFMERetailAsciiString m_shadowName;
	unsigned char m_pad[0x28];
};

class Gen_uwm_00017477
{
public:
	~Gen_uwm_00017477();
private:
	unsigned char m_body[0xc];
};

class Gen_uwm_00022d3b
{
public:
	~Gen_uwm_00022d3b();
private:
	unsigned char m_body[0xc];
};

class Gen_uwm_0000513c
{
public:
	~Gen_uwm_0000513c();
private:
	unsigned char m_body[0xc];
};

class Gen_uw_00026ab2
{
public:
	~Gen_uw_00026ab2();
private:
	unsigned char m_body[0xc];
};

class InstantDeathBehaviorModuleDataAllocator
{
public:
	~InstantDeathBehaviorModuleDataAllocator();
private:
	unsigned char m_body[0xc];
};

class ModuleData
{
public:
	virtual ~ModuleData() {}

private:
	unsigned int m_moduleTagNameKey;
};

class InstantDeathDieMuxData
{
private:
	unsigned char m_body[0x2c];
};

class SlowDeathBehaviorModuleData : public ModuleData
{
public:
	virtual ~SlowDeathBehaviorModuleData();

private:
	InstantDeathDieMuxData m_dieMuxData;
	unsigned char m_scalarFields[0x24];
	Gen_uwm_00017477 m_fx[4];
	Gen_uwm_00022d3b m_ocls[4];
	Gen_uwm_0000513c m_weapons[4];
	InstantDeathBehaviorModuleDataAllocator m_extraVectors[4];
	unsigned char m_unownedFields[0x48];
	Gen_uw_00026ab2 m_tail;
	RadiusDecalTemplate m_radius;
	unsigned char m_finalFields[0x0c];
};

// ??1SlowDeathBehaviorModuleData@@UAE@XZ
SlowDeathBehaviorModuleData::~SlowDeathBehaviorModuleData()
{
}
