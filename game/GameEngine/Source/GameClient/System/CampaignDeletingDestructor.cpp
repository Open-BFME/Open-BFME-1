// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: Campaign scalar-deleting destructor at retail RVA 0x005BC790
// (30 bytes). The matched constructor at 0x005BBF40 installs vtable
// 0x0110F65C, whose slot zero routes here. The wrapper calls the complete
// destructor at 0x005BC020 through ILT 0x00025220 before operator delete.

class Campaign
{
public:
	virtual ~Campaign();
};

// The implicit copy constructor (no retail twin) emits the vftable and with
// it ??_G without a second, non-retail copy of the default constructor.
void forceCampaignDeletingDestructor(const Campaign &that)
{
	Campaign value(that);
}
