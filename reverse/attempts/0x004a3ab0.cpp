// ?d_004a3ab0@@YAXXZ
// partial score=0.9 date=2026-08-30
// cl: /O2
struct BfmeSix4A3AB0 { int m_a, m_b, m_c, m_d, m_e, m_f; };
class BfmeThing4A3AB0 { public: void bfmeGet4A3AB0(BfmeSix4A3AB0 *out) const; private: char m_pad[0x15c]; BfmeSix4A3AB0 m_value; };
void BfmeThing4A3AB0::bfmeGet4A3AB0(BfmeSix4A3AB0 *out) const
{
	const BfmeSix4A3AB0 &value = m_value;

	*out = value;
}
