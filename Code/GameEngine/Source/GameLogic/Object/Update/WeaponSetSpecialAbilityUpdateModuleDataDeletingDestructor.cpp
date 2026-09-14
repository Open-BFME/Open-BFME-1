// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: WeaponSetSpecialAbilityUpdateModuleData scalar-deleting
// destructor at retail RVA 0x0026DD90 (30 bytes).  Its matched constructor
// at 0x0026DC20 installs module-data vtable 0x010B8DF0 after the shared
// SpecialAbilityUpdateModuleData base construction.  The wrapper's call is
// the shared base destructor ILT 0x0001980D, establishing this derived
// module-data identity.


class SpecialAbilityUpdateModuleData
{
public:
	virtual ~SpecialAbilityUpdateModuleData();
};

class WeaponSetSpecialAbilityUpdateModuleData : public SpecialAbilityUpdateModuleData
{
public:
	__declspec(noinline) virtual ~WeaponSetSpecialAbilityUpdateModuleData();
};

WeaponSetSpecialAbilityUpdateModuleData::~WeaponSetSpecialAbilityUpdateModuleData()
{
}
