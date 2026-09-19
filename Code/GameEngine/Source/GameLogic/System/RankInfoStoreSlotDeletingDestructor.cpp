// cl: /O2
//
// SubsystemSlot<RankInfoStore> scalar-deleting destructor, retail 0x000703B0
// (30 bytes).  The exact constructor at 0x00070390 installs the one-slot
// vtable 0x01075DD4, whose slot routes here through ILT 0x00008855.  The
// wrapper calls the paired 89-byte owned-subsystem destructor at 0x000703E0
// through ILT 0x0002325E.

class RankInfoStore;

template<class SUBSYSTEM>
class SubsystemSlot
{
public:
	virtual ~SubsystemSlot();
	void *m_slot;
};

void forceRankInfoStoreSlotDeletingDestructor()
{
	SubsystemSlot<RankInfoStore> value;
}
