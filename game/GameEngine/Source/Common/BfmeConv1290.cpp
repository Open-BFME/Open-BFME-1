// Open-BFME5 conversions.

extern unsigned char g_006fc8d0;

void bfmeEndSGA(void);

class BfmeThingSGA
{
public:
	void bfmeGoSGA();
	void bfmeOneSGA();
	void bfmeTwoSGA();
};

void BfmeThingSGA::bfmeGoSGA()
{
	char saved = g_006fc8d0;
	g_006fc8d0 = 0;
	bfmeOneSGA();
	bfmeTwoSGA();
	bfmeEndSGA();
	g_006fc8d0 = (unsigned char)saved;
}
