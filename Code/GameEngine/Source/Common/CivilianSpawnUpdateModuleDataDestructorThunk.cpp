// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: CivilianSpawnUpdateModuleData dtor. Buffer @+0xc and member @+0x14.

class Buffer
{
public:
	~Buffer();

private:
	unsigned char m_pad[8];
};

class CivilianSpawnUpdateModuleDataMember
{
public:
	~CivilianSpawnUpdateModuleDataMember();

private:
	unsigned char m_pad[0xc];
};

class CivilianSpawnUpdateModuleDataBase
{
public:
	virtual ~CivilianSpawnUpdateModuleDataBase() {}

private:
	unsigned char m_pad[8];
};

class __declspec(novtable) CivilianSpawnUpdateModuleData : public CivilianSpawnUpdateModuleDataBase
{
public:
	virtual ~CivilianSpawnUpdateModuleData();

private:
	Buffer m_buffer;
	CivilianSpawnUpdateModuleDataMember m_member;
};

// ??1CivilianSpawnUpdateModuleData@@UAE@XZ
CivilianSpawnUpdateModuleData::~CivilianSpawnUpdateModuleData()
{
}
