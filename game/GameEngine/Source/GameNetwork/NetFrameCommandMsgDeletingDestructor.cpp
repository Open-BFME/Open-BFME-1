// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: NetFrameCommandMsg scalar-deleting destructor at retail RVA
// 0x00662880 (30 bytes). The exact constructor at 0x006627F0 installs vtable
// 0x0111A220, whose slot zero routes through ILT 0x00029EC9 to this wrapper.
// The wrapper calls the complete destructor through ILT 0x000265D0.

class NetFrameCommandMsg
{
public:
	virtual ~NetFrameCommandMsg();
};

void forceNetFrameCommandMsgDeletingDestructor()
{
	NetFrameCommandMsg value;
}
