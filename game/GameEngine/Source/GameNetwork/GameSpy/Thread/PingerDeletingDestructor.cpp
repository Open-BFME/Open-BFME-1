// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: Pinger scalar-deleting destructor at retail RVA 0x00661160
// (30 bytes). The exact constructor at 0x00660FD0 installs vtable 0x0111A1D0,
// whose slot zero routes through ILT 0x00047E97 to this wrapper. The recovered
// Pinger method family corroborates identity; destructor ILT is 0x00038785.

class Pinger
{
public:
	virtual ~Pinger();
};

// The implicit copy constructor (no retail twin) emits the vftable and with
// it ??_G without a second, non-retail copy of the default constructor.
void forcePingerDeletingDestructor(const Pinger &that)
{
	Pinger value(that);
}
