// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: BuffNuggetFXNugget scalar-deleting destructor at retail RVA
// 0x0042D7A0 (30 bytes). Its exact constructor at 0x0042D2B0, complete
// destructor at 0x0042D7D0, parser, and recovered field layout establish the
// class. The destructor ILT is 0x0002499C.

class BuffNuggetFXNugget
{
public:
	virtual ~BuffNuggetFXNugget();
};

void forceBuffNuggetFXNuggetDeletingDestructor()
{
	BuffNuggetFXNugget value;
}
