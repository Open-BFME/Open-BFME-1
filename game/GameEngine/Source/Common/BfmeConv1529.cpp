// Open-BFME5 conversions.

class BfmeThingVID
{
public:
	int bfmeSizeVID();
	char m_bfmePad00[0x24];
};

class BfmeThingVOF
{
public:
	int bfmeSizeVOF();
	char m_bfmePad00[0x44];
	int m_bfme44;
	char m_bfmePad48[4];
	BfmeThingVID *m_bfme4c;
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
			total += ((BfmeThingVID *)((char *)m_bfme4c + off))->bfmeSizeVID();
			++i;
			off += 0x24;
		} while (i < m_bfme44);
	}
	return total;
}
