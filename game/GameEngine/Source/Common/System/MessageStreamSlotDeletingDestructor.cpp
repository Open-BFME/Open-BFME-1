// cl: /O2
//
// SubsystemDeleter<MessageStream> scalar-deleting destructor, retail 0x00070170
// (30 bytes).  The exact constructor at 0x00070150 installs the one-slot
// vtable 0x01075DC8, whose slot routes here through ILT 0x000143FD.  The
// wrapper calls the paired 89-byte owned-subsystem destructor at 0x000701A0
// through ILT 0x00031C46.

class MessageStream;

template<class SUBSYSTEM>
class SubsystemDeleter
{
public:
	virtual ~SubsystemDeleter();
	void *m_slot;
};

void forceMessageStreamSlotDeletingDestructor()
{
	SubsystemDeleter<MessageStream> value;
}
