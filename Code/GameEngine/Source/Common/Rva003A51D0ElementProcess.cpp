// cl: /DNDEBUG /MD /EHsc
// Address-derived reconstruction of the element step reached from
// Rva003BDE80Owner::processAll (0x003BDE80) through ILT 0x00033906.
// The two byte fields keep offset names; no semantic identity is asserted.

class BfmeHostCB
{
public:
	char bfmePopCB();
};

class Rva003BEED0
{
public:
	void run();
};

class Glo012F1028Type;
extern Glo012F1028Type *Glo012F1028;

class Gen003BDE80Element
{
public:
	void process();
	void rva003A50F0();
	void rva003A44A0(bool on);

	char m_prefix1C[0x1c];
	unsigned char m_byte1C;
	char m_gap1D[2];
	unsigned char m_byte1F;
};

void Gen003BDE80Element::process()
{
	if (!m_byte1C)
		reinterpret_cast<BfmeHostCB *>(this)->bfmePopCB();

	int was = m_byte1C;

	if (m_byte1C)
		rva003A50F0();

	if (was && !m_byte1C && m_byte1F)
	{
		reinterpret_cast<Rva003BEED0 *>(Glo012F1028)->run();
		m_byte1F = 0;
	}

	rva003A44A0(was || m_byte1C);
}
