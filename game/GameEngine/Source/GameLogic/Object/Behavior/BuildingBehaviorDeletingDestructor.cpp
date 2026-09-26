// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for BuildingBehavior.
// Vtable 0x00CA2C54 slots name this class (?getModuleNameKey@BuildingBehavior@@UBE?AW4NameKeyType@@XZ); its slot zero routes
// through ILT 0x0004947C to this 30-byte wrapper, whose complete destructor
// route ILT 0x0003C592 reaches cleanup body 0x001F6740.

class BuildingBehavior
{
protected:
	virtual ~BuildingBehavior();
private:
	friend void forceBuildingBehaviorDeletingDestructor();
};

void forceBuildingBehaviorDeletingDestructor()
{
	BuildingBehavior value;
}
