// ?d_0082be90@@YAXXZ
// partial score=0.7 date=2026-08-30
// cl: /Od
class BfmeChar82BE90 { public: bool bfmeDiffers82BE90(const BfmeChar82BE90 *other) const; private: char m_value; };
bool BfmeChar82BE90::bfmeDiffers82BE90(const BfmeChar82BE90 *other) const
{
	return !((other->m_value - m_value) == 0 ? true : false);
}
