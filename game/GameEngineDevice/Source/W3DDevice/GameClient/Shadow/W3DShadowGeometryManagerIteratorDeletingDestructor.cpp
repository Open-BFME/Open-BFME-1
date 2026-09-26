// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for W3DShadowGeometryManagerIterator.
// Constructor 0x007B96B0 installs dedicated vtable 0x00D284A8; its slot
// zero routes through ILT 0x00022598 to this 30-byte wrapper, whose complete
// destructor route ILT 0x00010B3B reaches cleanup body 0x007B96D0.

class W3DShadowGeometryManagerIterator
{
protected:
	virtual ~W3DShadowGeometryManagerIterator();
private:
	friend void forceW3DShadowGeometryManagerIteratorDeletingDestructor();
};

void forceW3DShadowGeometryManagerIteratorDeletingDestructor()
{
	W3DShadowGeometryManagerIterator value;
}
