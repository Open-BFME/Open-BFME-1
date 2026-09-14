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

void forceGrantUpgradeCreateModuleDataDeletingDestructor()
{
	GrantUpgradeCreateModuleData value;
}
