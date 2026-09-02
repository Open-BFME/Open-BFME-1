// ?d_00723cf0@@YAXXZ
// partial score=0.35 date=2026-09-02
// PARTIAL / UNVERIFIED -- does not compile-match yet. Banked for the next agent.
// ghidra: FUN_00b23cf0 retail @ 0x00723CF0 size 108
// Sibling of BfmeA1137 (see Code/GameEngine/Source/Common/BfmeConv1137*.cpp):
// a setter that writes this->m_bfme98=1, this->m_bfme3d=1(byte), then copies
// three fields (offsets +0x5c, +0x60, +0x64) out of a shared global object
// pointer at RVA 0x0012F15F8 into this->m_bfme4c/0x50/0x54.
//
// Blocker: every read goes through a repeated guard shape --
//   mov eax, [g_bfmeGlobalUnknown1137]      ; DIR32 to RVA 0x0012F15F8
//   test eax, eax
//   je skip
//   mov ecx, [eax+4]
//   test ecx, ecx
//   je skip
//   call <thunk at RVA 0x000022BB>          ; -> RVA 0x00087A80 (unidentified)
//  skip:
//   mov eax, [eax+... field]
// The thunk target (0x00087A80) is a tiny "walk a next-pointer chain to the
// end" routine with no other identified caller and no pin yet; the identity
// of the RVA 0x0012F15F8 global itself (is it TheGlobalData? a device/lock
// object?) is also unresolved. Both are shared by all four sibling getters
// at 0x00723B60/0x00723C50/0x00723CF0/0x00723D80 -- solving one unlocks the
// rest.  See docs/matching.md "MSVC 7.1 shaping notes" for the general class
// of branch-layout/х87 traps this family also risks once the guard compiles.

extern "C" void *g_bfmeGlobalUnknown1137; // RVA 0x0012F15F8, identity TBD
void __fastcall bfmeWalkLock1137(void *p); // RVA 0x000022BB thunk -> 0x00087A80

class BfmeA1137Getters
{
public:
	void bfmeCopyFromGlobal();
	char m_bfmePad[0x38];
	char m_bfme3d;
	char m_bfmePad2[0xe];
	int m_bfme4c;
	int m_bfme50;
	int m_bfme54;
	char m_bfmePad3[0x40];
	int m_bfme98;
};

void BfmeA1137Getters::bfmeCopyFromGlobal()
{
	m_bfme98 = 1;
	m_bfme3d = 1;

	void *g = g_bfmeGlobalUnknown1137;
	if (g)
	{
		void *inner = *(void **)((char *)g + 4);
		if (inner)
			bfmeWalkLock1137(inner);
	}
	m_bfme4c = *(int *)((char *)g + 0x5c);

	g = g_bfmeGlobalUnknown1137;
	if (g)
	{
		void *inner = *(void **)((char *)g + 4);
		if (inner)
			bfmeWalkLock1137(inner);
	}
	m_bfme50 = *(int *)((char *)g + 0x60);

	g = g_bfmeGlobalUnknown1137;
	if (!g || *(void **)((char *)g + 4) == 0)
	{
		m_bfme54 = *(int *)((char *)g + 0x64);
		return;
	}
	bfmeWalkLock1137(*(void **)((char *)g + 4));
	m_bfme54 = *(int *)((char *)g + 0x64);
}
