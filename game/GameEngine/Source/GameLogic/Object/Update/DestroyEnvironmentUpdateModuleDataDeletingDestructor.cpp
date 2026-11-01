// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for DestroyEnvironmentUpdateModuleData.
// Constructor 0x0028CD30 installs dedicated vtable 0x00CBDA00; its slot
// zero routes through ILT 0x00027908 to this 30-byte wrapper, whose complete
// destructor route ILT 0x00024181 reaches cleanup body 0x0028CF20.

class DestroyEnvironmentUpdateModuleData
{
public:
	virtual ~DestroyEnvironmentUpdateModuleData();
private:
	friend void forceDestroyEnvironmentUpdateModuleDataDeletingDestructor(const DestroyEnvironmentUpdateModuleData &);
};

// The implicit copy constructor (no retail twin) emits the vftable and with
// it ??_G without a second, non-retail copy of the default constructor.
void forceDestroyEnvironmentUpdateModuleDataDeletingDestructor(const DestroyEnvironmentUpdateModuleData &that)
{
	DestroyEnvironmentUpdateModuleData value(that);
}
