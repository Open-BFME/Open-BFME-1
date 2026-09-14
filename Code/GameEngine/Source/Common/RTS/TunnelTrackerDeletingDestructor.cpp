// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: TunnelTracker scalar-deleting destructor at retail RVA 0x000F8D50
// (30 bytes). The exact constructor at 0x000F8980 installs vtable 0x01085FD8,
// whose slot zero routes through ILT 0x000123FF to this wrapper. The complete
// destructor is reached through ILT 0x0002A19E.

class TunnelTracker
{
public:
	virtual ~TunnelTracker();
};

void forceTunnelTrackerDeletingDestructor()
{
	TunnelTracker value;
}
