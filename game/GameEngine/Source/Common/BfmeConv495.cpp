void j_00040412();

class BfmeSubBNC
{
public:
};

struct BfmeOwnerBNC
{
	unsigned char m_bfmeHead[0x34];
	BfmeSubBNC *m_bfmeSub;
};

void bfmeGoBNC(BfmeOwnerBNC *owner, void *one, void *two)
{
	BfmeSubBNC *sub = owner->m_bfmeSub;
	if (sub != 0)
	{
		typedef void (BfmeSubBNC::*Call)(void *, void *);
		union { void (*address)(); Call member; } route = { j_00040412 };
		(sub->*route.member)(one, two);
	}
}
