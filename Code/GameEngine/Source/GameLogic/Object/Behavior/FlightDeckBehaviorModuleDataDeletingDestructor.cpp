// cl: /O2 /GR- /EHsc-
//
// FlightDeckBehaviorModuleData scalar-deleting destructor, retail 0x002131F0
// (30 bytes).  Its dedicated vtable at 0x010A8268 is installed by the exact
// named constructor at 0x002131B0; slot zero routes through ILT 0x00029609.

class FlightDeckBehaviorModuleData
{
public:
	virtual ~FlightDeckBehaviorModuleData();
};

void forceFlightDeckBehaviorModuleDataDeletingDestructor()
{
	FlightDeckBehaviorModuleData value;
}
