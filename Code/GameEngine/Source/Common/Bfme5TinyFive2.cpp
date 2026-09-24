// Five more tiny ones: a setter that only writes when the value changes, a
// pair handed back through a pointer, a float with a global default, a flag
// that clears its neighbour when cleared, and a mark set through two hops.

class Gen_0043AD70
{
public:
	void bfmeSetMode(unsigned char value);
	void bfmeGetPair(int *out) const;

private:
	char m_bfmeHead[0x821];					// +0x000
	unsigned char m_bfmeMode;				// +0x821
	char m_bfmeGap[0xE];					// +0x822
	int m_bfmeFirst;					// +0x830
	int m_bfmeSecond;					// +0x834
};

class BfmeThingBR
{
public:
	char m_bfmeHead[0x44];					// +0x00
	float m_bfmeValue;					// +0x44
};

extern float g_bfmeDefaultBR;					// retail 0x01075350

class Gen_0043B230
{
public:
	float bfmeValue(void) const;

private:
	char m_bfmeHead[0x53C];					// +0x000
	BfmeThingBR **m_bfmeSlot;				// +0x53C
};

// ?bfmeValue@Gen_0043B230@@QBEMXZ
float Gen_0043B230::bfmeValue(void) const
{
	BfmeThingBR *thing = *m_bfmeSlot;

	if (thing)
		return thing->m_bfmeValue;

	return g_bfmeDefaultBR;
}

class Gen_002A5970
{
public:
	void bfmeSetHeld(unsigned char value);

private:
	char m_bfmeHead[0xDC];					// +0x00
	unsigned char m_bfmeOther;				// +0xDC
	unsigned char m_bfmeGap;				// +0xDD
	unsigned char m_bfmeHeld;				// +0xDE
};

// ?bfmeSetHeld@Gen_002A5970@@QAEXE@Z
void Gen_002A5970::bfmeSetHeld(unsigned char value)
{
	m_bfmeHeld = value;

	if (!value)
		m_bfmeOther = value;
}

class BfmeTargetBR
{
public:
	char m_bfmeHead[0x14];					// +0x00
	unsigned char m_bfmeFlag;				// +0x14
};

class BfmeOwnerBR
{
public:
	char m_bfmeHead[0x78];					// +0x00
	BfmeTargetBR *m_bfmeTarget;				// +0x78
};

extern BfmeOwnerBR *g_bfmeOwnerBR;				// retail 0x012F060C

