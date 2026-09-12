// cl: /O2
//
// SubsystemSlot<ModuleFactory> scalar-deleting destructor, retail 0x000700B0
// (30 bytes).  The exact constructor at 0x00070090 installs the one-slot
// vtable 0x01075DC4, whose slot routes here through ILT 0x00031066.  The
// wrapper calls the paired 89-byte owned-subsystem destructor at 0x000700E0
// through ILT 0x0003A6D4.

class ModuleFactory;

template<class SUBSYSTEM>
class SubsystemSlot
{
public:
	virtual ~SubsystemSlot();
	void *m_slot;
};

void forceModuleFactorySlotDeletingDestructor()
{
	SubsystemSlot<ModuleFactory> value;
}
