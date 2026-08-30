// ?d_000c8410@@YAXXZ
// partial score=0.93 date=2026-08-30
// cl: /O2
struct BfmeFlagsC8410 { char m_pad[0xc8]; unsigned char m_flags; };
class BfmeTableC8410 { public: float bfmeLookupC8410(int index, const BfmeFlagsC8410 *flags) const; private: float m_values[1]; };
float BfmeTableC8410::bfmeLookupC8410(int index, const BfmeFlagsC8410 *flags) const
{
	int bit = flags->m_flags >> 7;

	return m_values[bit + index * 2];
}
