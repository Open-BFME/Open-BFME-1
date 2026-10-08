// cl: /O2
//
// SubsystemDeleter<GlobalWeatherSystem> scalar-deleting destructor, retail
// 0x0006FF30 (30 bytes).  The exact constructor at 0x0006FF10 installs the
// one-slot vtable 0x01075DBC, whose slot routes here through ILT 0x0003E5E0.
// The wrapper calls the paired 89-byte owned-subsystem destructor at
// 0x0006FF60 through ILT 0x00031D72.

class GlobalWeatherSystem;

template<class SUBSYSTEM>
class SubsystemDeleter
{
public:
	virtual ~SubsystemDeleter();
	void *m_slot;
};

void forceGlobalWeatherSystemSlotDeletingDestructor()
{
	SubsystemDeleter<GlobalWeatherSystem> value;
}
