// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for ProneUpdateModuleData.
// Constructor 0x0029FE30 installs dedicated vtable 0x00CC1290; its slot
// zero routes through ILT 0x00028E43 to this 30-byte wrapper, whose complete
// destructor route ILT 0x0004A615 reaches cleanup body 0x002A0020.

class ProneUpdateModuleData
{
protected:
	virtual ~ProneUpdateModuleData();
private:
	friend void forceProneUpdateModuleDataDeletingDestructor();
};

void forceProneUpdateModuleDataDeletingDestructor()
{
	ProneUpdateModuleData value;
}
