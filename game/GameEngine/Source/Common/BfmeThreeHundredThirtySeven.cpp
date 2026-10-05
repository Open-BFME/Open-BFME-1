extern "C" unsigned char bfmeVftSI[];

class Win32Mouse;
extern Win32Mouse *TheWin32Mouse;

class BfmeThingSI
{
public:
	void bfmeTailSI();
	void bfmeResetSI();
	void *m_bfmeVft;
};

void BfmeThingSI::bfmeResetSI()
{
	m_bfmeVft = bfmeVftSI;
	TheWin32Mouse = 0;
	bfmeTailSI();
}
