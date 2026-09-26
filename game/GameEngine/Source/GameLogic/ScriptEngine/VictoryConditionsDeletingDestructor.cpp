// cl: /DNDEBUG /MD /EHsc
// stlport
//
// Open-BFME5: VictoryConditions scalar-deleting destructor at retail
// 0x0035F8F0 (30 bytes).  The constructor-installed vtable 0x010E8D90
// and matched complete destructor at 0x0035F880 establish the identity.

class VictoryConditions
{
public:
	virtual ~VictoryConditions();
};

void forceVictoryConditionsDeletingDestructor()
{
	VictoryConditions value;
}
