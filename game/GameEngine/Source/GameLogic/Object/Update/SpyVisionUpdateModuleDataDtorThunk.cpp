// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SpyVisionUpdateModuleData dtor multi-member SEH.

class SpyVisionUpdateModuleDataMemberA {
public:
	~SpyVisionUpdateModuleDataMemberA();
private:
	unsigned char m_pad[4];
};
class SpyVisionUpdateModuleDataMemberB {
public:
	~SpyVisionUpdateModuleDataMemberB();
private:
	unsigned char m_pad[4];
};
class SpyVisionUpdateModuleDataMemberC {
public:
	~SpyVisionUpdateModuleDataMemberC();
private:
	unsigned char m_pad[4];
};
class SpyVisionUpdateModuleDataMemberD {
public:
	~SpyVisionUpdateModuleDataMemberD();
private:
	unsigned char m_pad[4];
};
class SpyVisionUpdateModuleDataMemberE {
public:
	~SpyVisionUpdateModuleDataMemberE();
private:
	unsigned char m_pad[4];
};
class SpyVisionUpdateModuleDataMemberF {
public:
	~SpyVisionUpdateModuleDataMemberF();
private:
	unsigned char m_pad[4];
};
class SpyVisionUpdateModuleDataMemberG {
public:
	~SpyVisionUpdateModuleDataMemberG();
private:
	unsigned char m_pad[4];
};
class SpyVisionUpdateModuleDataMemberH {
public:
	~SpyVisionUpdateModuleDataMemberH();
private:
	unsigned char m_pad[4];
};

class SpyVisionUpdateModuleDataBase
{
public:
	virtual ~SpyVisionUpdateModuleDataBase() {}
private:
	unsigned char m_pad[0x8];
};

class __declspec(novtable) SpyVisionUpdateModuleData : public SpyVisionUpdateModuleDataBase
{
public:
	virtual ~SpyVisionUpdateModuleData();
private:
	SpyVisionUpdateModuleDataMemberA m_a;
	unsigned char m_gap1[0xc];
	SpyVisionUpdateModuleDataMemberB m_b;
	SpyVisionUpdateModuleDataMemberC m_c;
	unsigned char m_gap3[0x18];
	SpyVisionUpdateModuleDataMemberD m_d;
	SpyVisionUpdateModuleDataMemberE m_e;
	unsigned char m_gap5[0x10];
	SpyVisionUpdateModuleDataMemberF m_f;
	unsigned char m_gap6[0x8];
	SpyVisionUpdateModuleDataMemberG m_g;
	unsigned char m_gap7[0x8];
	SpyVisionUpdateModuleDataMemberH m_h;
};

// ??1SpyVisionUpdateModuleData@@UAE@XZ
SpyVisionUpdateModuleData::~SpyVisionUpdateModuleData()
{
}
