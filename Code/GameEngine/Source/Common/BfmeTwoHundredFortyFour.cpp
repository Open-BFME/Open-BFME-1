// Which of two keys comes first. The leading number settles it outright; after
// that a key that is marked ranks against another marked one on its next two
// numbers, an unmarked one ranks behind any marked one, and two unmarked ones
// are settled by their last number.

struct BfmeKeyOD
{
	int m_bfmeFirst;			// 0x00
	unsigned char m_bfmeOn;			// 0x04
	unsigned char m_bfmePad[3];		// 0x05
	int m_bfmeThird;			// 0x08
	int m_bfmeFourth;			// 0x0c
	int m_bfmeFifth;			// 0x10
};

unsigned char bfmeLessOD(const BfmeKeyOD *left, const BfmeKeyOD *right)
{
	if (left->m_bfmeFirst < right->m_bfmeFirst)
		return 1;

	if (left->m_bfmeFirst > right->m_bfmeFirst)
		return 0;

	if (left->m_bfmeOn != 0)
	{
		if (right->m_bfmeOn == 0)
			return 0;

		if (left->m_bfmeThird < right->m_bfmeThird)
			return 1;

		if (left->m_bfmeThird <= right->m_bfmeThird)
			return (unsigned char)(left->m_bfmeFourth > right->m_bfmeFourth);

		return 0;
	}

	if (right->m_bfmeOn != 0)
		return 1;

	return (unsigned char)(left->m_bfmeFifth < right->m_bfmeFifth);
}
