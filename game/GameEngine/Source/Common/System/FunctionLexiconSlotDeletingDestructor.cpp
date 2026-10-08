// cl: /O2
//
// SubsystemDeleter<FunctionLexicon> scalar-deleting destructor, retail
// 0x0006FFF0 (30 bytes).  The exact constructor at 0x0006FFD0 installs the
// one-slot vtable 0x01075DC0, whose slot routes here through ILT 0x0002A644.
// The wrapper calls the paired 89-byte owned-subsystem destructor at
// 0x00070020 through ILT 0x000292AD.

class FunctionLexicon;

template<class SUBSYSTEM>
class SubsystemDeleter
{
public:
	virtual ~SubsystemDeleter();
	void *m_slot;
};

void forceFunctionLexiconSlotDeletingDestructor()
{
	SubsystemDeleter<FunctionLexicon> value;
}
