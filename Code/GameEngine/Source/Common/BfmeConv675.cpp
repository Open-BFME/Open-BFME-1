extern "C" unsigned char bfmeInfoDCE[];

class BfmeThingDCE;

class BfmeOtherDCE
{
public:
	void bfmeCallDCE(BfmeThingDCE *self, void *info);
};

class BfmeThingDCE
{
public:
	void bfmeGoDCE(BfmeOtherDCE *other);
};

void BfmeThingDCE::bfmeGoDCE(BfmeOtherDCE *other)
{
	other->bfmeCallDCE(this, bfmeInfoDCE);
}
