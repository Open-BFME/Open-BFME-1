// cl: /DNDEBUG /DWIN32 /MD
// Open-BFME: the OnlineQuickMatch APT vtable update slot at 0x0055B9A0.

class BfmeAptScreenOnlineQuickMatch
{
public:
	void update();
	bool rva005588E0Ready();
	bool rva00558A30Ready();
	bool rva00559E60Ready();
	void _bfme_sendStartQuickMatchRequest();


private:
	unsigned char m_unmodelled_000[ 0x54 ];
	bool m_ready;
	bool m_startRequested;
};

void BfmeAptScreenOnlineQuickMatch::update()
{
	if ( !m_ready && rva005588E0Ready() && rva00558A30Ready()
		&& rva00559E60Ready() )
	{
		m_ready = true;
	}

	if ( m_startRequested )
	{
		_bfme_sendStartQuickMatchRequest();
		m_startRequested = false;
	}
}
