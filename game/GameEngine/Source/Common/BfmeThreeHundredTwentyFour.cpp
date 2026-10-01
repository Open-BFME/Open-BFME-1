class BfmeMemberRV
{
public:
	bool bfmeAskRV();
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
	if (!mine->bfmeAskRV())
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
