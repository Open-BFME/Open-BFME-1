// cl: /DNDEBUG /MD /O2 /Ob2
// Retail 0x0024F730: forwards a time delta to a pinned thiscall callee.
// Identity of the owner and its two pointer members is not recovered; the
// pinned callee's class (BfmeSubKQ) is the only real name involved.
class BfmeSubKQ
{
public:
	void bfmeDoKQ(int delta, int a, int b);
};

class Rva0024F730Inner
{
public:
	unsigned char m_head[0x28];
	int m_start;
};

class Rva0024F730State
{
public:
	unsigned char m_head[0x210];
	Rva0024F730Inner *m_inner;
};

class Rva0024F730Thing
{
public:
	unsigned char m_head[8];
	int m_time;
};

class Rva0024F730Owner
{
public:
	void apply(void);

	unsigned char m_head[4];
	Rva0024F730Thing *m_thing;
	Rva0024F730State *m_state;
};

void Rva0024F730Owner::apply(void)
{
	Rva0024F730State *state = m_state;
	Rva0024F730Thing *thing = m_thing;
	Rva0024F730Inner *inner = state->m_inner;
	int now = thing->m_time;
	int start = inner->m_start;
	reinterpret_cast<BfmeSubKQ *>(inner)->bfmeDoKQ(now - start, 0, 0);
}
