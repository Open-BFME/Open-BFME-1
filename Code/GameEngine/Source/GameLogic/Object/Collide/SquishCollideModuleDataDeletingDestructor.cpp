// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for SquishCollideModuleData.
// Constructor 0x00216B90 installs dedicated vtable 0x00CA9F40; its slot
// zero routes through ILT 0x000470EB to this 30-byte wrapper, whose complete
// destructor route ILT 0x0001922C reaches cleanup body 0x00216D80.

class SquishCollideModuleData
{
protected:
	virtual ~SquishCollideModuleData();
private:
	friend void forceSquishCollideModuleDataDeletingDestructor();
};

void forceSquishCollideModuleDataDeletingDestructor()
{
	SquishCollideModuleData value;
}
