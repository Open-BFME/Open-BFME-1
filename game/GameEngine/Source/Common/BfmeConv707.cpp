class BfmeRecAU;

// ABI view of BfmeCompAU from Bfme5InsertionSort.cpp: the by-value state is
// one dword, which is the raw slot forwarded by this wrapper.
class BfmeCompAU
{
public:
	int m_bfmeState;
};

void bfmeUnguardedInsertAV(BfmeRecAU **last, BfmeRecAU *value, BfmeCompAU comp);

void bfmeGoDID(void **begin, void **end, void *arg)
{
	while (begin != end)
	{
		bfmeUnguardedInsertAV((BfmeRecAU **)begin, (BfmeRecAU *)*begin, *(BfmeCompAU *)&arg);
		++begin;
	}
}
