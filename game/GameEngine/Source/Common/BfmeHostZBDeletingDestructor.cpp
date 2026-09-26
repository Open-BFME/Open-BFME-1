// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME5: BfmeHostZB scalar-deleting destructor at retail 0x0045B2B0
// (30 bytes).  The vftable at 0x00CF6898 is installed by the matched
// BfmeHostZB complete destructor at 0x0045B060; its subsystem ownership and
// existing BfmeHostZB member/callback family establish this wrapper identity.

class BfmeHostZB
{
public:
	virtual ~BfmeHostZB();
};

void Force_BfmeHostZB_Deleting_Destructor()
{
	BfmeHostZB value;
}
