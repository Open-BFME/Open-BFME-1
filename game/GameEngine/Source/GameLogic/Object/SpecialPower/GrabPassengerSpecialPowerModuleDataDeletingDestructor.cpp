// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: GrabPassengerSpecialPowerModuleData scalar deleting destructor.
// Its matched constructor installs vtable 0x010B5848, whose slot zero reaches
// this wrapper through ILT 0x0000FC09.  The empty derived destructor is folded
// with SpecialPowerModuleData::~SpecialPowerModuleData in the retail image.

class __declspec(novtable) SpecialPowerModuleData
{
public:
	virtual ~SpecialPowerModuleData();
};

class GrabPassengerSpecialPowerModuleData : public SpecialPowerModuleData
{
	friend void forceGrabPassengerSpecialPowerModuleDataDeletingDestructorCopy(const GrabPassengerSpecialPowerModuleData &that);
public:
	__declspec(noinline) virtual ~GrabPassengerSpecialPowerModuleData();
};

// ~GrabPassengerSpecialPowerModuleData is matched out of line (SpecialPowerModuleDataDestructorThunk.cpp). The implicit copy constructor (no
// retail twin) emits the vftable and with it ??_G without a second destructor body.
void forceGrabPassengerSpecialPowerModuleDataDeletingDestructorCopy(const GrabPassengerSpecialPowerModuleData &that)
{
	GrabPassengerSpecialPowerModuleData value(that);
}
