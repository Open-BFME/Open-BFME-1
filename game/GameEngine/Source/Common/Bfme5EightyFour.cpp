// Four more: a permission chain, a kind classifier, a match that accepts
// three different agreements, and a squared distance in tenths.

class BfmeThingGP
{
public:
	int m_bfmeGap[105];							// +0x000
	int m_bfmeFlags;							// +0x1a4
	unsigned char m_bfmeGap2[0x343 - 0x1a8];	// +0x1a8
	unsigned char m_bfmeBits;					// +0x343
};

class Gen_004181B0
{
public:
	bool bfmeAllows(bool strict) const;
private:
	int m_bfmeGap[63];							// +0x000
	BfmeThingGP *m_bfmeThing;					// +0x0fc
};

bool Gen_004181B0::bfmeAllows(bool strict) const
{
	BfmeThingGP *thing = m_bfmeThing;
	if (thing != 0)
	{
		if (strict && (thing->m_bfmeBits & 2) != 0)
			return false;

		int flags = thing->m_bfmeFlags;
		if (flags != 0)
		{
			if ((flags & 0x24) != 0)
				return false;
			if (strict && (flags & 0x40) != 0)
				return false;
		}
	}
	return true;
}

class BfmeThingGQ
{
public:
	int m_bfmeGap[4];							// +0x00
	int m_bfmeKind;								// +0x10
};

// The thousand block is one family, and four more numbers join it by hand.
int __stdcall bfmeKindCheck(BfmeThingGQ *thing)
{
	int kind = thing->m_bfmeKind;
	if (kind >= 1000 && kind <= 1999)
		return 0;
	if (kind == 30 || kind == 29 || kind == 2009 || kind == 2026)
		return 0;
	return kind != 31;
}

class BfmeHalfGR
{
public:
	unsigned short m_bfmeKind;					// +0x00
	unsigned short m_bfmeGap;					// +0x02
	int m_bfmeId;								// +0x04
	int m_bfmeOther;							// +0x08
	int m_bfmeGap2;								// +0x0c
};

class BfmePairGR
{
public:
	BfmeHalfGR m_bfmeA;							// +0x00
	BfmeHalfGR m_bfmeB;							// +0x10
};

bool bfmeMatches(BfmePairGR *pair)
{
	if (pair->m_bfmeA.m_bfmeKind != pair->m_bfmeB.m_bfmeKind)
		return false;

	if (pair->m_bfmeA.m_bfmeId == pair->m_bfmeB.m_bfmeId)
		return true;
	if (pair->m_bfmeA.m_bfmeId == pair->m_bfmeB.m_bfmeOther)
		return true;
	if (pair->m_bfmeA.m_bfmeOther == pair->m_bfmeB.m_bfmeId)
		return true;
	if (pair->m_bfmeA.m_bfmeOther == 16 && pair->m_bfmeB.m_bfmeOther == 16)
		return true;
	return false;
}

class BfmeAnchorGS
{
public:
	int m_bfmeGap[14];							// +0x00
	float m_bfmeX;								// +0x38
	float m_bfmeY;								// +0x3c
};

class Gen_003D80A0
{
public:
	float bfmeDistSq(int x, int y) const;
private:
	int m_bfmeGap[10];							// +0x00
	BfmeAnchorGS *m_bfmeAnchor;					// +0x28
};

float Gen_003D80A0::bfmeDistSq(int x, int y) const
{
	BfmeAnchorGS *anchor = m_bfmeAnchor;
	float dx = (float)(x * 10) - anchor->m_bfmeX;
	float dy = (float)(y * 10) - anchor->m_bfmeY;
	return dx * dx + dy * dy;
}
