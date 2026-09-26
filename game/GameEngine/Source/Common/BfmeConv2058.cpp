class BfmeItemGB
{
public:
	unsigned char m_bfmeHeadGB[0x24];
	void *m_bfmePtrGB;
	unsigned char m_bfmeTailGB[0x30];
};

class BfmeListGB
{
public:
	void *bfmeAtGB(int i);

	unsigned char m_bfmeGapGB[0x18];
	BfmeItemGB *m_bfmeBeginGB;
	BfmeItemGB *m_bfmeEndGB;
};

void *BfmeListGB::bfmeAtGB(int i)
{
	if (i < 0 || (unsigned int)i >= (unsigned int)(m_bfmeEndGB - m_bfmeBeginGB))
		return 0;

	return (*(BfmeItemGB *volatile *)&m_bfmeBeginGB)[i].m_bfmePtrGB;
}
