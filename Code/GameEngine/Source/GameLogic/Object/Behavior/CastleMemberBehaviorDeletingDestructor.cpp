// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: CastleMemberBehavior scalar-deleting destructor at retail RVA
// 0x0036CF10 (30 bytes). Its exact constructor at 0x0036CEA0, complete
// destructor at 0x0036BBA0, typed factory, module name, and lookup helper
// establish the class. The destructor ILT is 0x0003FB89.

class CastleMemberBehavior
{
public:
	virtual ~CastleMemberBehavior();
};

void forceCastleMemberBehaviorDeletingDestructor()
{
	CastleMemberBehavior value;
}
