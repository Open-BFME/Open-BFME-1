// cl: /O2

// SubsystemDeleter<Radar> scalar-deleting destructor, retail 0x00071BB0
// (30 bytes). The matched initSubsystem<Radar> body at 0x00075350 constructs
// this holder with vtable 0x01075E54; slot zero routes here through ILT
// 0x0002088D. The wrapper calls the paired 89-byte destructor at 0x00071BE0
// through ILT 0x00027C87.

class Radar;

template<class SUBSYSTEM>
class SubsystemDeleter
{
public:
	virtual ~SubsystemDeleter();
	void *m_slot;
};

void forceRadarSlotDeletingDestructor()
{
	SubsystemDeleter<Radar> value;
}
