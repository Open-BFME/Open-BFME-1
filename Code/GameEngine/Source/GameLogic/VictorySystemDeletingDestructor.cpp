// cl: /DNDEBUG /MD /EHsc
// stlport
//
// Open-BFME5: VictorySystem scalar-deleting destructor at retail
// 0x001E02F0 (30 bytes).  The constructor-installed vtable 0x0109FD8C
// and matched complete destructor at 0x001DFF40 establish the identity.

class VictorySystem
{
public:
	virtual ~VictorySystem();
};

void forceVictorySystemDeletingDestructor()
{
	VictorySystem value;
}
