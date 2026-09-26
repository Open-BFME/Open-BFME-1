// Two more: a character replacement over a range and a two-bit readiness
// test.

// ?bfmeReplaceDots@@YAXPAD0D@Z
void __cdecl bfmeReplaceDots(char *first, char *last, char replacement)
{
	if (replacement == '.')
		return;

	while (first != last)
	{
		if (*first == '.')
			*first = replacement;

		++first;
	}
}

class BfmeThingDA
{
public:
	int m_bfmeHead[18];					// +0x0000
	int *m_bfmeOwner;					// +0x0048
	int m_bfmeGap[6];					// +0x004C
	int m_bfmeFlags;					// +0x0064
	int m_bfmeTail[1483];					// +0x0068
	int m_bfmeCount;					// +0x1794

	int bfmeCount(void) const
	{
		return m_bfmeCount;
	}

	void bfmeSetCount(int count)
	{
		m_bfmeCount = count;
	}
};

// ?bfmeIsReady@@YAHPBVBfmeThingDA@@@Z
int __cdecl bfmeIsReady(const BfmeThingDA *thing)
{
	if (thing == 0)
		return 0;

	if (thing->m_bfmeOwner == 0)
		return 0;

	return (thing->m_bfmeFlags & 0x30) == 0x30;
}
