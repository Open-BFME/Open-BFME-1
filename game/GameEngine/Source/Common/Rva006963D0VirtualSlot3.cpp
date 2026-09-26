// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Retail 0x006963D0: a stdcall wrapper forwarding two arguments to slot three.
struct Rva006963D0Receiver
{
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual int slot3(int first, int second);
};

int __stdcall rva006963D0ForwardSlot3(Rva006963D0Receiver *receiver, int first, int second)
{
	return receiver->slot3(first, second);
}
