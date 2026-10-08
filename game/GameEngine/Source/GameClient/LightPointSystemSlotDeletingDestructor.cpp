// cl: /O2
//
// SubsystemDeleter<LightPointSystem> scalar-deleting destructor, retail
// 0x00070E30 (30 bytes).  The exact constructor at 0x00070E10 installs the
// one-slot vtable 0x01075E0C, whose slot routes here through ILT 0x0001E3DA.
// The wrapper calls the paired 89-byte owned-subsystem destructor at
// 0x00070E60 through ILT 0x0000B9EC.

class LightPointSystem;

template<class SUBSYSTEM>
class SubsystemDeleter
{
public:
	virtual ~SubsystemDeleter();
	void *m_slot;
};

void forceLightPointSystemSlotDeletingDestructor()
{
	SubsystemDeleter<LightPointSystem> value;
}
