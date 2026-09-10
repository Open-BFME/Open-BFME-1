// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: GiveUpgradeUpdateModuleData scalar deleting destructor.
// The constructor installs vtable 0x010B53D0, whose slot zero reaches this
// wrapper through ILT 0x00040309.  The real destructor body is separately
// matched at 0x0025DE90.

class SpecialAbilityUpdateModuleData
{
public:
	virtual ~SpecialAbilityUpdateModuleData();
};

class GiveUpgradeUpdateModuleData : public SpecialAbilityUpdateModuleData
{
public:
	__declspec(noinline) virtual ~GiveUpgradeUpdateModuleData();
};

GiveUpgradeUpdateModuleData::~GiveUpgradeUpdateModuleData()
{
}
