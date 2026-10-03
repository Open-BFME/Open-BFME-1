extern void j_00034211();

class BfmeSubBEB
{
};

class BfmeThingBEB
{
public:
	bool bfmeGoBEB();
	unsigned char m_bfmeHead[0x1e8];
	BfmeSubBEB *m_bfmeSub;
};

bool BfmeThingBEB::bfmeGoBEB()
{
	BfmeSubBEB *sub = m_bfmeSub;
	if (sub == 0)
		return false;
	return ((bool (__fastcall *)(BfmeSubBEB *))j_00034211)(sub);
}
