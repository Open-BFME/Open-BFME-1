extern "C" unsigned char bfmeInfoDCF[];

class BfmeThingDCF;

class BfmeOtherDCF
{
public:
	void bfmeCallDCF(BfmeThingDCF *self, void *info);
};

class BfmeThingDCF
{
public:
	void bfmeGoDCF(BfmeOtherDCF *other);
};

void BfmeThingDCF::bfmeGoDCF(BfmeOtherDCF *other)
{
	other->bfmeCallDCF(this, bfmeInfoDCF);
}
