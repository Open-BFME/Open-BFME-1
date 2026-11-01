// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for RainOfFireUpdateModuleData.
// Constructor 0x002A08B0 installs dedicated vtable 0x00CC1698; its slot
// zero routes through ILT 0x000220CF to this 30-byte wrapper, whose complete
// destructor route ILT 0x0003BF52 reaches cleanup body 0x002A0C80.

class RainOfFireUpdateModuleData
{
public:
	virtual ~RainOfFireUpdateModuleData();
private:
	friend void forceRainOfFireUpdateModuleDataDeletingDestructor(const RainOfFireUpdateModuleData &);
};

// The implicit copy constructor (no retail twin) emits the vftable and with
// it ??_G without a second, non-retail copy of the default constructor.
void forceRainOfFireUpdateModuleDataDeletingDestructor(const RainOfFireUpdateModuleData &that)
{
	RainOfFireUpdateModuleData value(that);
}
