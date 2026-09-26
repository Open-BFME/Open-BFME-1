// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for ObjectTypes.
// Constructor 0x001DC220 installs dedicated vtable 0x00C9FB2C; its slot
// zero routes through ILT 0x0003DFBE to this 30-byte wrapper, whose complete
// destructor route ILT 0x0003EAFE reaches cleanup body 0x001DC400.

class ObjectTypes
{
protected:
	virtual ~ObjectTypes();
private:
	friend void forceObjectTypesDeletingDestructor();
};

void forceObjectTypesDeletingDestructor()
{
	ObjectTypes value;
}
