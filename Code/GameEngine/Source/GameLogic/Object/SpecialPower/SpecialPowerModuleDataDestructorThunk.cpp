// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SpecialPowerModuleData dtor multi-member SEH.
// ICF-folded onto ??1RiderChangeContainModuleData@@UAE@XZ @ 0x00258730 in
// retail; the matched CashHack/OCL/ElvenWood derived dtors all call this body
// as their base-class destructor via link thunk 0x0001D7B4.

class SpecialPowerModuleDataMemberA {
public:
	~SpecialPowerModuleDataMemberA();
private:
	unsigned char m_pad[4];
};
class SpecialPowerModuleDataMemberB {
public:
	~SpecialPowerModuleDataMemberB();
private:
	unsigned char m_pad[4];
};
class SpecialPowerModuleDataMemberC {
public:
	~SpecialPowerModuleDataMemberC();
private:
	unsigned char m_pad[4];
};
class SpecialPowerModuleDataMemberD {
public:
	~SpecialPowerModuleDataMemberD();
private:
	unsigned char m_pad[4];
};
class SpecialPowerModuleDataMemberE {
public:
	~SpecialPowerModuleDataMemberE();
private:
	unsigned char m_pad[4];
};
class SpecialPowerModuleDataMemberF {
public:
	~SpecialPowerModuleDataMemberF();
private:
	unsigned char m_pad[4];
};

class SpecialPowerModuleDataBase
{
public:
	virtual ~SpecialPowerModuleDataBase() {}
private:
	unsigned char m_pad[0xc];
};

class __declspec(novtable) SpecialPowerModuleData : public SpecialPowerModuleDataBase
{
public:
	virtual ~SpecialPowerModuleData();
private:
	SpecialPowerModuleDataMemberA m_a;
	unsigned char m_gap1[0x6c];
	SpecialPowerModuleDataMemberB m_b;
	unsigned char m_gap2[0x6c];
	SpecialPowerModuleDataMemberC m_c;
	unsigned char m_gap3[0x6c];
	SpecialPowerModuleDataMemberD m_d;
	unsigned char m_gap4[0x6c];
	SpecialPowerModuleDataMemberE m_e;
	unsigned char m_gap5[0x8];
	SpecialPowerModuleDataMemberF m_f;
};

SpecialPowerModuleData::~SpecialPowerModuleData()
{
}
