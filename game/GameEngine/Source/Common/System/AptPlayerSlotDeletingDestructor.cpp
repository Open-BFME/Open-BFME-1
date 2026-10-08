// cl: /O2
//
// SubsystemDeleter<AptPlayer> scalar-deleting destructor, retail 0x00070FB0
// (30 bytes).  The exact constructor at 0x00070F90 installs the one-slot
// vtable 0x01075E14, whose slot routes here through ILT 0x0001A582.  The
// wrapper calls the paired 89-byte owned-subsystem destructor at 0x00070FE0
// through ILT 0x000444B8.

class AptPlayer;

template<class SUBSYSTEM>
class SubsystemDeleter
{
public:
	virtual ~SubsystemDeleter();
	void *m_slot;
};

void forceAptPlayerSlotDeletingDestructor()
{
	SubsystemDeleter<AptPlayer> value;
}
