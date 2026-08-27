// One more: a four-byte reader that takes the bytes most significant first.

class BfmeCursorXF
{
public:
	const unsigned char *m_bfmeData;			// +0x00
	unsigned int m_bfmeValue;					// +0x04
	int m_bfmeBits;								// +0x08
	int m_bfmeCount;							// +0x0c
};

void bfmeReadWordXF(BfmeCursorXF *out, const unsigned char *data)
{
	out->m_bfmeData = data;

	unsigned int value = data[0];
	value = (value << 8) + data[1];
	value = (value << 8) + data[2];
	value = (value << 8) + data[3];
	out->m_bfmeValue = value;

	out->m_bfmeBits = 0x20;
	out->m_bfmeCount = 4;
}
