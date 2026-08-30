// ?d_0020dad0@@YAXXZ
// partial score=0.75 date=2026-08-30
// cl: /O2
struct BfmeTriple20DAD0 { int m_first; int m_flags; int m_third; };
struct BfmeHolder20DAD0 { char m_pad[0x90]; BfmeTriple20DAD0 m_triple; };
class BfmeThing20DAD0 { public: int bfmeChoose20DAD0() const; private: char m_pad[8]; const BfmeHolder20DAD0 *m_holder; };
int BfmeThing20DAD0::bfmeChoose20DAD0() const
{
	const BfmeTriple20DAD0 &triple = m_holder->m_triple;
	volatile BfmeTriple20DAD0 held = triple;

	return (triple.m_flags & 0x40) ? 0x1e : 0x14;
}
