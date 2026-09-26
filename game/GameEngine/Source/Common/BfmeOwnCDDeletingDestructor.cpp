// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME5: BfmeOwnCD scalar-deleting destructor at retail 0x00339FA0
// (30 bytes).  Its vtable at 0x00CE7688 routes slot zero here, while the
// matched complete destructor at 0x00339E20 and the existing pure-virtual
// BfmeOwnCD layout establish the class identity.

class BfmeOwnCD
{
public:
	virtual ~BfmeOwnCD();
};

void Force_BfmeOwnCD_Deleting_Destructor()
{
	BfmeOwnCD value;
}
