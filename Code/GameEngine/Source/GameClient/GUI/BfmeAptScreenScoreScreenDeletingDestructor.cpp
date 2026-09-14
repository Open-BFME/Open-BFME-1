// cl: /DNDEBUG /MD /EHsc
// stlport
//
// Open-BFME5: BfmeAptScreenScoreScreen scalar-deleting destructor at retail
// 0x00575880 (30 bytes).  The primary vtable 0x0110AAB8 and matched complete
// destructor at 0x00575050 establish the identity.

class BfmeAptScreenScoreScreen
{
public:
	virtual ~BfmeAptScreenScoreScreen();
};

void forceBfmeAptScreenScoreScreenDeletingDestructor()
{
	BfmeAptScreenScoreScreen value;
}
