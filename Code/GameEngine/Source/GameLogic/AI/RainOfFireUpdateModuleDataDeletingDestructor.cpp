// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for RainOfFireUpdateModuleData.
// Constructor 0x002A08B0 installs dedicated vtable 0x00CC1698; its slot
// zero routes through ILT 0x000220CF to this 30-byte wrapper, whose complete
// destructor route ILT 0x0003BF52 reaches cleanup body 0x002A0C80.

class RainOfFireUpdateModuleData
{
protected:
	virtual ~RainOfFireUpdateModuleData();
private:
	friend void forceRainOfFireUpdateModuleDataDeletingDestructor();
};

void forceRainOfFireUpdateModuleDataDeletingDestructor()
{
	RainOfFireUpdateModuleData value;
}
