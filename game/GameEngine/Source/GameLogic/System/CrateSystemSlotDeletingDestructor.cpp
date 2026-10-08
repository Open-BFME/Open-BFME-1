// cl: /O2

// SubsystemDeleter<CrateSystem> scalar-deleting destructor, retail
// 0x000718B0 (30 bytes). The exact constructor at 0x00071890 installs the
// one-slot vtable, whose slot routes here.

class CrateSystem;

template<class SUBSYSTEM>
class SubsystemDeleter
{
public:
	virtual ~SubsystemDeleter();
	void *m_slot;
};

void forceCrateSystemSlotDeletingDestructor()
{
	SubsystemDeleter<CrateSystem> value;
}
