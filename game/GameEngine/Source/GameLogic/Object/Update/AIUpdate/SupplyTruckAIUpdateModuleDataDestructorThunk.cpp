// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SupplyTruckAIUpdateModuleData dtor. SEH SupplyTruckAIUpdateModuleDataMember @+0x84 then base.

class SupplyTruckAIUpdateModuleDataMember
{
public:
	~SupplyTruckAIUpdateModuleDataMember();
private:
	unsigned char m_pad[4];
};

class SupplyTruckAIUpdateModuleDataBase
{
public:
	virtual ~SupplyTruckAIUpdateModuleDataBase();
private:
	unsigned char m_pad[0x80];
};

class __declspec(novtable) SupplyTruckAIUpdateModuleData : public SupplyTruckAIUpdateModuleDataBase
{
public:
	virtual ~SupplyTruckAIUpdateModuleData();
private:
	SupplyTruckAIUpdateModuleDataMember m_member;
};

// ??1SupplyTruckAIUpdateModuleData@@UAE@XZ
SupplyTruckAIUpdateModuleData::~SupplyTruckAIUpdateModuleData()
{
}
