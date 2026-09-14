// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for TransportContain.
// Vtable 0x00CAD4E8 slots name this class (?getClassMemoryPool@TransportContain@@CAPAVMemoryPool@@XZ); its slot zero routes
// through ILT 0x00035E7C to this 30-byte wrapper, whose complete destructor
// route ILT 0x0003FF49 reaches cleanup body 0x0022CC80.

class TransportContain
{
protected:
	virtual ~TransportContain();
private:
	friend void forceTransportContainDeletingDestructor();
};

void forceTransportContainDeletingDestructor()
{
	TransportContain value;
}
