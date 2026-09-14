// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: SwayClientUpdate scalar-deleting destructor at retail RVA
// 0x006045F0 (30 bytes). The exact constructor at 0x006044E0 installs vtable
// 0x011154F0, whose slot zero routes through ILT 0x0003C420 to this wrapper.
// The named module factory at 0x00121AF0 corroborates identity; the complete
// destructor is called through ILT 0x00044035.

class SwayClientUpdate
{
public:
	virtual ~SwayClientUpdate();
};

void forceSwayClientUpdateDeletingDestructor()
{
	SwayClientUpdate value;
}
