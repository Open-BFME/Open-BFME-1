// The selector table at the callers identifies this as the generic final
// insertion pass. Its four-argument callee is the landed BfmeRecAU insert.

class BfmeRecAU;

class BfmeCompAU
{
public:
	int m_state;
};

void __cdecl bfmeLinearInsertAU(BfmeRecAU **first, BfmeRecAU **last,
	BfmeRecAU *value, BfmeCompAU comp);

// ?Gen005139E0@@YAXPAPAX0PAX@Z
void __cdecl Gen005139E0(void **first, void **last, void *arg)
{
	if (first == last)
		return;

	void **cursor = first + 1;
	if (cursor == last)
		return;

	while (cursor != last)
	{
		void *value = *cursor;
		bfmeLinearInsertAU((BfmeRecAU **)first, (BfmeRecAU **)cursor,
			(BfmeRecAU *)value, *(BfmeCompAU *)&arg);
		++cursor;
	}
}
