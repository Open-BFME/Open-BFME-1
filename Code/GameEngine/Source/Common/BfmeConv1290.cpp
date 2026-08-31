// Open-BFME5 conversions.

extern char g_bfmeFlagSGA;

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
	char saved = g_bfmeFlagSGA;
	g_bfmeFlagSGA = 0;
	bfmeOneSGA();
	bfmeTwoSGA();
	bfmeEndSGA();
	g_bfmeFlagSGA = saved;
}
