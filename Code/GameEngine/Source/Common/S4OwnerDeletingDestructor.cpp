// cl: /DNDEBUG /MD /EHsc /O2
//
// Open-BFME: S4Owner scalar-deleting destructor at retail RVA 0x004654C0
// (30 bytes).  The matched constructor at 0x00464B20 installs vtable
// 0x010F7114 whose first slot reaches this wrapper through ILT 0x00020FB3;
// the complete destructor at 0x00464E20 drains S4Owner's four string-vector
// members before their STLport storage is unwound.

class S4Owner
{
public:
	virtual ~S4Owner();
};

void forceS4OwnerDeletingDestructor()
{
	S4Owner value;
}
