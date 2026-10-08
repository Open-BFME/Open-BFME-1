// cl: /O2
//
// SubsystemDeleter<AudioManager> scalar-deleting destructor, retail 0x0006F930
// (30 bytes).  The exact constructor at 0x0006F910 installs the one-slot
// vtable 0x01075D9C, whose slot routes here through ILT 0x00001BA4.  The
// wrapper calls the paired 89-byte owned-subsystem destructor at 0x0006F960
// through ILT 0x000223BD.

class AudioManager;

template<class SUBSYSTEM>
class SubsystemDeleter
{
public:
	virtual ~SubsystemDeleter();
	void *m_slot;
};

void forceAudioManagerSlotDeletingDestructor()
{
	SubsystemDeleter<AudioManager> value;
}
