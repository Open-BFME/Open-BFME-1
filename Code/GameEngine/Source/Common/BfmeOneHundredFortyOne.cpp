// Copying one record over another, field by field so the unused space between
// them is left alone. Asked to write nowhere, it does nothing at all.

struct BfmeRecordXL
{
	int m_bfmeFirst;			// 0x00
	int m_bfmeSecond;			// 0x04
	int m_bfmeThird;			// 0x08
	int m_bfmeFourth;			// 0x0c
	unsigned char m_bfmeFlag;		// 0x10
	int m_bfmeFifth;			// 0x14
	int m_bfmeSixth;			// 0x18
};

void bfmeCopyRecordXL(BfmeRecordXL *dest, const BfmeRecordXL *src)
{
	if (dest != 0)
	{
		dest->m_bfmeFirst = src->m_bfmeFirst;
		dest->m_bfmeSecond = src->m_bfmeSecond;
		dest->m_bfmeThird = src->m_bfmeThird;
		dest->m_bfmeFourth = src->m_bfmeFourth;
		dest->m_bfmeFlag = src->m_bfmeFlag;
		dest->m_bfmeFifth = src->m_bfmeFifth;
		dest->m_bfmeSixth = src->m_bfmeSixth;
	}
}
