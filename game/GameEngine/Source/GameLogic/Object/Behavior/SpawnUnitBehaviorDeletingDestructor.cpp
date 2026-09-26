// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for SpawnUnitBehavior.
// Vtable 0x00CA6F94 slots name this class (?getModuleNameKey@SpawnUnitBehavior@@UBE?AW4NameKeyType@@XZ); its slot zero routes
// through ILT 0x0000EC73 to this 30-byte wrapper, whose complete destructor
// route ILT 0x00035922 reaches cleanup body 0x0020D090.

class SpawnUnitBehavior
{
protected:
	virtual ~SpawnUnitBehavior();
private:
	friend void forceSpawnUnitBehaviorDeletingDestructor();
};

void forceSpawnUnitBehaviorDeletingDestructor()
{
	SpawnUnitBehavior value;
}
