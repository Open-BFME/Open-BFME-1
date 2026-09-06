// ?bfmeMarkAZ@BfmeOwnAZ@@QAEXPAX@Z (identity unknown)
// partial score=0.88 date=2026-09-06
// 47/48. The negative-offset load is settled: `mov ecx,[esi-0x18]` is a plain
// cast on this (see negative-this-is-raw-arithmetic), and the shrink-wrapped
// `pop esi` between the test and the branch falls out on its own.
// Residue: retail materialises the 0x400 mask into eax and uses it twice
// (`mov eax,0x400` / `test eax,edx` / `or edx,eax`), while MSVC folds it into
// `test ah,4` and `or eax,0x400`, saving one byte. Tried a named int local for
// the mask, a separate local for the loaded flags, and an inline setter on the
// host class taking the bit as its parameter. All fold. Constant-hoisting
// class, same wall as 0x00511830.
class BfmeHostAZ
{
public:
	void bfmeNotifyAZ(void);	// pin at thunk 0x0002191D

	unsigned char m_bfmeHeadAZ[0x110];
	int m_bfmeFlagsAZ;
};

class BfmeOwnAZ
{
public:
	void bfmeMarkAZ(void *value);
	void bfmeForwardAZ(void *value);	// pin at thunk 0x00005C22
};

void BfmeOwnAZ::bfmeMarkAZ(void *value)
{
	bfmeForwardAZ(value);

	BfmeHostAZ *host = *(BfmeHostAZ **)((char *)this - 0x18);
	int flags = host->m_bfmeFlagsAZ;
	int bit = 0x400;

	if ((flags & bit) == 0)
	{
		host->m_bfmeFlagsAZ = flags | bit;
		host->bfmeNotifyAZ();
	}
}
