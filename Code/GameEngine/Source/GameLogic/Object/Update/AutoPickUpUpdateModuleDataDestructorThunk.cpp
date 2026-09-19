// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: AutoPickUpUpdateModuleData dtor. dual different members SEH.

class AutoPickUpUpdateModuleDataMemberA
{
public:
	~AutoPickUpUpdateModuleDataMemberA();
private:
	unsigned char m_pad[4];
};

class AutoPickUpUpdateModuleDataMemberB
{
public:
	~AutoPickUpUpdateModuleDataMemberB();
private:
	unsigned char m_pad[4];
};

class AutoPickUpUpdateModuleDataBase
{
public:
	virtual ~AutoPickUpUpdateModuleDataBase() {}
private:
	unsigned char m_pad[0x28];
};

class __declspec(novtable) AutoPickUpUpdateModuleData : public AutoPickUpUpdateModuleDataBase
{
public:
	virtual ~AutoPickUpUpdateModuleData();
private:
	AutoPickUpUpdateModuleDataMemberA m_a;
	AutoPickUpUpdateModuleDataMemberB m_b;
};

// ??1AutoPickUpUpdateModuleData@@UAE@XZ
AutoPickUpUpdateModuleData::~AutoPickUpUpdateModuleData()
{
}
