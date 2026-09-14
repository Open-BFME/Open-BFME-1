// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME5: FXNugget scalar-deleting destructor at retail RVA 0x00427410
// (30 bytes). Its exact constructor at 0x00428590 and complete destructor at
// 0x00427390 share the recovered FXNugget identity; the extensive constructor,
// parser, and virtual-method family corroborates it. The destructor ILT is
// 0x000033F0.

class FXNugget
{
public:
	virtual ~FXNugget();
};

void forceFXNuggetDeletingDestructor()
{
	FXNugget value;
}
