// 0x000179BD is retail's 5-byte ILT thunk (?j_000179bd@@YAXXZ); the
// __thiscall member behind it is routed through the thunk's address.
extern void j_000179bd();

class BfmeMemberRV
{
public:
	bool askRV()
	{
		typedef bool (BfmeMemberRV::*Call)();
		union { void *raw; Call method; } u;
		u.raw = (void *)j_000179bd;
		return (this->*u.method)();
	}
};

struct BfmeWorldRV
{
	unsigned char m_bfmeHead[0x274];
	BfmeMemberRV *m_bfmeOther;
};

class ControlBar;

extern ControlBar *TheControlBar;

class BfmeThingRV
{
public:
	BfmeMemberRV *bfmePickRV();
	unsigned char m_bfmeHead[0xc];
	BfmeMemberRV *m_bfmeMine;
};

BfmeMemberRV *BfmeThingRV::bfmePickRV()
{
	BfmeMemberRV *mine = m_bfmeMine;
	if (mine == 0)
		return 0;
	if (!mine->askRV())
	{
		BfmeWorldRV *world = (BfmeWorldRV *)TheControlBar;
		if (world != 0)
		{
			BfmeMemberRV *other = world->m_bfmeOther;
			if (other != 0)
				return other;
		}
	}
	return mine;
}
