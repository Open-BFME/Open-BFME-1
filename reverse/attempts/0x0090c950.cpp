// ?bfmeIsRawVHN@BfmeNameVHN@@QAEDXZ
// partial score=0.95 date=2026-09-07
// 142/142 EXACT SIZE. COM refresh-rate probe: slot 0x48 hands back an
// interface into a stack local, slot 0x30 fills a 32-byte descriptor, the
// first dword is range-checked 0x3c..0x40 and the interface is Released.
// EH: handler stub 0x00C5B8B8 -> FuncInfo 0x00E4A8F0 maxState 1, unwind
// funclet 0x00C5B8B0 does lea ecx,[ebp-0x34] (= the interface local) and
// tail-jumps the destructor thunk 0x0000BFAF -- so the local IS a guard
// object whose destructor is the inlined Release.
// Remaining diff (one cause, three instructions): retail ends the guard's
// lifetime INSIDE the success block -- the slot-0x48 failure branch jumps
// past the Release straight to the state=-1 store, and the state store
// follows the Release. Modelling the guard in the enclosing scope runs the
// destructor on both paths, so MSVC emits state=-1 BEFORE the Release and
// the failure branch targets it.
// Ruled out: aggregate-init of the guard inside the block from a raw
// out-parameter (adds mov esi,eax + a spill, 144 bytes); an empty inline
// destructor plus an explicit Release (MSVC drops the whole EH frame, 99
// bytes). The 4-byte pad member in the guard is what makes sub esp,0x28.
void W3DRadarResetLock();
char bfmeUnlock1179();

class BfmeIfaceEQS
{
public:
	virtual long __stdcall bfmeSlot00EQS();
	virtual long __stdcall bfmeSlot01EQS();
	virtual long __stdcall bfmeSlot02EQS();
	virtual long __stdcall bfmeSlot03EQS();
	virtual long __stdcall bfmeSlot04EQS();
	virtual long __stdcall bfmeSlot05EQS();
	virtual long __stdcall bfmeSlot06EQS();
	virtual long __stdcall bfmeSlot07EQS();
	virtual long __stdcall bfmeSlot08EQS();
	virtual long __stdcall bfmeSlot09EQS();
	virtual long __stdcall bfmeSlot10EQS();
	virtual long __stdcall bfmeSlot11EQS();
	virtual long __stdcall bfmeSlot12EQS(struct BfmeDescEQS *desc);
	virtual long __stdcall bfmeSlot13EQS();
	virtual long __stdcall bfmeSlot14EQS();
	virtual long __stdcall bfmeSlot15EQS();
	virtual long __stdcall bfmeSlot16EQS();
	virtual long __stdcall bfmeSlot17EQS();
	virtual long __stdcall bfmeSlot18EQS(int flags, BfmeIfaceEQS **out);
};

class BfmeComEQS
{
public:
	~BfmeComEQS() { m_bfmePtrEQS->bfmeSlot02EQS(); }

	int m_bfmePadEQS;
	BfmeIfaceEQS *m_bfmePtrEQS;
};

struct BfmeDescEQS
{
	int m_bfmeFieldEQS[8];
};

class BfmeNameVHN
{
public:
	char bfmeIsRawVHN();

	unsigned char m_bfmeHeadEQS[8];
	BfmeIfaceEQS *m_bfmeDevEQS;
};

char BfmeNameVHN::bfmeIsRawVHN()
{
	char ok = 0;

	if (m_bfmeDevEQS != 0)
	{
		W3DRadarResetLock();

		{
			BfmeComEQS obj;
			if (m_bfmeDevEQS->bfmeSlot18EQS(0, &obj.m_bfmePtrEQS) == 0)
			{
				BfmeDescEQS desc;
				if (obj.m_bfmePtrEQS->bfmeSlot12EQS(&desc) == 0 &&
					desc.m_bfmeFieldEQS[0] >= 0x3c && desc.m_bfmeFieldEQS[0] <= 0x40)
					ok = 1;
			}
		}

		bfmeUnlock1179();
	}

	return ok;
}
