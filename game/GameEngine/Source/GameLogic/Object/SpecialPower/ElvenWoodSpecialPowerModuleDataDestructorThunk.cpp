// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ElvenWoodSpecialPowerModuleData dtor.

class ElvenWoodSpecialPowerModuleDataMemberA
{
public:
	~ElvenWoodSpecialPowerModuleDataMemberA();
private:
	unsigned char m_pad[0xc];
};

class ElvenWoodSpecialPowerModuleDataMemberB
{
public:
	~ElvenWoodSpecialPowerModuleDataMemberB();
private:
	unsigned char m_pad[4];
};

class ElvenWoodSpecialPowerModuleDataBase
{
public:
	virtual ~ElvenWoodSpecialPowerModuleDataBase();
private:
	unsigned char m_pad[0x20c];
};

class __declspec(novtable) ElvenWoodSpecialPowerModuleData : public ElvenWoodSpecialPowerModuleDataBase
{
public:
	virtual ~ElvenWoodSpecialPowerModuleData();
private:
	ElvenWoodSpecialPowerModuleDataMemberA m_a;
	ElvenWoodSpecialPowerModuleDataMemberB m_b;
};

// ??1ElvenWoodSpecialPowerModuleData@@UAE@XZ
ElvenWoodSpecialPowerModuleData::~ElvenWoodSpecialPowerModuleData()
{
}
