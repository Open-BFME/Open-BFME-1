// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: SupplyTruckAIUpdate scalar-deleting destructor at retail RVA
// 0x002C5E30 (30 bytes). Its exact constructor at 0x002C6AE0, complete
// destructor at 0x002C5580, typed factories, module name, and state-machine
// implementation establish the class. The destructor ILT is 0x00042F2D.

class SupplyTruckAIUpdate
{
public:
	virtual ~SupplyTruckAIUpdate();
};

void forceSupplyTruckAIUpdateDeletingDestructor()
{
	SupplyTruckAIUpdate value;
}
