// cl: /DNDEBUG /MD /EHsc
// Two-call thiscall chain: forwards to the base call at ILT 0x0004ADB3 (still
// a dump at 0x0040DE00), then tail-calls a member at this+0x278 whose ILT is
// 0x0002F7FC (still a dump at 0x006E8310, described elsewhere as a
// W3DDisplay transition-state sub-object). Neither callee carries a proven
// name, so this lands under an address-derived name per the exact-match rule.

void j_0004adb3();
extern void j_0002f7fc();

class MemberUnknown006E85D0
{
};

template <class R>
__forceinline R call0(void (*p)(), void *self)
{
	typedef R (MemberUnknown006E85D0::*F)();
	union { void (*p)(); F f; } u;
	u.p = p;
	return (((MemberUnknown006E85D0 *)self)->*u.f)();
}

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
	call0<void>(j_0002f7fc, &m_transition);
}
