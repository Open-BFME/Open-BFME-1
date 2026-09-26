// Four more small ones: a bounded push, two tests that answer false through a
// shared exit, and a free function that ors bits into a global.
//
// The two tests differ in their return type. One hands back literal answers,
// so a bool is what it is; the other returns the result of a comparison
// straight out of setl, and only a one-byte type does that -- a bool return
// zero-extends it through another register and costs eight bytes.

class Gen_0015A260
{
public:
	void bfmePush(int value);

private:
	int m_bfmeCount;					// +0x00
	int m_bfmeItems[6];					// +0x04
};

// ?bfmePush@Gen_0015A260@@QAEXH@Z
void Gen_0015A260::bfmePush(int value)
{
	int count = m_bfmeCount;

	if (count < 6)
	{
		m_bfmeItems[count] = value;

		++m_bfmeCount;
	}
}

class BfmeThingBH
{
public:
	int m_bfmeTag;						// +0x00
	BfmeThingBH *m_bfmeNext;				// +0x04
};

class Gen_0015E750
{
public:
	bool bfmeIsAlone(void) const;

private:
	int m_bfmeHead[7];					// +0x00
	BfmeThingBH *m_bfmeThing;				// +0x1C
};

// ?bfmeIsAlone@Gen_0015E750@@QBE_NXZ
bool Gen_0015E750::bfmeIsAlone(void) const
{
	BfmeThingBH *thing = m_bfmeThing;

	if (thing != 0 && thing->m_bfmeNext == 0)
		return true;

	return false;
}

class Gen_001604C0
{
public:
	unsigned char bfmeHasRoom(void) const;

private:
	int m_bfmeHead[2];					// +0x00
	int m_bfmeClosed;					// +0x08
	int m_bfmeGap;						// +0x0C
	int m_bfmeUsed;						// +0x10
	int m_bfmeSize;						// +0x14
};

// ?bfmeHasRoom@Gen_001604C0@@QBEEXZ
unsigned char Gen_001604C0::bfmeHasRoom(void) const
{
	if (m_bfmeClosed)
		return false;

	return m_bfmeUsed < m_bfmeSize;
}

extern int g_bfmeDirtyBH;					// retail 0x012EF418

// ?bfmeMarkDirty@@YAXH@Z
void __cdecl bfmeMarkDirty(int bits)
{
	int state = g_bfmeDirtyBH;

	state |= bits;

	g_bfmeDirtyBH = state;
}
