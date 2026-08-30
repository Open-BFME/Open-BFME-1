// Clean reconstruction of the conditional forwarding helper at retail RVA
// 0x00942BC0.  The owning type and callee identity are not recovered; the
// address-derived declarations preserve the observed five-argument call.

class Gen_00942BC0
{
	void helper(int *local, void *first, void *second, void *third, int zero);

public:
	void process(void *first, void *second, void *third);
};

void Gen_00942BC0::process(void *first, void *second, void *third)
{
	int local[2];
	if (first != 0)
		helper(local, first, second, third, 0);
}
