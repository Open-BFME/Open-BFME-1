// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: HordeSiegeEngineContainModuleData dtor.

class HordeSiegeEngineContainModuleDataMemberA
{
public:
	~HordeSiegeEngineContainModuleDataMemberA();
private:
	unsigned char m_pad[0x8];
};

class HordeSiegeEngineContainModuleDataMemberB
{
public:
	~HordeSiegeEngineContainModuleDataMemberB();
private:
	unsigned char m_pad[4];
};

class HordeSiegeEngineContainModuleDataBase
{
public:
	virtual ~HordeSiegeEngineContainModuleDataBase();
private:
	unsigned char m_pad[0x220];
};

class __declspec(novtable) HordeSiegeEngineContainModuleData : public HordeSiegeEngineContainModuleDataBase
{
public:
	virtual ~HordeSiegeEngineContainModuleData();
private:
	HordeSiegeEngineContainModuleDataMemberA m_a;
	HordeSiegeEngineContainModuleDataMemberB m_b;
};

// ??1HordeSiegeEngineContainModuleData@@UAE@XZ
HordeSiegeEngineContainModuleData::~HordeSiegeEngineContainModuleData()
{
}
