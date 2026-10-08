class BfmeRefCHB;

// retail ILT 0x0003FA7B -> 0x0058C4C0 is the matched ~UpgradeMuxData row and
// 0x00881EB0 the matched operator delete
class UpgradeMuxData
{
public:
	~UpgradeMuxData();
};

class BfmeThingCHB
{
public:
	void bfmeGoCHB(BfmeRefCHB *what);
	BfmeRefCHB *m_bfmeRef;
};


void BfmeThingCHB::bfmeGoCHB(BfmeRefCHB *what)
{
	BfmeRefCHB *cur = m_bfmeRef;
	if (what != cur)
	{
		if (cur != 0)
		{
			((UpgradeMuxData *)cur)->~UpgradeMuxData();
			operator delete(cur);
		}
		m_bfmeRef = what;
	}
}
