// cl: /O2
// DisconnectScreen vtable slot 5, retail 0x0050E800.

class DisconnectMenu
{
public:
	void _bfme_showPlayerControls(int slot, bool show);
};

class Rva0050E800DisconnectScreen
{
public:
	virtual int slot05();

private:
	char m_padding[0x25c];
	bool m_initialized;
	char m_paddingAfterInitialized;
	bool m_playerControls[8];
};

int Rva0050E800DisconnectScreen::slot05()
{
	if (m_initialized)
	{
		m_initialized = false;
		for (int slot = 0; slot < 8; ++slot)
		{
			((DisconnectMenu *)this)->_bfme_showPlayerControls(
				slot, m_playerControls[slot]);
		}
	}

	return 1;
}
