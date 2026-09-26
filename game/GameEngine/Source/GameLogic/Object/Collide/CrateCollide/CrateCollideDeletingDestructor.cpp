// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: CrateCollide protected scalar-deleting destructor at retail RVA
// 0x00217700 (30 bytes). Its exact constructor at 0x00217660, the six official
// derived crate-collision classes, and the shared complete-destructor chain at
// 0x00217620 establish the base. The wrapper calls the destructor through ILT
// 0x0004B68C before conditionally invoking operator delete.

class CrateCollide
{
	friend void forceCrateCollideDeletingDestructor();

protected:
	virtual ~CrateCollide();
};

void forceCrateCollideDeletingDestructor()
{
	CrateCollide value;
}
