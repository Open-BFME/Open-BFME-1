// Open-BFME5 conversions.

class BfmeItemVOF
{
public:
	int bfmeItemSizeVOF();
	char m_bfmePad00[0x24];
};

class BfmeThingVOF
{
public:
	int bfmeSizeVOF();
	char m_bfmePad00[0x44];
	int m_bfme44;
	char m_bfmePad48[4];
	BfmeItemVOF *m_bfme4c;
};

int BfmeThingVOF::bfmeSizeVOF()
{
	int n = m_bfme44;
	int i = 0;
	int total = 0x50;

	if (n > 0)
	{
		int off = 0;

		do
		{
			total += ((BfmeItemVOF *)((char *)m_bfme4c + off))->bfmeItemSizeVOF();
			++i;
			off += 0x24;
		} while (i < m_bfme44);
	}
	return total;
}
