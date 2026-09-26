// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for TunnelContain.
// Vtable 0x00CADDB8 slots name this class (?getClassMemoryPool@TunnelContain@@CAPAVMemoryPool@@XZ); its slot zero routes
// through ILT 0x00040B42 to this 30-byte wrapper, whose complete destructor
// route ILT 0x0003BF39 reaches cleanup body 0x0022EF90.

class TunnelContain
{
protected:
	virtual ~TunnelContain();
private:
	friend void forceTunnelContainDeletingDestructor();
};

void forceTunnelContainDeletingDestructor()
{
	TunnelContain value;
}
