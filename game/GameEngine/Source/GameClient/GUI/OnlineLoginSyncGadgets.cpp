// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

extern "C" void __cdecl __identifier("?applyLoginGadgets0054FB10@BfmeAptScreenOnlineLogin@@QAE_NXZ")();
class BfmeAptScreenOnlineLogin
{
public:
	void _bfme_syncLoginGadgets();
	void _bfme_refreshLoginState();
	void _bfme_applyLoginGadgets() {
	 // retail body is ledgered as ?applyLoginGadgets0054FB10@BfmeAptScreenOnlineLogin@@QAE_NXZ; call it by that defined name
	 union { void (__cdecl *symbol)(); void (BfmeAptScreenOnlineLogin::*member)(); } c;
	 c.symbol = &__identifier("?applyLoginGadgets0054FB10@BfmeAptScreenOnlineLogin@@QAE_NXZ");
	 (this->*c.member)();
	}
	bool _bfme_loginGadgetsState();

private:
	unsigned char m_unmodelled[ 0x95 ];
	bool m_needsRefresh;
	unsigned char m_pad[ 0xA1 - 0x96 ];
	bool m_gadgetState;
};

void BfmeAptScreenOnlineLogin::_bfme_syncLoginGadgets()
{
	if( m_needsRefresh )
	{
		_bfme_refreshLoginState();
		_bfme_applyLoginGadgets();
	}
	bool state = _bfme_loginGadgetsState();
	if( m_gadgetState != state )
	{
		_bfme_applyLoginGadgets();
		state = _bfme_loginGadgetsState();
		m_gadgetState = state;
	}
}
