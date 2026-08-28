extern "C" unsigned char bfmeInfoDNG[];

class BfmeOtherDNG
{
public:
	void bfmeCallDNG(void *info);
};

class BfmeThingDNG
{
public:
	BfmeOtherDNG *bfmeGoDNG(BfmeOtherDNG *other, void *spare);
};

BfmeOtherDNG *BfmeThingDNG::bfmeGoDNG(BfmeOtherDNG *other, void *spare)
{
	volatile int tmp = 0;
	other->bfmeCallDNG(bfmeInfoDNG);
	return other;
}
