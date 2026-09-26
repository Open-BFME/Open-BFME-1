// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// Open-BFME7: BfmeOwnVVB scalar-deleting destructor at retail RVA
// 0x00191380 (30 bytes). The matched constructors at 0x00190340 and
// 0x001903F0 establish the owner layout, and the complete destructor at
// 0x00190490 installs vtable 0x0109BFAC while releasing the owned array,
// node list, inline BfmeElemBX array and strings.

class BfmeOwnVVB
{
public:
	virtual ~BfmeOwnVVB();
};

void forceBfmeOwnVVBDeletingDestructor()
{
	BfmeOwnVVB value;
}
