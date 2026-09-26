// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: protected scalar-deleting destructor for PhysicsBehaviorModuleData.
// Constructor 0x0029A090 installs dedicated vtable 0x00CC0910; its slot
// zero routes through ILT 0x00040827 to this 30-byte wrapper, whose complete
// destructor route ILT 0x00041425 reaches cleanup body 0x0029A640.

class PhysicsBehaviorModuleData
{
protected:
	virtual ~PhysicsBehaviorModuleData();
private:
	friend void forcePhysicsBehaviorModuleDataDeletingDestructor();
};

void forcePhysicsBehaviorModuleDataDeletingDestructor()
{
	PhysicsBehaviorModuleData value;
}
