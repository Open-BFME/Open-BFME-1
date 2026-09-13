// cl: /DNDEBUG /MD /EHsc
// Two-call thiscall chain: forwards to the base call at ILT 0x0004ADB3 (still
// a dump at 0x0040DE00), then tail-calls a member at this+0x278 whose ILT is
// 0x0002F7FC (still a dump at 0x006E8310, described elsewhere as a
// W3DDisplay transition-state sub-object). Neither callee carries a proven
// name, so this lands under an address-derived name per the exact-match rule.

void j_0004adb3();

class MemberUnknown006E85D0
{
public:
	void bfmeCall2(void);
};

class Chain006E85D0
{
public:
	void forwardThenTransition(void);

private:
	unsigned char m_pad[0x278];
	MemberUnknown006E85D0 m_transition;
};

void Chain006E85D0::forwardThenTransition(void)
{
	j_0004adb3();
	m_transition.bfmeCall2();
}
