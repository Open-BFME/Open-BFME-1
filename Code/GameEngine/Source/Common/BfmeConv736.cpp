extern "C" unsigned char bfmeInfoDND[];

class BfmeOtherDND
{
public:
	void bfmeCallDND(void *info);
};

class BfmeThingDND
{
public:
	BfmeOtherDND *bfmeGoDND(BfmeOtherDND *other);
};

BfmeOtherDND *BfmeThingDND::bfmeGoDND(BfmeOtherDND *other)
{
	volatile int tmp = 0;
	other->bfmeCallDND(bfmeInfoDND);
	return other;
}
