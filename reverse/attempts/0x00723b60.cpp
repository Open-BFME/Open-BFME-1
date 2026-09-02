// ?d_00723b60@@YAXXZ
// partial score=0.3 date=2026-09-02
// PARTIAL / UNVERIFIED -- does not compile-match yet. Banked for the next agent.
// ghidra: FUN_00b23b60 retail @ 0x00723B60 size 184
// Sibling of BfmeA1137Getters (see attempt_723cf0.cpp for the shared global
// and 0x000022BB thunk this whole family goes through). This one reads a
// bool flag from *that global*'s offset +0x40 (NOT from `this`), then:
//   - if this->m_bfme44 (byte) is already set and this->m_bfme48 (int
//     counter) is > 1 after a decrement, just decrement and return (a
//     ref-counted "cache still warm" fast path);
//   - otherwise recomputes via x87: a call to a helper at RVA 0x008D8E00
//     (pinned "?bfmeValBC@BfmeObjBC@@QAEMXZ" -- float getter, comment says
//     "float getter for 0x0040BC50") fetching a float, compared against
//     *(float*)(other_global+0x54); on failure sets this->m_bfme44=1 and
//     recomputes this->m_bfme48 via
//       ftol2( fval * [0x01121004] + [0x01075C6C] + this->m_bfme50 * [0x0107533C] )
//     i.e. a seconds-to-frames style conversion (LOGICFRAMES_PER_SECOND-ish
//     constants) -- classic SAGE timing cache pattern, not yet pinned to a
//     named GlobalData field. __ftol2 is already pinned (RVA 0x009F6E38).
//
// Blocker: the exact x87 operand/branch order (matching.md "MSVC 7.1 shaping
// notes" -- ternary/x87 traps) and the identity of the two floating
// constants at RVA 0x01121004 / 0x01075C6C / 0x0107533C. Needs the same
// 0x0012F15F8 global identity as the rest of this family.

extern "C" void *g_bfmeGlobalUnknown1137; // RVA 0x0012F15F8, identity TBD
void __fastcall bfmeWalkLock1137(void *p); // RVA 0x000022BB thunk -> 0x00087A80
float __cdecl bfmeValBC1137(); // RVA 0x008D8E00, pinned ?bfmeValBC@BfmeObjBC@@QAEMXZ

class BfmeA1137Cache
{
public:
	void bfmeRefreshCache();
	char m_bfmePad[0x44];
	char m_bfme44;
	int m_bfme48;
	int m_bfme4c;
	int m_bfme50;
};

void BfmeA1137Cache::bfmeRefreshCache()
{
	void *g = g_bfmeGlobalUnknown1137;
	if (g)
	{
		void *inner = *(void **)((char *)g + 4);
		if (inner)
			bfmeWalkLock1137(inner);
	}
	char flag = g ? *((char *)g + 0x40) : 0;
	if (!flag)
		return;

	if (m_bfme44)
	{
		if (--m_bfme48 > 0)
			return;
		m_bfme48 = 0;
		m_bfme44 = 0;
		return;
	}

	float v = bfmeValBC1137();
	// TODO: compare v against *(float*)(other_global + 0x54); on the
	// "close enough" branch fall straight to the pop/ret at +0x15 (no cache
	// refresh) -- not modelled here yet.
	m_bfme44 = 1;
	// m_bfme48 = (int)(v * K1 + K2 + m_bfme50 * K3);  -- constants unresolved
}
