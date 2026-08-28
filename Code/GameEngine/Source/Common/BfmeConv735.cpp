extern "C" unsigned char bfmeInfoDNC[];

class BfmeOtherDNC
{
public:
	void bfmeCallDNC(void *info);
};

class BfmeThingDNC
{
public:
	BfmeOtherDNC *bfmeGoDNC(BfmeOtherDNC *other, void *spare);
};

BfmeOtherDNC *BfmeThingDNC::bfmeGoDNC(BfmeOtherDNC *other, void *spare)
{
	volatile int tmp = 0;
	other->bfmeCallDNC(bfmeInfoDNC);
	return other;
}
