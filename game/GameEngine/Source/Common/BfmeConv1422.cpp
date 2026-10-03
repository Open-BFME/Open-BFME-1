// cl: /Od

extern "C" void *memset(void *d, int c, unsigned n);
#pragma intrinsic(memset)

// The 0x0082EE30 body's two allocators, by the names the ledger defines at
// those addresses. 0x0082E450 is ?bfmeSmallAllocPR@@YAPAXI@Z, matched at
// game/GameEngine/Source/Common/BfmeSmallAllocPR.cpp; 0x00037C54 is the
// five-byte ILT thunk ?j_00037c54@@YAXXZ, reached through a `void(void)`
// gen-thunk declaration, so the call goes through a cast that supplies the one
// stack argument retail pushes and reads eax back.
extern void *bfmeSmallAllocPR(unsigned n);

extern void j_00037c54();

typedef void *(*BfmeBigAllocVLW)(unsigned n);

struct BfmeHdrVLW
{
	unsigned m_bfmeTag : 16;
	unsigned m_bfmeVer : 16;
	unsigned m_bfmeSize;
	unsigned m_bfmePad08;
	unsigned m_bfmePad0c;
};

void *bfmeAllocVLW(unsigned n)
{
	BfmeHdrVLW *n1;
	unsigned n3;
	unsigned n2;

	n3 = n + 0x18;
	if (n3 > 0x80)
		n2 = (unsigned)reinterpret_cast<BfmeBigAllocVLW>(j_00037c54)(n3);
	else
		n2 = (unsigned)bfmeSmallAllocPR(n3);
	n1 = (BfmeHdrVLW *)n2;
	memset(n1, 0xa3, n3);
	n1->m_bfmeTag = 0xdeba;
	n1->m_bfmeVer = 1;
	n1->m_bfmeSize = n;
	return n1 + 1;
}
