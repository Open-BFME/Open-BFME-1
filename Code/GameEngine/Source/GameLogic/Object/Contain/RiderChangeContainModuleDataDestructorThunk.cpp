// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: RiderChangeContainModuleData dtor multi-member SEH.

class RiderChangeContainModuleDataMemberA {
public:
	~RiderChangeContainModuleDataMemberA();
private:
	unsigned char m_pad[4];
};
class RiderChangeContainModuleDataMemberB {
public:
	~RiderChangeContainModuleDataMemberB();
private:
	unsigned char m_pad[4];
};
class RiderChangeContainModuleDataMemberC {
public:
	~RiderChangeContainModuleDataMemberC();
private:
	unsigned char m_pad[4];
};
class RiderChangeContainModuleDataMemberD {
public:
	~RiderChangeContainModuleDataMemberD();
private:
	unsigned char m_pad[4];
};
class RiderChangeContainModuleDataMemberE {
public:
	~RiderChangeContainModuleDataMemberE();
private:
	unsigned char m_pad[4];
};
class RiderChangeContainModuleDataMemberF {
public:
	~RiderChangeContainModuleDataMemberF();
private:
	unsigned char m_pad[4];
};

class RiderChangeContainModuleDataBase
{
public:
	virtual ~RiderChangeContainModuleDataBase() {}
private:
	unsigned char m_pad[0xc];
};

class __declspec(novtable) RiderChangeContainModuleData : public RiderChangeContainModuleDataBase
{
public:
	virtual ~RiderChangeContainModuleData();
private:
	RiderChangeContainModuleDataMemberA m_a;
	unsigned char m_gap1[0x6c];
	RiderChangeContainModuleDataMemberB m_b;
	unsigned char m_gap2[0x6c];
	RiderChangeContainModuleDataMemberC m_c;
	unsigned char m_gap3[0x6c];
	RiderChangeContainModuleDataMemberD m_d;
	unsigned char m_gap4[0x6c];
	RiderChangeContainModuleDataMemberE m_e;
	unsigned char m_gap5[0x8];
	RiderChangeContainModuleDataMemberF m_f;
};

// ??1RiderChangeContainModuleData@@UAE@XZ
RiderChangeContainModuleData::~RiderChangeContainModuleData()
{
}
