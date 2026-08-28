extern "C" unsigned char bfmeInfoDNF[];

class BfmeOtherDNF
{
public:
	void bfmeCallDNF(void *info);
};

class BfmeThingDNF
{
public:
	BfmeOtherDNF *bfmeGoDNF(BfmeOtherDNF *other);
};

BfmeOtherDNF *BfmeThingDNF::bfmeGoDNF(BfmeOtherDNF *other)
{
	volatile int tmp = 0;
	other->bfmeCallDNF(bfmeInfoDNF);
	return other;
}
