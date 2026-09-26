// cl: /O2 /Ob0 /DNDEBUG /DWIN32 /D_WINDOWS /MD

class Rva002DF120
{
public:
	unsigned char test(void *first, void *second);
};

class Object;
class Weapon;
class BfmeX1004;
class BfmeItemMD;
class BfmeX1004
{
public:
#define RVA002DCDA0_SLOT(number) virtual BfmeX1004 *slot##number() = 0;
	RVA002DCDA0_SLOT(00)
	RVA002DCDA0_SLOT(01)
	RVA002DCDA0_SLOT(02)
	RVA002DCDA0_SLOT(03)
	RVA002DCDA0_SLOT(04)
	RVA002DCDA0_SLOT(05)
	RVA002DCDA0_SLOT(06)
	RVA002DCDA0_SLOT(07)
	RVA002DCDA0_SLOT(08)
	RVA002DCDA0_SLOT(09)
	RVA002DCDA0_SLOT(10)
	RVA002DCDA0_SLOT(11)
	RVA002DCDA0_SLOT(12)
	RVA002DCDA0_SLOT(13)
	RVA002DCDA0_SLOT(14)
	RVA002DCDA0_SLOT(15)
	RVA002DCDA0_SLOT(16)
	RVA002DCDA0_SLOT(17)
	RVA002DCDA0_SLOT(18)
	RVA002DCDA0_SLOT(19)
	virtual BfmeX1004 *slot20() = 0;
	RVA002DCDA0_SLOT(21)
	RVA002DCDA0_SLOT(22)
	RVA002DCDA0_SLOT(23)
	RVA002DCDA0_SLOT(24)
	RVA002DCDA0_SLOT(25)
	RVA002DCDA0_SLOT(26)
	RVA002DCDA0_SLOT(27)
	RVA002DCDA0_SLOT(28)
	RVA002DCDA0_SLOT(29)
	RVA002DCDA0_SLOT(30)
	RVA002DCDA0_SLOT(31)
	RVA002DCDA0_SLOT(32)
	RVA002DCDA0_SLOT(33)
	RVA002DCDA0_SLOT(34)
	RVA002DCDA0_SLOT(35)
	RVA002DCDA0_SLOT(36)
	RVA002DCDA0_SLOT(37)
	RVA002DCDA0_SLOT(38)
	RVA002DCDA0_SLOT(39)
	RVA002DCDA0_SLOT(40)
	RVA002DCDA0_SLOT(41)
	RVA002DCDA0_SLOT(42)
	RVA002DCDA0_SLOT(43)
	RVA002DCDA0_SLOT(44)
	RVA002DCDA0_SLOT(45)
	RVA002DCDA0_SLOT(46)
	RVA002DCDA0_SLOT(47)
	RVA002DCDA0_SLOT(48)
	RVA002DCDA0_SLOT(49)
	RVA002DCDA0_SLOT(50)
	RVA002DCDA0_SLOT(51)
	RVA002DCDA0_SLOT(52)
	RVA002DCDA0_SLOT(53)
	RVA002DCDA0_SLOT(54)
	RVA002DCDA0_SLOT(55)
	RVA002DCDA0_SLOT(56)
	RVA002DCDA0_SLOT(57)
	RVA002DCDA0_SLOT(58)
	RVA002DCDA0_SLOT(59)
	RVA002DCDA0_SLOT(60)
	RVA002DCDA0_SLOT(61)
	virtual BfmeX1004 *slot62(int value) = 0;
#undef RVA002DCDA0_SLOT
};

class BfmeHolderMD
{
public:
	BfmeItemMD *bfmeFindMD(int slot);
};

class BfmeHold1004
{
public:
	BfmeX1004 *bfmeFind1004();
};

class BfmeThingAIA
{
public:
	bool bfmeAskAIA(int kind);
};

class GameLogic
{
public:
	Object *bfmeFind1011(int id);
};

class Weapon
{
public:
	bool bfmeCanAffect(const Object *first, const Object *second) const;
};

class Rva002DCDA0ObjectId
{
private:
	unsigned char m_padding[8];

public:
	int m_id;
};

class Rva002DCDA0 : public Rva002DF120
{
public:
	unsigned char test(void *first, void *second);
};

extern GameLogic *TheBfmeGameLogic;

unsigned char Rva002DCDA0::test(void *first, void *second)
{
	if (!Rva002DF120::test(first, second))
		return 0;

	Object *found = TheBfmeGameLogic->bfmeFind1011(
		((Rva002DCDA0ObjectId *)first)->m_id);
	if (found == 0 || *(void **)((unsigned char *)found + 0x1fc) == 0)
		return 1;

	BfmeX1004 *controller =
		((BfmeHold1004 *)found)->bfmeFind1004();
	if (controller == 0)
		return 1;
	if (((BfmeThingAIA *)found)->bfmeAskAIA(0x6d))
		controller = controller->slot20();
	else
		controller = controller->slot62(0xa3);
	if (controller == 0)
		return 1;
	if (((BfmeHolderMD *)controller)->bfmeFindMD(0) == 0)
		return 1;
	return ((Weapon *)((BfmeHolderMD *)controller)->bfmeFindMD(0))
		->bfmeCanAffect((Object *)found, (Object *)second);
}
