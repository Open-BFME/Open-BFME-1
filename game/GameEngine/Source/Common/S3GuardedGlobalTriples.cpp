// Five __cdecl free functions with no arguments, each firing three guarded
// __thiscall calls through three FIXED global pointers:
//
//     mov ecx,[G1] / test ecx,ecx / je .1 / call <REL32>
//  .1 mov ecx,[G2] / test ecx,ecx / je .2 / call <REL32>
//  .2 mov ecx,[G3] / test ecx,ecx / je .3 / jmp  <REL32>
//  .3 ret
//
// WHAT THE BYTES SHOW.  ecx is loaded from a global slot, not from a parameter
// and not from ecx-on-entry, so these take no `this`; nothing reads [esp+4] and
// the `ret` is bare, so they take no stack argument either.  Each callee is
// entered with ecx already holding the loaded pointer and no pushes, so each is
// a __thiscall member of no arguments.  The THIRD call is a `jmp`: it is the
// last statement, so MSVC turned it into a tail jump and the callee's `ret`
// returns to our caller -- which also fixes the return type as void.
//
// THE THREE GLOBALS ARE THE SAME THREE IN ALL FIVE ROWS, at the same three
// addresses and always in the same order, so there is one pointer global per
// slot, not five.  Only the callee triple varies: fifteen callees over five
// rows, all fifteen distinct, so each global's type carries five members and no
// (global, callee) pair repeats.
//
// IDENTITY IS NOT RECOVERED.  The names are derived from addresses.  The bytes
// cannot say what the three globals point at, whether the three types are
// related, or what any of the fifteen members do -- only that the guard, the
// order, and the tail position are as written.

#define S3_H( ADDR ) __declspec(noinline) void h##ADDR();

struct GenAlphaNode
{
	void *m_vtable;
	bool m_enabled;
	char m_unmodelled[ 0x63 ];
	GenAlphaNode *m_next;
};

struct GenBetaNode
{
	virtual void remove( bool destroy );
	bool m_enabled;
	char m_unmodelled[ 0x67 ];
	GenBetaNode *m_next;
};

class GenAlpha
{
public:
	S3_H(00044062) S3_H(00016AF4) S3_H(00024D2A) S3_H(00040601) S3_H(000053B7)
	GenAlphaNode *m_head;
	void *m_04;
	void *m_08;
};

class GenBeta
{
public:
	S3_H(00015BF4) S3_H(00008ACB) S3_H(00043743) S3_H(000217DD) S3_H(00005592)
	void *m_00;
	void *m_04;
	GenBetaNode *m_head;
};
class GenGamma { public: S3_H(0004AB42) S3_H(000131E2) S3_H(0001FE8D) S3_H(00048C70) S3_H(0000C919) };

extern GenAlpha *TheAlpha;
extern GenBeta  *TheBeta;
extern GenGamma *TheGamma;

#define S3_TRIPLE( NAME, A, B, C )                                        \
	void NAME()                                                           \
	{                                                                     \
		if( TheAlpha ) TheAlpha->h##A();                                  \
		if( TheBeta )  TheBeta->h##B();                                   \
		if( TheGamma ) TheGamma->h##C();                                  \
	}

S3_TRIPLE( Rva007B7580, 00044062, 00015BF4, 0004AB42 )
S3_TRIPLE( Rva007B75C0, 00016AF4, 00008ACB, 000131E2 )
S3_TRIPLE( Rva007B7680, 00024D2A, 00043743, 0001FE8D )
S3_TRIPLE( Rva007B7880, 00040601, 000217DD, 00048C70 )
S3_TRIPLE( Rva007B78C0, 000053B7, 00005592, 0000C919 )

void GenAlpha::h00040601()
{
	for( GenAlphaNode *node = m_head; node; node = node->m_next )
		node->m_enabled = false;
}

void GenAlpha::h000053B7()
{
	for( GenAlphaNode *node = m_head; node; node = node->m_next )
		node->m_enabled = true;
}

void GenBeta::h000217DD()
{
	for( GenBetaNode *node = m_head; node; node = node->m_next )
		node->m_enabled = false;
}

void GenBeta::h00005592()
{
	for( GenBetaNode *node = m_head; node; node = node->m_next )
		node->m_enabled = true;
}
