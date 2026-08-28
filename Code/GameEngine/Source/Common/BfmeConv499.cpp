extern "C" unsigned char bfmeTagBNH[];

class BfmeThingBNH;

void bfmeDoBNH(BfmeThingBNH *who, void *tag, int one, int two);

class BfmeThingBNH
{
public:
	BfmeThingBNH *bfmeGoBNH(void *what);
};

BfmeThingBNH *BfmeThingBNH::bfmeGoBNH(void *what)
{
	bfmeDoBNH(this, bfmeTagBNH, 0, 0);
	return this;
}
