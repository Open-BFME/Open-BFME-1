// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for W3DView.
// Vtable 0x00D217A0 slots name this class (?init@W3DView@@UAEXXZ); its slot zero routes
// through ILT 0x00041191 to this 30-byte wrapper, whose complete destructor
// route ILT 0x00044684 reaches cleanup body 0x007461B0.

class W3DView
{
protected:
	virtual ~W3DView();
private:
	friend void forceW3DViewDeletingDestructor();
};

void forceW3DViewDeletingDestructor()
{
	W3DView value;
}
