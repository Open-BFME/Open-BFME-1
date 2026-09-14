// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: View scalar-deleting destructor at retail RVA 0x0045C440
// (30 bytes).  The exact View constructor at 0x0045B8C0 installs the
// complete 64-slot vtable at 0x010F6940; slot zero routes through ILT
// 0x0000EF43 to this wrapper.  W3DView's constructor at 0x00745B10 calls
// that View constructor through ILT 0x0002284F, and its destructor at
// 0x007461B0 ends by calling ILT 0x0003732B to the matching View
// complete-destructor body at 0x0045C1B0.

class View
{
public:
	virtual ~View();
};

void forceViewDeletingDestructor()
{
	View value;
}
