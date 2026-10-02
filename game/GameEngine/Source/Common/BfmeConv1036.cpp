// Open-BFME5 conversions.

extern "C" __declspec(dllimport) int __stdcall WaitForSingleObject(void *h, int t);

class BfmeA1036
{
public:
	BfmeA1036 *bfmeGo1036A(void *h);

	void *m_bfmeHandle;
	char m_bfmeOn;
};

BfmeA1036 *BfmeA1036::bfmeGo1036A(void *h)
{
	m_bfmeOn = 0;
	m_bfmeHandle = h;

	if (WaitForSingleObject(h, -1) != 0x102)
		m_bfmeOn = 1;

	return this;
}

// Retail 0x00804330 is ProtoMangle's own destroy routine (matched in
// game/Libraries/Source/DirtySock/Y2ProtoMangleHelpers.cpp); the call site is
// spelled as its definition spells it so the object links.
extern "C" void ProtoMangleDestroy(void *ref);

class BfmeE1036
{
public:
	void bfmeGo1036E(void);

	char m_bfmePad[8];
	void *m_bfmeP;
	char m_bfmePad2[0xc];
	int m_bfmeA;
	int m_bfmeB;
	int m_bfmeC;
};

void BfmeE1036::bfmeGo1036E(void)
{
	int z = 0;

	if (m_bfmeP != 0) {
		ProtoMangleDestroy(m_bfmeP);
		m_bfmeP = (void *)z;
	}

	m_bfmeA = z;
	m_bfmeB = z;
	m_bfmeC = z;
}
