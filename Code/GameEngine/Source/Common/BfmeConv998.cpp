// Open-BFME5 conversions.

class BfmeC998
{
public:
	virtual void bfmeVX0998();
	virtual void bfmeVX1998();
	virtual void bfmeVX2998();
	virtual void bfmeVX3998();
	virtual void bfmeApply998(int v, int a);

	void bfmeGo998C(int a);
	int bfmeConv998(int a);

	char m_bfmePad[0x14];
	int m_bfmeFlags;
};

void BfmeC998::bfmeGo998C(int a)
{
	if (m_bfmeFlags & 4)
		bfmeApply998(bfmeConv998(a), a);

	bfmeConv998(a);
}
