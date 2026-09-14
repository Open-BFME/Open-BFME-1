// cl: /DNDEBUG /MD /EHsc /O2
//
// Open-BFME: BfmeAptScreenOnlineCustomMatch scalar-deleting destructor at
// retail RVA 0x00539720 (30 bytes).  The exact screen constructor at
// 0x00545310 installs primary vtable 0x01107484 whose first slot reaches
// this wrapper through ILT 0x00027D4F; the matched complete destructor at
// 0x00538CE0 tears down the online custom-match screen and its members.

class BfmeAptScreenOnlineCustomMatch
{
public:
	virtual ~BfmeAptScreenOnlineCustomMatch();
};

void forceBfmeAptScreenOnlineCustomMatchDeletingDestructor()
{
	BfmeAptScreenOnlineCustomMatch value;
}
