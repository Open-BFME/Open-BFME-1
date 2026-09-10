// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: GrabPassengerSpecialPowerModuleData scalar deleting destructor.
// Its matched constructor installs vtable 0x010B5848, whose slot zero reaches
// this wrapper through ILT 0x0000FC09.  The empty derived destructor is folded
// with SpecialPowerModuleData::~SpecialPowerModuleData in the retail image.

class SpecialPowerModuleData
{
public:
	virtual ~SpecialPowerModuleData();
};

class GrabPassengerSpecialPowerModuleData : public SpecialPowerModuleData
{
public:
	__declspec(noinline) virtual ~GrabPassengerSpecialPowerModuleData();
};

GrabPassengerSpecialPowerModuleData::~GrabPassengerSpecialPowerModuleData()
{
}
