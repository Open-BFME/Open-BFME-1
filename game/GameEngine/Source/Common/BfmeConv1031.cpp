// Open-BFME5 conversions.
class BfmeG1031;
// Retail calls ILT 0x000139BC, which the ledger defines as ?j_000139bc@@YAXXZ.
extern void j_000139bc();
typedef void (__cdecl *BfmeFill1031Call)(BfmeG1031 *o, int *t);

class BfmeG1031
{
public:
	BfmeG1031 *bfmeGo1031G(int *out);
};

BfmeG1031 *BfmeG1031::bfmeGo1031G(int *out)
{
	int t;

	((BfmeFill1031Call)j_000139bc)(this, &t);
	*out = t;
	return this;
}

