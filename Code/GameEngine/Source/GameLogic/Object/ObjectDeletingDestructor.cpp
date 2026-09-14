// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for Object.
// Vtable 0x00C9EE74 slots name this class (?getDrawable@Object@@UBEPAVDrawable@@XZ); its slot zero routes
// through ILT 0x00046F33 to this 30-byte wrapper, whose complete destructor
// route ILT 0x0000207C reaches cleanup body 0x001D4010.

class Object
{
protected:
	virtual ~Object();
private:
	friend void forceObjectDeletingDestructor();
};

void forceObjectDeletingDestructor()
{
	Object value;
}
