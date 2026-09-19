// The callers identify this as the generic final insertion pass.  Its
// four-argument callee is the landed AV linear insert body.

class BfmeRecAU;

class BfmeCompAU
{
public:
	int m_state;
};

void __cdecl bfmeLinearInsertAV(BfmeRecAU **first, BfmeRecAU **last,
	BfmeRecAU *value, BfmeCompAU comp);

// ?Gen005317B0@@YAXPAPAX0PAX@Z
void __cdecl Gen005317B0(void **first, void **last, void *arg)
{
	if (first == last)
		return;

	void **cursor = first + 1;
	if (cursor == last)
		return;

	while (cursor != last)
	{
		void *value = *cursor;
		bfmeLinearInsertAV((BfmeRecAU **)first, (BfmeRecAU **)cursor,
			(BfmeRecAU *)value, *(BfmeCompAU *)&arg);
		++cursor;
	}
}
