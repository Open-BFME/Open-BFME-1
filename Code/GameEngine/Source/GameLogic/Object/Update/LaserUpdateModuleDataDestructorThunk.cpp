// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: LaserUpdateModuleData dtor. members @+8/+0xc/+0x14 pin 0x887940.

class LaserUpdateModuleDataMember4
{
public:
	~LaserUpdateModuleDataMember4();
private:
	unsigned char m_pad[4];
};

class LaserUpdateModuleDataMember8
{
public:
	~LaserUpdateModuleDataMember8();
private:
	unsigned char m_pad[8];
};

class LaserUpdateModuleDataBase
{
public:
	virtual ~LaserUpdateModuleDataBase() {}
private:
	unsigned char m_pad[0x4];
};

class __declspec(novtable) LaserUpdateModuleData : public LaserUpdateModuleDataBase
{
public:
	virtual ~LaserUpdateModuleData();
private:
	LaserUpdateModuleDataMember4 m_a;
	LaserUpdateModuleDataMember8 m_b;
	LaserUpdateModuleDataMember4 m_c;
};

// ??1LaserUpdateModuleData@@UAE@XZ
LaserUpdateModuleData::~LaserUpdateModuleData()
{
}
