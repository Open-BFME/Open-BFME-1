// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: GloriousChargeUpdateModuleData scalar deleting destructor.
// The matched constructor at 0x0025E7C0 installs vtable 0x010B5428;
// slot zero reaches the wrapper at 0x0025E850 through ILT 0x00049FF8.

class SpecialAbilityUpdateModuleData
{
public:
	virtual ~SpecialAbilityUpdateModuleData();

private:
	unsigned char m_data[ 0x250 ];
};

class GloriousChargeUpdateModuleData : public SpecialAbilityUpdateModuleData
{
public:
	__declspec(noinline) virtual ~GloriousChargeUpdateModuleData();

private:
	unsigned int m_field254;
	unsigned int m_field258;
	unsigned int m_field25c;
};

GloriousChargeUpdateModuleData::~GloriousChargeUpdateModuleData()
{
}
