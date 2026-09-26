// Five more tiny ones: a global field tested for zero, a float with a default
// loaded first and dropped again when there is something to read, and three
// two-part tests -- each of which keeps its branches because the condition has
// two halves.

class BfmeHolderBU
{
public:
	char m_bfmeHead[0x126C];				// +0x0000
	int m_bfmeField;					// +0x126C
};

extern BfmeHolderBU *g_bfmeHolderBU;				// retail 0x013377D8

// ?bfmeIsSet@@YAHXZ
int __cdecl bfmeIsSet(void)
{
	return g_bfmeHolderBU->m_bfmeField != 0;
}

class BfmeThingBU
{
public:
	char m_bfmeHead[0x48];					// +0x00
	float m_bfmeValue;					// +0x48
};

extern float g_bfmeDefaultBU;					// retail 0x01075334

class Gen_0079F3C0
{
public:
	float bfmeValue(void) const;

private:
	char m_bfmeHead[0x250];					// +0x000
	BfmeThingBU *m_bfmeThing;				// +0x250
};

// ?bfmeValue@Gen_0079F3C0@@QBEMXZ
float Gen_0079F3C0::bfmeValue(void) const
{
	BfmeThingBU *thing = m_bfmeThing;

	float value = g_bfmeDefaultBU;

	if (thing)
		value = thing->m_bfmeValue;

	return value;
}

class BfmeFlaggedBU
{
public:
	char m_bfmeHead[0x10];					// +0x00
	unsigned char m_bfmeFlags;				// +0x10
};

class Gen_006E7B60
{
public:
	int bfmeIsReady(void) const;

private:
	int m_bfmeHead[16];					// +0x00
	BfmeFlaggedBU *m_bfmeThing;				// +0x40
};

// ?bfmeIsReady@Gen_006E7B60@@QBEHXZ
int Gen_006E7B60::bfmeIsReady(void) const
{
	BfmeFlaggedBU *thing = m_bfmeThing;

	if (thing && (thing->m_bfmeFlags & 4))
		return 1;

	return 0;
}

class Gen_007F57E0
{
public:
	int bfmeIsThree(void) const;
	int bfmeIsFive(void) const;

private:
	int m_bfmeHead[12];					// +0x00
	int m_bfmeLevel;					// +0x30
	unsigned char m_bfmeGap;				// +0x34
	unsigned char m_bfmeReady;				// +0x35
};

// ?bfmeIsThree@Gen_007F57E0@@QBEHXZ
int Gen_007F57E0::bfmeIsThree(void) const
{
	if (m_bfmeReady && m_bfmeLevel >= 3)
		return 1;

	return 0;
}

// ?bfmeIsFive@Gen_007F57E0@@QBEHXZ
int Gen_007F57E0::bfmeIsFive(void) const
{
	if (m_bfmeReady && m_bfmeLevel >= 5)
		return 1;

	return 0;
}
