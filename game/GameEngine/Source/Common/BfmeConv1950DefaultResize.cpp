// ?bfmeResizeERE@BfmeVecERE@@QAEXI@Z
// Retail 0x000DEE90, 37 bytes. This is the one-argument default-resize
// overload paired with the independently matched two-argument
// BfmeVecERE::bfmeResizeERE body at 0x000DEDD0. The retail call reaches that
// body through the existing five-byte thunk at 0x0000FBAF.
//
// The banked source modeled this as a free __stdcall wrapper. That leaves the
// receiver out of ECX and makes MSVC choose ECX for the zero-fill. Keeping the
// overload on the witnessed vector receiver makes ECX be `this`, reproducing
// retail's EDX zero register and the complete 37-byte body.
struct BfmeItemERE
{
public:
	BfmeItemERE() { m_at00 = 0; m_at04 = 0; m_at08 = 0; m_at0C = 0; }
	BfmeItemERE(const BfmeItemERE &other) throw()
	{
		m_at00 = other.m_at00;
		m_at04 = other.m_at04;
		m_at08 = other.m_at08;
		m_at0C = other.m_at0C;
	}
	~BfmeItemERE();

	int m_at00;
	int m_at04;
	int m_at08;
	int m_at0C;
};

class BfmeVecERE
{
public:
	void bfmeResizeERE(unsigned int count, BfmeItemERE value);
	void bfmeResizeERE(unsigned int count);
};

void BfmeVecERE::bfmeResizeERE(unsigned int count)
{
	bfmeResizeERE(count, BfmeItemERE());
}
