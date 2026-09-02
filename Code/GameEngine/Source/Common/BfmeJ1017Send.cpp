// cl: /O2 /DNDEBUG /MD

extern unsigned char g_bfmeJ1017Flag;

class BfmeJ1017
{
public:
	void bfmeInsert(unsigned int packed);
	void bfmeSendX1017(int a, int b);
	void bfmeSendY1017(int a, int b, int c);
};

void BfmeJ1017::bfmeSendX1017(int a, int b)
{
	if (g_bfmeJ1017Flag)
		bfmeInsert(((a << 15) | (b & 0x7FFF)) << 2);
}

void BfmeJ1017::bfmeSendY1017(int a, int b, int c)
{
	bfmeInsert(((((a << 7) | (b & 0x7F)) << 8) | (c & 0xFF)) << 2 | 1);
}
