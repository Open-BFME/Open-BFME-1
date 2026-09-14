// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for FireSpreadUpdateModuleData.
// Constructor 0x00292680 installs dedicated vtable 0x00CBEA00; its slot
// zero routes through ILT 0x00038235 to this 30-byte wrapper, whose complete
// destructor route ILT 0x0002EEDD reaches cleanup body 0x002928F0.

class FireSpreadUpdateModuleData
{
protected:
	virtual ~FireSpreadUpdateModuleData();
private:
	friend void forceFireSpreadUpdateModuleDataDeletingDestructor();
};

void forceFireSpreadUpdateModuleDataDeletingDestructor()
{
	FireSpreadUpdateModuleData value;
}
