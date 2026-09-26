// Open-BFME5 conversions.

struct BfmeV1207
{
	int m_bfme00;
	int m_bfme04;
};

class BfmeA1207
{
public:
	void bfmeDo1207(const BfmeV1207 &a1, const BfmeV1207 &a2, const BfmeV1207 &a3,
		const BfmeV1207 &a4, const BfmeV1207 &a5, const BfmeV1207 &a6, int a7);
};

void bfmeGo1207(BfmeA1207 *o, const BfmeV1207 *a1, const BfmeV1207 *a2, const BfmeV1207 *a3,
	const BfmeV1207 *a4, const BfmeV1207 *a5, const BfmeV1207 *a6)
{
	o->bfmeDo1207(BfmeV1207(*a1), BfmeV1207(*a2), BfmeV1207(*a3),
		BfmeV1207(*a4), BfmeV1207(*a5), BfmeV1207(*a6), -1);
}
