// ?bfmeUnlinkZN@Rva0035E710Owner@@QAEXPAXPAPAUBfmeNodeZN@@PAU2@00@Z
// partial score=0.98 date=2026-09-22
struct BfmeNodeZN
{
	BfmeNodeZN *m_bfmeNextZN;
};

class Rva0035E710Owner {
public:
 void bfmeDoZN(void *a, BfmeNodeZN **link, void *what);
 void bfmeUnlinkZN(void *a, BfmeNodeZN **link, BfmeNodeZN *target, void *fallback, void *chosen);
};

void Rva0035E710Owner::bfmeUnlinkZN(void *a, BfmeNodeZN **link, BfmeNodeZN *target,
                            void *fallback, void *chosen)
{
	BfmeNodeZN *cur = *link;

	while (cur != target)
	{
		if (cur == 0)
			return;

		link = &cur->m_bfmeNextZN;
		cur = *link;
	}

	bfmeDoZN(a, link, chosen != 0 ? chosen : fallback);
}
