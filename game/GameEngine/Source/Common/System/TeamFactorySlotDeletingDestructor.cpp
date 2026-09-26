// cl: /O2

// SubsystemSlot<TeamFactory> scalar-deleting destructor, retail
// 0x000717F0 (30 bytes). The exact constructor at 0x000717D0 installs the
// one-slot vtable, whose slot routes here.

class TeamFactory;

template<class SUBSYSTEM>
class SubsystemSlot
{
public:
	virtual ~SubsystemSlot();
	void *m_slot;
};

void forceTeamFactorySlotDeletingDestructor()
{
	SubsystemSlot<TeamFactory> value;
}
