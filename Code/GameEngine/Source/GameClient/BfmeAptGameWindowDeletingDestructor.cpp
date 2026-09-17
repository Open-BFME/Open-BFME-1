// cl: /DNDEBUG /MD /EHsc
// stlport
//
// Open-BFME5: _bfme_AptGameWindow scalar-deleting destructor at retail
// 0x00465500 (30 bytes).  The constructor-installed vtables
// 0x010F711C/0x010F7118 and matched complete destructor at 0x00465430
// establish the identity.

class _bfme_AptGameWindow
{
public:
	virtual ~_bfme_AptGameWindow();
};

void forceBfmeAptGameWindowDeletingDestructor()
{
	_bfme_AptGameWindow value;
}
