// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: BFMENetGameSpyStatsAuthKeyCommandMsg scalar-deleting destructor
// at retail RVA 0x00676210 (30 bytes). Its exact constructor at 0x00675BE0,
// complete destructor at 0x00675E60, and recovered text accessors and packet
// handlers establish the class. The destructor ILT is 0x0002413B.

class BFMENetGameSpyStatsAuthKeyCommandMsg
{
public:
	virtual ~BFMENetGameSpyStatsAuthKeyCommandMsg();
};

// The implicit copy constructor (no retail twin) emits the vftable and with
// it ??_G without a second, non-retail copy of the default constructor.
void forceBFMENetGameSpyStatsAuthKeyCommandMsgDeletingDestructor(const BFMENetGameSpyStatsAuthKeyCommandMsg &that)
{
	BFMENetGameSpyStatsAuthKeyCommandMsg value(that);
}
