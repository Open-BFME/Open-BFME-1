// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for DestroyEnvironmentUpdateModuleData.
// Constructor 0x0028CD30 installs dedicated vtable 0x00CBDA00; its slot
// zero routes through ILT 0x00027908 to this 30-byte wrapper, whose complete
// destructor route ILT 0x00024181 reaches cleanup body 0x0028CF20.

class DestroyEnvironmentUpdateModuleData
{
protected:
	virtual ~DestroyEnvironmentUpdateModuleData();
private:
	friend void forceDestroyEnvironmentUpdateModuleDataDeletingDestructor();
};

void forceDestroyEnvironmentUpdateModuleDataDeletingDestructor()
{
	DestroyEnvironmentUpdateModuleData value;
}
