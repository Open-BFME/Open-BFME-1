extern "C" unsigned char bfmeInfoDCG[];

class BfmeThingDCG;

class BfmeOtherDCG
{
public:
	void bfmeCallDCG(BfmeThingDCG *self, void *info);
};

class BfmeThingDCG
{
public:
	void bfmeGoDCG(BfmeOtherDCG *other);
};

void BfmeThingDCG::bfmeGoDCG(BfmeOtherDCG *other)
{
	other->bfmeCallDCG(this, bfmeInfoDCG);
}
