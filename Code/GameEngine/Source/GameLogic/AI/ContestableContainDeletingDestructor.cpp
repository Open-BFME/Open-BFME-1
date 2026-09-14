// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: ContestableContain scalar-deleting destructor at retail RVA
// 0x0021C050 (30 bytes). The exact constructor at 0x0021BEE0 and complete
// destructor at 0x0021B6F0 share vtable 0x00CAB3C0; the typed instance factory
// and updateObject method corroborate the class. The dtor ILT is 0x0004A674.

class ContestableContain
{
public:
	virtual ~ContestableContain();
};

void forceContestableContainDeletingDestructor()
{
	ContestableContain value;
}
