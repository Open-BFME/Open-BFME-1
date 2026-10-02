class BfmeRecAU;

// ABI view of BfmeCompAU from Bfme5InsertionSort.cpp: the by-value state is
// one dword, which is the raw slot forwarded by this wrapper.
class BfmeCompAU
{
public:
	int m_bfmeState;
};

void bfmeUnguardedInsertAU(BfmeRecAU **last, BfmeRecAU *value, BfmeCompAU comp);

void bfmeGoDIB(void **begin, void **end, void *arg)
{
	while (begin != end)
	{
		bfmeUnguardedInsertAU((BfmeRecAU **)begin, (BfmeRecAU *)*begin, *(BfmeCompAU *)&arg);
		++begin;
	}
}
