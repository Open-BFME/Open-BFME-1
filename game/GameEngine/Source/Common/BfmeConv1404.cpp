// Open-BFME5 conversions.

struct BfmeHdrVKK
{
	unsigned short m_bfme00;
	unsigned short m_bfme02;
	unsigned short m_bfme04;
	unsigned short m_bfme06;
};

class BfmeStrVKK
{
public:
	void bfmeTruncVKK(unsigned n);
	BfmeStrVKK *bfmeReverseVKK();
	BfmeHdrVKK *m_bfme00;
};

// The reserve call retail makes here is EAStringC::ChangeBuffer at 0x0089E570
// (matched in EAStringCMid.cpp); only the this-pointer matters to this TU.
class EAStringC
{
	enum CBPushZero
	{
		CB_NO_PUSH_ZERO,
		CB_PUSH_ZERO
	};

	void ChangeBuffer(unsigned int reserve, unsigned int offset,
		unsigned int copy, CBPushZero pushZero, unsigned int internalSize);

	friend class BfmeStrVKK;
};

void BfmeStrVKK::bfmeTruncVKK(unsigned n)
{
	unsigned len = m_bfme00->m_bfme02;
	if (len > n)
		len = n;
	reinterpret_cast<EAStringC *>(this)->ChangeBuffer(n, 0, len,
		EAStringC::CB_PUSH_ZERO, len);
}

BfmeStrVKK *BfmeStrVKK::bfmeReverseVKK()
{
	unsigned len = m_bfme00->m_bfme02;
	reinterpret_cast<EAStringC *>(this)->ChangeBuffer(len, 0, len,
		EAStringC::CB_PUSH_ZERO, len);
	unsigned n = m_bfme00->m_bfme02;
	if (n > 1)
	{
		char *a = (char *)m_bfme00 + 8;
		char *b = a + n - 1;
		if (a < b)
		{
			do
			{
				char x = *b;
				char y = *a;
				*a = x;
				++a;
				*b = y;
				--b;
			} while (a < b);
		}
		m_bfme00->m_bfme06 = 0;
	}
	return this;
}
