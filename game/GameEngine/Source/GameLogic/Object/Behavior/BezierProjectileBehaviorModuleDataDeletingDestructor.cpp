// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for BezierProjectileBehaviorModuleData.
// Constructor 0x001EFD50 installs dedicated vtable 0x00CA23E0; its slot
// zero routes through ILT 0x0004B06F to this 30-byte wrapper, whose complete
// destructor route ILT 0x0004A14C reaches cleanup body 0x001EFE80.

class BezierProjectileBehaviorModuleData
{
protected:
	virtual ~BezierProjectileBehaviorModuleData();
private:
	friend void forceBezierProjectileBehaviorModuleDataDeletingDestructor(const BezierProjectileBehaviorModuleData &);
};

// The implicit copy constructor (no retail twin) emits the vftable and with
// it ??_G without a second, non-retail copy of the default constructor.
void forceBezierProjectileBehaviorModuleDataDeletingDestructor(const BezierProjectileBehaviorModuleData &that)
{
	BezierProjectileBehaviorModuleData value(that);
}
