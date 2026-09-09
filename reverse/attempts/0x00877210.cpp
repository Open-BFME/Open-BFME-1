// Near-match attempt for BYTEmark LoadAssignArrayWithRand.
// partial score=0.85 date=2026-09-09
// The retail body calls fillRandom008747F0, then copies the first 101x101
// array into each subsequent array using an internal register-optimized ABI.
static void LoadAssignArrayWithRand_attempt(farlong *arraybase, ulong numarrays)
{
    farlong *abase1;
    LoadAssign(reinterpret_cast<farlong (*)[ASSIGNCOLS]>(arraybase));
    for (ulong i = 1; i < numarrays; ++i)
    {
        abase1 = arraybase + i * ASSIGNROWS * ASSIGNCOLS;
        CopyToAssign(reinterpret_cast<farlong (*)[ASSIGNCOLS]>(arraybase),
            reinterpret_cast<farlong (*)[ASSIGNCOLS]>(abase1));
    }
}
