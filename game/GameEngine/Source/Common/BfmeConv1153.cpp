// cl: /Od
// Open-BFME5 conversions.

// Both callees are five-byte ILT thunks (0x00005934 and 0x00006B9A), so the
// only names defined at the addresses the retail calls encode are the ?j_
// thunk symbols.  Reference those names and type the calls through views of
// their cdecl signatures.
extern "C" void __identifier("?j_00005934@@YAXXZ")();
extern "C" void __identifier("?j_00006b9a@@YAXXZ")();

typedef void (__cdecl *BfmeCopy1153Thunk)(char *, char *, const char *, const char *);
typedef unsigned int (__cdecl *BfmeLen1153Thunk)(const char *);

// retail callee at 0x006434C0, reached through the ILT thunk at 0x000132CD;
// declaration only, the body is game/gen_small/fun_004.cpp
struct Gen_006434c0 { void m(); };

class BfmeS1153
{
public:
	void bfmeReplace1153(unsigned int pos, unsigned int n, const char *s);
	char *m_bfme00;
	char *m_bfme04;
};

void BfmeS1153::bfmeReplace1153(unsigned int pos, unsigned int n, const char *s)
{
	const unsigned int *n1;
	int n2;
	int n3;
	int n4;
	unsigned int n5;
	int n6;

	if (pos > (unsigned int)(m_bfme04 - m_bfme00))
		((Gen_006434c0 *)this)->m();

	n5 = (unsigned int)(m_bfme04 - m_bfme00) - pos;
	n1 = (n5 < n) ? &n5 : &n;
	((BfmeCopy1153Thunk)__identifier("?j_00005934@@YAXXZ"))(
		m_bfme00 + pos, m_bfme00 + pos + *n1, s,
		s + ((BfmeLen1153Thunk)__identifier("?j_00006b9a@@YAXXZ"))(s));
}
