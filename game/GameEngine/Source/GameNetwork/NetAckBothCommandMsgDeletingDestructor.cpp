// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: NetAckBothCommandMsg protected scalar-deleting destructor at
// retail RVA 0x00674490 (30 bytes).  The exact constructors at 0x00673740
// and 0x006737A0 install vtable 0x0111A488.  Its slot-0 thunk routes through
// ILT 0x0003570B to this body, which calls NetCommandMsg::~NetCommandMsg()
// through ILT 0x0002F702 before operator delete.  The upstream header keeps
// both destructors commented, so the protected declarations below preserve
// the retail access decoration without changing the reference header.

class NetCommandMsg
{
protected:
	virtual ~NetCommandMsg();
};

class NetAckBothCommandMsg : public NetCommandMsg
{
	friend void forceNetAckBothCommandMsgDeletingDestructor();

protected:
	virtual ~NetAckBothCommandMsg() {}
};

void forceNetAckBothCommandMsgDeletingDestructor()
{
	NetAckBothCommandMsg value;
}
