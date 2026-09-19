// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ParticleUplinkCannonUpdateModuleData dtor.
// Members @+0x08/+0xa0/+0xac/+0xb0.

class ParticleUplinkCannonUpdateModuleDataMemberA
{
public:
	~ParticleUplinkCannonUpdateModuleDataMemberA();
private:
	unsigned char m_pad[4];
};

class ParticleUplinkCannonUpdateModuleDataMemberB
{
public:
	~ParticleUplinkCannonUpdateModuleDataMemberB();
private:
	unsigned char m_pad[4];
};

// Retail destroys this member with a direct call to
// StringBase<char>::releaseBuffer (0x00887940) -- the member is a retail
// AsciiString, not the WWLib Buffer whose own destructor is the 40-byte
// body at 0x009E1E30, so name it the way the other lifted ModuleData
// destructors already do.
class BFMERetailAsciiString
{
public:
	~BFMERetailAsciiString() { releaseBuffer(); }

private:
	void releaseBuffer();
	unsigned char m_pad[4];
};

class ParticleUplinkCannonUpdateModuleDataBase
{
public:
	virtual ~ParticleUplinkCannonUpdateModuleDataBase() {}
private:
	unsigned char m_pad[4];
};

class __declspec(novtable) ParticleUplinkCannonUpdateModuleData
	: public ParticleUplinkCannonUpdateModuleDataBase
{
public:
	virtual ~ParticleUplinkCannonUpdateModuleData();
private:
	ParticleUplinkCannonUpdateModuleDataMemberA m_a;
	unsigned char m_gap1[0x94];
	ParticleUplinkCannonUpdateModuleDataMemberB m_b;
	unsigned char m_gap2[0x8];
	BFMERetailAsciiString m_c;
	BFMERetailAsciiString m_d;
};

// ??1ParticleUplinkCannonUpdateModuleData@@UAE@XZ
ParticleUplinkCannonUpdateModuleData::~ParticleUplinkCannonUpdateModuleData()
{
}
