// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Two BfmeAptScreenOnlineChat button handlers, retail 0x0052CD50 and
// 0x0052CD60, thirteen bytes each. The constructor at 0x00536DC0 registers
// them under the selector strings "AptOnline::OnlineChat::OnBttnIgnoreList"
// and "AptOnline::OnlineChat::OnBttnPlayerList". Each one writes the list
// mode that OnlineChatConstructor.cpp already calls m_zA4 and returns.
// Retail leaves int3 padding after each ret 4, which is where the extent
// comes from.

class BfmeAptScreenOnlineChat
{
public:
	void _bfme_onBttnIgnoreList( const char *name );
	void _bfme_onBttnPlayerList( const char *name );

private:
	unsigned char m_head[ 0xa4 ];
	int m_zA4;
};

void BfmeAptScreenOnlineChat::_bfme_onBttnIgnoreList( const char *name )
{
	(void)name;
	m_zA4 = 3;
}

void BfmeAptScreenOnlineChat::_bfme_onBttnPlayerList( const char *name )
{
	(void)name;
	m_zA4 = 1;
}
