// cl: /O2
//
// SubsystemSlot<ThingFactory> scalar-deleting destructor, retail 0x00070D70
// (30 bytes).  The exact constructor at 0x00070D50 installs the one-slot
// vtable 0x01075E08, whose slot routes here through ILT 0x00027A89.  The
// wrapper calls the paired 89-byte owned-subsystem destructor at 0x00070DA0
// through ILT 0x00025E5A.

class ThingFactory;

template<class SUBSYSTEM>
class SubsystemSlot
{
public:
	virtual ~SubsystemSlot();
	void *m_slot;
};

void forceThingFactorySlotDeletingDestructor()
{
	SubsystemSlot<ThingFactory> value;
}
