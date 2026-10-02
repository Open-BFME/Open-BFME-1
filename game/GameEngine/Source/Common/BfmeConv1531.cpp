// Open-BFME5 conversions.

struct NodeCompressedMotionStruct
{
public:
	int Get_Channel_Memory_Usage();
	char m_bfmePad00[0x1c];
};

class BfmeThingVOG
{
public:
	int bfmeSizeVOG();
	char m_bfmePad00[0x44];
	int m_bfme44;
	char m_bfmePad48[8];
	NodeCompressedMotionStruct *m_bfme50;
};

int BfmeThingVOG::bfmeSizeVOG()
{
	int n = m_bfme44;
	int i = 0;
	int total = 0x54;

	if (n > 0)
	{
		int off = 0;

		do
		{
			total += ((NodeCompressedMotionStruct *)((char *)m_bfme50 + off))->Get_Channel_Memory_Usage();
			++i;
			off += 0x1c;
		} while (i < m_bfme44);
	}
	return total;
}
