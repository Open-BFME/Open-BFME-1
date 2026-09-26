// cl: /DNDEBUG /MD /EHsc
// stlport
//
// Open-BFME5: SkirmishBattleHonors scalar-deleting destructor at retail
// 0x0009C1F0 (30 bytes).  The constructor-installed vtable 0x01080460 and
// matched complete destructor at 0x0009C1E0 establish the identity.

class SkirmishBattleHonors
{
public:
	virtual ~SkirmishBattleHonors();
};

void forceSkirmishBattleHonorsDeletingDestructor()
{
	SkirmishBattleHonors value;
}
