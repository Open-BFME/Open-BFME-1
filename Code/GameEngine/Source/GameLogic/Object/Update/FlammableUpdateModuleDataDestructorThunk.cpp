// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: FlammableUpdateModuleData dtor. dual members @+0x18/+0x24.

class FlammableUpdateModuleDataMemberA
{
public:
	~FlammableUpdateModuleDataMemberA();
private:
	unsigned char m_pad[0xc];
};

class FlammableUpdateModuleDataMemberB
{
public:
	~FlammableUpdateModuleDataMemberB();
private:
	unsigned char m_pad[0x4];
};

class FlammableUpdateModuleDataBase
{
public:
	virtual ~FlammableUpdateModuleDataBase() {}
private:
	unsigned char m_pad[0x14];
};

class __declspec(novtable) FlammableUpdateModuleData : public FlammableUpdateModuleDataBase
{
public:
	virtual ~FlammableUpdateModuleData();
private:
	FlammableUpdateModuleDataMemberA m_a;
	FlammableUpdateModuleDataMemberB m_b;
};

// ??1FlammableUpdateModuleData@@UAE@XZ
FlammableUpdateModuleData::~FlammableUpdateModuleData()
{
}
