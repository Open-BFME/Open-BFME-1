// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for DelayedLuaEventUpdateModuleData.
// Constructor 0x0028BBF0 installs dedicated vtable 0x00CBD278; its slot
// zero routes through ILT 0x0000DECC to this 30-byte wrapper, whose complete
// destructor route ILT 0x00049B4D reaches cleanup body 0x0028BCA0.

class DelayedLuaEventUpdateModuleData
{
protected:
	virtual ~DelayedLuaEventUpdateModuleData();
private:
	friend void forceDelayedLuaEventUpdateModuleDataDeletingDestructor();
};

void forceDelayedLuaEventUpdateModuleDataDeletingDestructor()
{
	DelayedLuaEventUpdateModuleData value;
}
