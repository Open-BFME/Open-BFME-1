// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for ClickReactionBehaviorModuleData.
// Constructor 0x002001A0 installs dedicated vtable 0x00CA4A10; its slot
// zero routes through ILT 0x000259F5 to this 30-byte wrapper, whose complete
// destructor route ILT 0x00011162 reaches cleanup body 0x00200410.

class ClickReactionBehaviorModuleData
{
protected:
	virtual ~ClickReactionBehaviorModuleData();
private:
	friend void forceClickReactionBehaviorModuleDataDeletingDestructor(const ClickReactionBehaviorModuleData &);
};

// The implicit copy constructor (no retail twin) emits the vftable and with
// it ??_G without a second, non-retail copy of the default constructor.
void forceClickReactionBehaviorModuleDataDeletingDestructor(const ClickReactionBehaviorModuleData &that)
{
	ClickReactionBehaviorModuleData value(that);
}
