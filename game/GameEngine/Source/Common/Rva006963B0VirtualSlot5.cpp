// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Retail 0x006963B0: a stdcall wrapper forwarding two arguments to slot five.
struct Rva006963B0Receiver
{
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual int slot5(int first, int second);
};

int __stdcall rva006963B0ForwardSlot5(Rva006963B0Receiver *receiver, int first, int second)
{
	return receiver->slot5(first, second);
}
