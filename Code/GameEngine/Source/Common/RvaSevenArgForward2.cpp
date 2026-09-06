// Open-BFME5 conversions. Address-derived name: no recovered owner/source declaration.
// Duplicate of Rva000C13E0 (RvaSevenArgForward.cpp) at a different retail address, same callee.

void __cdecl bfmeDoSevenRL(void *a1, void *a2, void *a3, void *a4, void *a5, void **a6, int a7);

void *Rva000C1500(void *a1, void *a2, void *a3, void *a4, void *a5, void *a6, void *a7)
{
	void *slot;
	bfmeDoSevenRL(a1, a2, a3, a4, a5, &slot, 0);
	return a1;
}
