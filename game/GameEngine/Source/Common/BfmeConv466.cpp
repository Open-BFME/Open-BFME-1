struct BfmeThingBHG
{
	unsigned char m_bfmeHead[0x259];
	bool m_bfmeFlag;
};

class BfmeAptScreenMainMenu;
extern BfmeAptScreenMainMenu *g_rva012F49B4MainMenu;

// ILT 0x00006D52 jumps to 0x0062F760, the matched CancelPatchCheckCallback
// (CancelPatchCheckCallback_BFME.cpp).
void CancelPatchCheckCallback();

void bfmeGoBHG()
{
	if (reinterpret_cast<BfmeThingBHG * &>(g_rva012F49B4MainMenu) != 0)
		reinterpret_cast<BfmeThingBHG * &>(g_rva012F49B4MainMenu)->m_bfmeFlag = false;
	CancelPatchCheckCallback();
}
