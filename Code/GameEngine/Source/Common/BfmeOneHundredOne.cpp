// Two more: a second ten word mask with the same intersection, and an axis
// classifier.

class BfmeBitsNB
{
public:
	void bfmeAndWith(const BfmeBitsNB *other);
private:
	unsigned int m_bfmeWords[10];
};

void BfmeBitsNB::bfmeAndWith(const BfmeBitsNB *other)
{
	m_bfmeWords[0] &= other->m_bfmeWords[0];
	m_bfmeWords[1] &= other->m_bfmeWords[1];
	m_bfmeWords[2] &= other->m_bfmeWords[2];
	m_bfmeWords[3] &= other->m_bfmeWords[3];
	m_bfmeWords[4] &= other->m_bfmeWords[4];
	m_bfmeWords[5] &= other->m_bfmeWords[5];
	m_bfmeWords[6] &= other->m_bfmeWords[6];
	m_bfmeWords[7] &= other->m_bfmeWords[7];
	m_bfmeWords[8] &= other->m_bfmeWords[8];
	m_bfmeWords[9] &= other->m_bfmeWords[9];
}

extern "C" double fabs(double value);
#pragma intrinsic(fabs)

class BfmePointNC
{
public:
	float m_bfmeX;								// +0x00
	float m_bfmeY;								// +0x04
};

// Which way the offset leans, and which side of nothing it sits on.
int bfmeAxisOf(const BfmePointNC *offset)
{
	if ((float)fabs(offset->m_bfmeX) > (float)fabs(offset->m_bfmeY))
	{
		if (offset->m_bfmeX > 0.0f)
			return 1;
		return 2;
	}

	if (offset->m_bfmeY > 0.0f)
		return 0;
	return 3;
}
