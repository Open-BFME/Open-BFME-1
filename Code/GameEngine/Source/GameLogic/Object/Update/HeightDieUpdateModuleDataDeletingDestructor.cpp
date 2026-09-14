// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for HeightDieUpdateModuleData.
// Constructor 0x00295500 installs dedicated vtable 0x00CBF498; its slot
// zero routes through ILT 0x0001C95E to this 30-byte wrapper, whose complete
// destructor route ILT 0x0002DC9A reaches cleanup body 0x00295750.

class HeightDieUpdateModuleData
{
protected:
	virtual ~HeightDieUpdateModuleData();
private:
	friend void forceHeightDieUpdateModuleDataDeletingDestructor();
};

void forceHeightDieUpdateModuleDataDeletingDestructor()
{
	HeightDieUpdateModuleData value;
}
