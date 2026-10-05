struct BfmeThingBHG
{
	unsigned char m_bfmeHead[0x259];
	bool m_bfmeFlag;
};

class BfmeAptScreenMainMenu;
extern BfmeAptScreenMainMenu *g_rva012F49B4MainMenu;

void bfmeTailBHG();

void bfmeGoBHG()
{
	if (reinterpret_cast<BfmeThingBHG * &>(g_rva012F49B4MainMenu) != 0)
		reinterpret_cast<BfmeThingBHG * &>(g_rva012F49B4MainMenu)->m_bfmeFlag = false;
	bfmeTailBHG();
}
