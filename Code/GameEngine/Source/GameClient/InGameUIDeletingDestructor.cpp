// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: InGameUI scalar-deleting destructor at retail RVA 0x0044C0F0
// (30 bytes). Its exact constructor at 0x0044B800, complete destructor at
// 0x0044AE70, primary vtable, and extensive recovered interface establish the
// class. The destructor ILT is 0x0003B106.

class InGameUI
{
public:
	virtual ~InGameUI();
};

void forceInGameUIDeletingDestructor()
{
	InGameUI value;
}
