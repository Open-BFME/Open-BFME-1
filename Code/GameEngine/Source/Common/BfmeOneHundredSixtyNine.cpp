// cl: /Od /GR- /EHsc-
// Whether a number falls inside a range, kept at the low end of the two and
// short of the high one. Built without the optimiser, as retail has it, and
// written twice over for the two callers.

class BfmeRangeAM
{
public:
	unsigned char bfmeInsideAM(unsigned int value) const;
	unsigned char bfmeWithinAM(unsigned int value) const;

private:
	unsigned int m_bfmeLow;			// 0x0
	unsigned int m_bfmeHigh;		// 0x4
};

unsigned char BfmeRangeAM::bfmeInsideAM(unsigned int value) const
{
	unsigned int at = value;

	return (unsigned char)((at >= m_bfmeLow && at < m_bfmeHigh) ? 1 : 0);
}

unsigned char BfmeRangeAM::bfmeWithinAM(unsigned int value) const
{
	unsigned int at = value;

	return (unsigned char)((at >= m_bfmeLow && at < m_bfmeHigh) ? 1 : 0);
}
