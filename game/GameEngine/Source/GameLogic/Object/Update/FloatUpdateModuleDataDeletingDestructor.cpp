// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for FloatUpdateModuleData.
// Constructor 0x00294F60 installs dedicated vtable 0x00CBF308; its slot
// zero routes through ILT 0x0003A125 to this 30-byte wrapper, whose complete
// destructor route ILT 0x0004129A reaches cleanup body 0x002954B0.

class FloatUpdateModuleData
{
protected:
	virtual ~FloatUpdateModuleData();
private:
	friend void forceFloatUpdateModuleDataDeletingDestructor();
};

void forceFloatUpdateModuleDataDeletingDestructor()
{
	FloatUpdateModuleData value;
}
