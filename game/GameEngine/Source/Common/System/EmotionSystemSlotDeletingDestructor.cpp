// cl: /O2
//
// SubsystemDeleter<EmotionSystem> scalar-deleting destructor, retail 0x00070CB0
// (30 bytes).  The exact constructor at 0x00070C90 installs the one-slot
// vtable 0x01075E04, whose slot routes here through ILT 0x00003D23.  The
// wrapper calls the paired 89-byte owned-subsystem destructor at 0x00070CE0
// through ILT 0x0001B2C0.

class EmotionSystem;

template<class SUBSYSTEM>
class SubsystemDeleter
{
public:
	virtual ~SubsystemDeleter();
	void *m_slot;
};

void forceEmotionSystemSlotDeletingDestructor()
{
	SubsystemDeleter<EmotionSystem> value;
}
