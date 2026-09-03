// ?m009EC9A0@Q1Receiver0134FAAC@@QAEXH@Z
// partial score=0.85 date=2026-09-03
// cl: /DNDEBUG /MD /EHsc
// Open-BFME: Q1Receiver0134FAAC::m009EC9A0, retail 0x009EC9A0, 81 bytes.
//
// The clearing half of the m009EC970 switch (same subtract-and-two-decrements
// dispatch, same three flags at this+0x1EC/+0x1ED/+0x1EE): each arm stores
// false through bl, which MSVC zeroes once up front and reuses even for the
// dispatch subtract. Case 0 additionally clears a shared spin flag and polls
// it with Sleep(1) until a producer sets it; the flag is volatile so the
// write-then-reread and the loop re-read all stay memory traffic, matching
// retail's three absolute accesses.
//
// The spin flag lives at retail 0x0134FAA8, four bytes below the receiver
// global. Real identity unrecovered; pinned under a descriptive name as the
// address retail encodes (cf. the Image insert_unique call-target precedent).

typedef int Int;
typedef bool Bool;

extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned long);

extern volatile Bool g_q1Flag0134FAA8;

class Q1Receiver0134FAAC
{
public:
	void m009EC9A0(Int which);

private:
	unsigned char m_unmodelled_000[0x1EC];
	Bool m_flag0;						// this+0x1EC
	Bool m_flag1;						// this+0x1ED
	Bool m_flag2;						// this+0x1EE
};

void Q1Receiver0134FAAC::m009EC9A0(Int which)
{
	switch (which)
	{
		case 0:
			g_q1Flag0134FAA8 = false;
			if (g_q1Flag0134FAA8)
				break;
			m_flag0 = false;
		spin:
			Sleep(1);
			if (!g_q1Flag0134FAA8)
				goto spin;
			break;
		case 1:
			m_flag1 = false;
			break;
		case 2:
			m_flag2 = false;
			break;
	}
}
