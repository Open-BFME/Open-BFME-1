// Open-BFME5 conversions.

char bfmeShroudedVNI(void *ctx);

class BfmeObjVNI
{
public:
	int bfmeRelationVNI(BfmeObjVNI *o);
	char m_bfmePad000[0x90];
	unsigned char m_bfme90;
	char m_bfmePad091[0x113];
	unsigned char m_bfme1a4;
	char m_bfmePad1a5[0x19f];
	unsigned char m_bfme344;
};

char __stdcall bfmeCanSeeVNI(BfmeObjVNI *a, BfmeObjVNI *b, void *ctx)
{
	if (a != 0 && b != 0 && (b->m_bfme344 & 1) == 0 && bfmeShroudedVNI(ctx) == 0
		&& a->bfmeRelationVNI(b) == 0 && (b->m_bfme90 & 0x40) == 0)
	{
		unsigned char v = b->m_bfme1a4;

		v >>= 5;
		v = ~v;
		v &= 1;
		return (char)v;
	}
	return 0;
}
