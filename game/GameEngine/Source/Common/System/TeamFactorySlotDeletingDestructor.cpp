// cl: /O2

// SubsystemDeleter<TeamFactory> scalar-deleting destructor, retail
// 0x000717F0 (30 bytes). The exact constructor at 0x000717D0 installs the
// one-slot vtable, whose slot routes here.

class TeamFactory;

template<class SUBSYSTEM>
class SubsystemDeleter
{
public:
	virtual ~SubsystemDeleter();
	void *m_slot;
};

void forceTeamFactorySlotDeletingDestructor()
{
	SubsystemDeleter<TeamFactory> value;
}
