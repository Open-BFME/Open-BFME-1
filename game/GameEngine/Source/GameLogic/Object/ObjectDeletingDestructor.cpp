// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for Object.
// Primary vftable 0x00C9EE58 (installed by ??0Object at 0x001D29A0); its slot 7 routes
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
