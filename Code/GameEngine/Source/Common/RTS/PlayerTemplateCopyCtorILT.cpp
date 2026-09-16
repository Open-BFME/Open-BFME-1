// cl: /DNDEBUG /MD /O2
// Address-preserving clean C++ spelling of the incremental-link thunk at
// 0x0001449D. The target is the independently proven PlayerTemplate copy body
// at 0x000E2E50; the opaque name makes no second identity claim.

void dup_000e2e50(void);

void j_0001449d(void)
{
	dup_000e2e50();
}
