// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: public scalar-deleting destructor for GrantUpgradeCreateModuleData.
// The exact constructor at 0x0024FA80 installs dedicated vtable 0x010B17B8;
// slot zero routes through ILT 0x00040291 to this 30-byte wrapper, whose
// complete destructor is reached through ILT 0x0003DEF1.

class GrantUpgradeCreateModuleData
{
public:
	virtual ~GrantUpgradeCreateModuleData();
};

// The implicit copy constructor (no retail twin) emits the vftable and with
// it ??_G without a second, non-retail copy of the default constructor.
void forceGrantUpgradeCreateModuleDataDeletingDestructor(const GrantUpgradeCreateModuleData &that)
{
	GrantUpgradeCreateModuleData value(that);
}
