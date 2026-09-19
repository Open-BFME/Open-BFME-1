// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for DemoTrapUpdateModuleData.
// Constructor 0x0028C9E0 installs dedicated vtable 0x00CBD7D8; its slot
// zero routes through ILT 0x0000C784 to this 30-byte wrapper, whose complete
// destructor route ILT 0x0000F1C3 reaches cleanup body 0x0028CA60.

class DemoTrapUpdateModuleData
{
protected:
	virtual ~DemoTrapUpdateModuleData();
private:
	friend void forceDemoTrapUpdateModuleDataDeletingDestructor();
};

void forceDemoTrapUpdateModuleDataDeletingDestructor()
{
	DemoTrapUpdateModuleData value;
}
