// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: PhysicsBehavior scalar-deleting destructor at retail RVA
// 0x0029AC10 (30 bytes). Its exact constructor at 0x0029A880, complete
// destructor at 0x0029AA30, factories, module name, and vtable family
// establish the class. The destructor ILT is 0x000087D8.

class PhysicsBehavior
{
public:
	virtual ~PhysicsBehavior();
};

void forcePhysicsBehaviorDeletingDestructor()
{
	PhysicsBehavior value;
}
