// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for MapTransferLoadScreen.
// Vtable 0x00CF9B60 slots name this class (?update@MapTransferLoadScreen@@UAEXH@Z); its slot zero routes
// through ILT 0x0000F538 to this 30-byte wrapper, whose complete destructor
// route ILT 0x00034081 reaches cleanup body 0x00490E10.

class MapTransferLoadScreen
{
protected:
	virtual ~MapTransferLoadScreen();
private:
	friend void forceMapTransferLoadScreenDeletingDestructor();
};

void forceMapTransferLoadScreenDeletingDestructor()
{
	MapTransferLoadScreen value;
}
