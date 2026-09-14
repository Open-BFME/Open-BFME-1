// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: ScoreKeeper scalar-deleting destructor at retail RVA 0x000E9FE0
// (30 bytes). The exact constructor at 0x000EA390 installs vtable 0x01084DF0,
// whose slot zero routes through ILT 0x00026B75 to this wrapper. The complete
// destructor is reached through ILT 0x0002CD7C.

class ScoreKeeper
{
public:
	virtual ~ScoreKeeper();
};

void forceScoreKeeperDeletingDestructor()
{
	ScoreKeeper value;
}
