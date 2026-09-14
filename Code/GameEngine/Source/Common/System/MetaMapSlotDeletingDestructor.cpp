// cl: /O2

// SubsystemSlot<MetaMap> scalar-deleting destructor, retail
// 0x00071D30 (30 bytes). The exact constructor at 0x00071D10 installs the
// one-slot vtable, whose slot routes here.

class MetaMap;

template<class SUBSYSTEM>
class SubsystemSlot
{
public:
	virtual ~SubsystemSlot();
	void *m_slot;
};

void forceMetaMapSlotDeletingDestructor()
{
	SubsystemSlot<MetaMap> value;
}
