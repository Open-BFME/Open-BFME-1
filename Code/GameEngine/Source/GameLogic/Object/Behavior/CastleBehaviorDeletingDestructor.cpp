// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: CastleBehavior scalar-deleting destructor at retail RVA
// 0x00374EF0 (30 bytes). Its exact constructor at 0x00376250, complete
// destructor at 0x003728E0, typed factory, module name, and recovered method
// family establish the class. The destructor ILT is 0x0000ADC1.

class CastleBehavior
{
public:
	virtual ~CastleBehavior();
};

void forceCastleBehaviorDeletingDestructor()
{
	CastleBehavior value;
}
