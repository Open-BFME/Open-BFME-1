// Open-BFME5 conversions.
class BfmeG1031;
void bfmeFill1031(BfmeG1031 *o, int *t);

class BfmeG1031
{
public:
	BfmeG1031 *bfmeGo1031G(int *out);
};

BfmeG1031 *BfmeG1031::bfmeGo1031G(int *out)
{
	int t;

	bfmeFill1031(this, &t);
	*out = t;
	return this;
}

