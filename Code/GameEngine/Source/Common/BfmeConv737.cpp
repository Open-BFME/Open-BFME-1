extern "C" unsigned char bfmeInfoDNE[];

class BfmeOtherDNE
{
public:
	void bfmeCallDNE(void *info);
};

class BfmeThingDNE
{
public:
	BfmeOtherDNE *bfmeGoDNE(BfmeOtherDNE *other);
};

BfmeOtherDNE *BfmeThingDNE::bfmeGoDNE(BfmeOtherDNE *other)
{
	volatile int tmp = 0;
	other->bfmeCallDNE(bfmeInfoDNE);
	return other;
}
