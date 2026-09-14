// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: BFMENetRouterFallbackCommandMsg scalar-deleting destructor at
// retail RVA 0x006628F0 (30 bytes). The exact constructor at 0x006628C0
// installs vtable 0x0111A234, whose slot zero routes through ILT 0x00046F6F
// to this wrapper. The complete destructor is reached through ILT 0x00020E00.

class BFMENetRouterFallbackCommandMsg
{
public:
	virtual ~BFMENetRouterFallbackCommandMsg();
};

void forceBFMENetRouterFallbackCommandMsgDeletingDestructor()
{
	BFMENetRouterFallbackCommandMsg value;
}
