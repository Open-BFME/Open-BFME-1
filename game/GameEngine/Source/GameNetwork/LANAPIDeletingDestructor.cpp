// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: LANAPI scalar-deleting destructor at retail RVA 0x00688740
// (30 bytes). Its exact constructor at 0x006854F0, complete destructor at
// 0x00688680, primary vtable, and extensive recovered method family establish
// the class. The destructor ILT is 0x00030224.

class LANAPI
{
public:
	virtual ~LANAPI();
};

// The implicit copy constructor (no retail twin) emits the vftable and with
// it ??_G without a second, non-retail copy of the default constructor.
void forceLANAPIDeletingDestructor(const LANAPI &that)
{
	LANAPI value(that);
}
