// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for AutoFindHealingUpdateModuleData.
// Constructor 0x00281430 installs dedicated vtable 0x00CBB210; its slot
// zero routes through ILT 0x0001B9F0 to this 30-byte wrapper, whose complete
// destructor route ILT 0x00032303 reaches cleanup body 0x00281630.

class AutoFindHealingUpdateModuleData
{
protected:
	virtual ~AutoFindHealingUpdateModuleData();
private:
	friend void forceAutoFindHealingUpdateModuleDataDeletingDestructor();
};

void forceAutoFindHealingUpdateModuleDataDeletingDestructor()
{
	AutoFindHealingUpdateModuleData value;
}
