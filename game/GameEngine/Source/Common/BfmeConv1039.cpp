// Open-BFME5 conversions.

struct BfmeRec1039
{
	int m_bfmeKind;
	char m_bfmePad[4];
	int m_bfmeVal;
	char m_bfmePad2[4];
};

struct BfmeQ1039
{
	BfmeRec1039 *m_bfmeCur;
	char m_bfmePad[4];
	BfmeRec1039 *m_bfmeEnd;
};

// Retail's callee at 0x009959C0 is Lua 4.0.1's luaD_checkstack, vendored in
// game/Libraries/Source/Lua/ldo.c (declared in ldo.h). BfmeQ1039 is this TU's
// view of lua_State; only that one call is needed here, so no Lua header is
// pulled into this TU.
extern "C" void luaD_checkstack(void *state, int n);

void bfmeGo1039E(BfmeQ1039 *q, int v)
{
	q->m_bfmeCur->m_bfmeKind = 6;
	q->m_bfmeCur->m_bfmeVal = v;

	if (q->m_bfmeCur == q->m_bfmeEnd)
		luaD_checkstack(q, 1);

	q->m_bfmeCur++;
}
