// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: GiveUpgradeUpdateModuleData scalar deleting destructor.
// The constructor installs vtable 0x010B53D0, whose slot zero reaches this
// wrapper through ILT 0x00040309.  The real destructor body is separately
// matched at 0x0025DE90.

class __declspec(novtable) SpecialAbilityUpdateModuleData
{
public:
	virtual ~SpecialAbilityUpdateModuleData();
};

class GiveUpgradeUpdateModuleData : public SpecialAbilityUpdateModuleData
{
	friend void forceGiveUpgradeUpdateModuleDataDeletingDestructorCopy(const GiveUpgradeUpdateModuleData &that);
public:
	__declspec(noinline) virtual ~GiveUpgradeUpdateModuleData();
};

// ~GiveUpgradeUpdateModuleData is matched out of line (GiveUpgradeUpdateModuleDataDestructor.cpp). The implicit copy constructor (no
// retail twin) emits the vftable and with it ??_G without a second destructor body.
void forceGiveUpgradeUpdateModuleDataDeletingDestructorCopy(const GiveUpgradeUpdateModuleData &that)
{
	GiveUpgradeUpdateModuleData value(that);
}
