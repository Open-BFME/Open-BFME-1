// cl: /DNDEBUG /MD

// Open-BFME5: Gen003BF540Owner::consume, retail 0x003CAE40, 89 bytes.
// Called from Rva003BF540::act at 0x003BD8D0 through ILT 0x0002E54B.
//
// The 1-arg pin is the caller's spelling; the body itself is a thiscall that
// cleans 16 bytes, so four stack arguments. Arg2 is the built object whose
// dword at +0xB4 is passed twice to the same cdecl helper the 45-byte
// bfmeGoFHA at 0x003CAE00 uses. A 1 result, or a null arg2, returns false.
// A null arg1 returns true. Otherwise the holder at +4 yields a subobject
// at +0x3C that is called with (arg1+4, arg2+4, arg3, arg4).

int __cdecl bfmeCallFHA(void *a, void *b);

class BfmeObjHC
{
public:
	bool bfmeDoHC(void *a, void *b, void *c, int d);
};

class Gen003CAE40Hold
{
public:
	char m_bfmeHead[0x3C];
	BfmeObjHC *m_bfmeSub;					// +0x3C
};

class Gen003BD8D0Built
{
public:
	char m_bfmeHead[0xB4];
	void *m_bfmeP;							// +0xB4
};

class Gen003BF540Owner
{
public:
	bool consume(void *a, Gen003BD8D0Built *b, void *c, void *d);

	char m_bfmeHead[0x04];
	Gen003CAE40Hold *m_bfmeHold;			// +0x04
};

// ?consume@Gen003BF540Owner@@QAE_NPAXPAVGen003BD8D0Built@@00@Z
bool Gen003BF540Owner::consume(void *a, Gen003BD8D0Built *b, void *c, void *d)
{
	if (!b)
		return false;
	void *p = b->m_bfmeP;
	if (bfmeCallFHA(p, p) == 1)
		return false;
	if (!a)
		return true;
	void *arg4 = d;
	Gen003CAE40Hold *hold = m_bfmeHold;
	BfmeObjHC *sub = hold->m_bfmeSub;
	return sub->bfmeDoHC((char *)a + 4, (char *)b + 4, c, (int)arg4);
}
