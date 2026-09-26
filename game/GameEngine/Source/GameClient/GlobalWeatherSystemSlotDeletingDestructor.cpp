// cl: /O2
//
// SubsystemSlot<GlobalWeatherSystem> scalar-deleting destructor, retail
// 0x0006FF30 (30 bytes).  The exact constructor at 0x0006FF10 installs the
// one-slot vtable 0x01075DBC, whose slot routes here through ILT 0x0003E5E0.
// The wrapper calls the paired 89-byte owned-subsystem destructor at
// 0x0006FF60 through ILT 0x00031D72.

class GlobalWeatherSystem;

template<class SUBSYSTEM>
class SubsystemSlot
{
public:
	virtual ~SubsystemSlot();
	void *m_slot;
};

void forceGlobalWeatherSystemSlotDeletingDestructor()
{
	SubsystemSlot<GlobalWeatherSystem> value;
}
