// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for SpawnTownsmenBehavior.
// Vtable 0x00CA6DD4 slots name this class (?getModuleNameKey@SpawnTownsmenBehavior@@UBE?AW4NameKeyType@@XZ); its slot zero routes
// through ILT 0x0002631E to this 30-byte wrapper, whose complete destructor
// route ILT 0x00007D8D reaches cleanup body 0x0020CC30.

class SpawnTownsmenBehavior
{
protected:
	virtual ~SpawnTownsmenBehavior();
private:
	friend void forceSpawnTownsmenBehaviorDeletingDestructor();
};

void forceSpawnTownsmenBehaviorDeletingDestructor()
{
	SpawnTownsmenBehavior value;
}
