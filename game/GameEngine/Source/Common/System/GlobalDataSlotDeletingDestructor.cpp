// cl: /O2
//
// SubsystemDeleter<GlobalData> scalar-deleting destructor, retail 0x0006F6F0
// (30 bytes).  The exact constructor at 0x0006F6D0 installs the one-slot
// vtable 0x01075D90, which routes here through ILT 0x0000C72F.  The wrapper
// calls the paired 89-byte owned-subsystem destructor at 0x0006F720 through
// ILT 0x0003B96C.

class GlobalData;

template<class SUBSYSTEM>
class SubsystemDeleter
{
public:
	virtual ~SubsystemDeleter();
	void *m_slot;
};

void forceGlobalDataSlotDeletingDestructor()
{
	SubsystemDeleter<GlobalData> value;
}
