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

// .data slot 0x012F1028. The owning row is the GameEngine::init site that
// pushes EA's literal "TheLivingWorldLogic", so the canonical spelling of the
// datum this reads is TheLivingWorldLogic, not an address-derived one.
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

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
		reinterpret_cast<Rva003BEED0 *>(TheLivingWorldLogic)->run();
		m_byte1F = 0;
	}

	rva003A44A0(was || m_byte1C);
}
