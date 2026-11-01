// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for FloatUpdateModuleData.
// Constructor 0x00294F60 installs dedicated vtable 0x00CBF308; its slot
// zero routes through ILT 0x0003A125 to this 30-byte wrapper, whose complete
// destructor route ILT 0x0004129A reaches cleanup body 0x002954B0.

class FloatUpdateModuleData
{
public:
	virtual ~FloatUpdateModuleData();
private:
	friend void forceFloatUpdateModuleDataDeletingDestructor();
};

// The implicit copy constructor (no retail twin) emits the vftable and with
// it ??_G without a second, non-retail copy of the default constructor.
void forceFloatUpdateModuleDataDeletingDestructor(const FloatUpdateModuleData &that)
{
	FloatUpdateModuleData value(that);
}
