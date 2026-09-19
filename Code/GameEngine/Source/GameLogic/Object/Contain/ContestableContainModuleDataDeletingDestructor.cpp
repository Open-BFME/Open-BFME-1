// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: public scalar-deleting destructor for ContestableContainModuleData.
// The exact constructor at 0x00249B50 installs dedicated vtable 0x010AFE60;
// slot zero routes through ILT 0x000028E7 to this 30-byte wrapper, whose
// complete destructor is reached through ILT 0x0001871E.

class ContestableContainModuleData
{
public:
	virtual ~ContestableContainModuleData();
};

void forceContestableContainModuleDataDeletingDestructor()
{
	ContestableContainModuleData value;
}
