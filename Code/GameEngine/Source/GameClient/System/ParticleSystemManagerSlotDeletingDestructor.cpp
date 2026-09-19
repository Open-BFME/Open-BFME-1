// cl: /O2
//
// SubsystemSlot<ParticleSystemManager> scalar-deleting destructor, retail
// 0x000705F0 (30 bytes).  The exact constructor at 0x000705D0 installs the
// one-slot vtable 0x01075DE0, whose slot routes here through ILT 0x00035611.
// The wrapper calls the paired 89-byte owned-subsystem destructor at
// 0x00070620 through ILT 0x0002D7BD.

class ParticleSystemManager;

template<class SUBSYSTEM>
class SubsystemSlot
{
public:
	virtual ~SubsystemSlot();
	void *m_slot;
};

void forceParticleSystemManagerSlotDeletingDestructor()
{
	SubsystemSlot<ParticleSystemManager> value;
}
