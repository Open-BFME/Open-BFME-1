// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for HordeMemberCollideModuleData.
// Constructor 0x00216790 installs dedicated vtable 0x00CA9DD0; its slot
// zero routes through ILT 0x00044521 to this 30-byte wrapper, whose complete
// destructor route ILT 0x000424FB reaches cleanup body 0x00216930.

class HordeMemberCollideModuleData
{
protected:
	virtual ~HordeMemberCollideModuleData();
private:
	friend void forceHordeMemberCollideModuleDataDeletingDestructor();
};

void forceHordeMemberCollideModuleDataDeletingDestructor()
{
	HordeMemberCollideModuleData value;
}
