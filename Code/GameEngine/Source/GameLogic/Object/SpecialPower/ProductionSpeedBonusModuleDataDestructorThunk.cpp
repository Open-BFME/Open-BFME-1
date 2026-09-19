// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ProductionSpeedBonusModuleData dtor. SEH ProductionSpeedBonusModuleDataMember @+0x218 then base.

class ProductionSpeedBonusModuleDataMember
{
public:
	~ProductionSpeedBonusModuleDataMember();
private:
	unsigned char m_pad[4];
};

class ProductionSpeedBonusModuleDataBase
{
public:
	virtual ~ProductionSpeedBonusModuleDataBase();
private:
	unsigned char m_pad[0x214];
};

class __declspec(novtable) ProductionSpeedBonusModuleData : public ProductionSpeedBonusModuleDataBase
{
public:
	virtual ~ProductionSpeedBonusModuleData();
private:
	ProductionSpeedBonusModuleDataMember m_member;
};

// ??1ProductionSpeedBonusModuleData@@UAE@XZ
ProductionSpeedBonusModuleData::~ProductionSpeedBonusModuleData()
{
}
