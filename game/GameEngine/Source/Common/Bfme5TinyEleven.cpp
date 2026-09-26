// Four more tiny ones: a value taken from a source or zeroed, a singleton
// field tested for zero, an identity test against a singleton, and a choice
// between two fields.
//
// The two tests differ in their return type again: the one that hands back a
// comparison is a bool, which zero-extends the setne through another register
// before moving it into al; a one-byte type would stop at the setne.

class BfmeSourceCB
{
public:
	char m_bfmeHead[0x74];					// +0x00
	int m_bfmeValue;					// +0x74
};

class Gen_004AFA80
{
public:
	void bfmeTake(BfmeSourceCB *source);

private:
	int m_bfmeHead[7];					// +0x00
	int m_bfmeValue;					// +0x1C
};

// ?bfmeTake@Gen_004AFA80@@QAEXPAVBfmeSourceCB@@@Z
void Gen_004AFA80::bfmeTake(BfmeSourceCB *source)
{
	int value;

	if (source)
		value = source->m_bfmeValue;
	else
		value = 0;

	m_bfmeValue = value;
}

class BfmeThingCB
{
public:
	char m_bfmeHead[0x34];					// +0x00
	int m_bfmeField;					// +0x34
};

extern BfmeThingCB *g_bfmeThingCB;				// retail 0x012F49D0

// ?bfmeIsSet@@YA_NXZ
bool __cdecl bfmeIsSet(void)
{
	BfmeThingCB *thing = g_bfmeThingCB;

	if (!thing)
		return 0;

	return thing->m_bfmeField != 0;
}

extern void *g_bfmeCurrentCB;					// retail 0x012F7094

// ?bfmeIsCurrent@@YGEPAX@Z
unsigned char __stdcall bfmeIsCurrent(void *thing)
{
	void *current = g_bfmeCurrentCB;

	if (current && current == thing)
		return 1;

	return 0;
}

class Gen_004C3150
{
public:
	int bfmeValue(unsigned char which) const;

private:
	char m_bfmeHead[0x83C];					// +0x000
	int m_bfmeSecond;					// +0x83C
	int m_bfmeFirst;					// +0x840
};

// ?bfmeValue@Gen_004C3150@@QBEHE@Z
int Gen_004C3150::bfmeValue(unsigned char which) const
{
	if (which)
		return m_bfmeFirst;

	return m_bfmeSecond;
}
