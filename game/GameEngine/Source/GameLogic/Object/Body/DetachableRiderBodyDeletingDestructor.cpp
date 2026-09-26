// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for DetachableRiderBody.
// Vtable 0x00CA81A8 slots name this class (?getModuleNameKey@DetachableRiderBody@@UBE?AW4NameKeyType@@XZ); its slot zero routes
// through ILT 0x00032DC1 to this 30-byte wrapper, whose complete destructor
// route ILT 0x00016469 reaches cleanup body 0x00212D30.

class DetachableRiderBody
{
protected:
	virtual ~DetachableRiderBody();
private:
	friend void forceDetachableRiderBodyDeletingDestructor();
};

void forceDetachableRiderBodyDeletingDestructor()
{
	DetachableRiderBody value;
}
