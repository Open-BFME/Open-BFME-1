// cl: /O2

// SubsystemDeleter<HouseColorSystem> scalar-deleting destructor, retail
// 0x00071DF0 (30 bytes). The exact constructor at 0x00071DD0 installs the
// one-slot vtable, whose slot routes here.

class HouseColorSystem;

template<class SUBSYSTEM>
class SubsystemDeleter
{
public:
	virtual ~SubsystemDeleter();
	void *m_slot;
};

void forceHouseColorSystemSlotDeletingDestructor()
{
	SubsystemDeleter<HouseColorSystem> value;
}
