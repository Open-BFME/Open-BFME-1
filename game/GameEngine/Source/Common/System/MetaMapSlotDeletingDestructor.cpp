// cl: /O2

// SubsystemDeleter<MetaMap> scalar-deleting destructor, retail
// 0x00071D30 (30 bytes). The exact constructor at 0x00071D10 installs the
// one-slot vtable, whose slot routes here.

class MetaMap;

template<class SUBSYSTEM>
class SubsystemDeleter
{
public:
	virtual ~SubsystemDeleter();
	void *m_slot;
};

void forceMetaMapSlotDeletingDestructor()
{
	SubsystemDeleter<MetaMap> value;
}
