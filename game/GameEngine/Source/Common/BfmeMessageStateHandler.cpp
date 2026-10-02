// cl: /DNDEBUG /MD /EHsc

// Retail ILTs 0x00021E4F, 0x000394F5 and 0x0003FFDA reach these
// matched Skirmish callbacks at 0x0057CE00, 0x005791C0 and 0x0057D600.
class BfmeAptScreenSkirmish
{
public:
	void _bfme_close(int argument);
	void _bfme_exit(void *argument);
	void personaAccept(int argument);
};

class BfmeMessageStateHandler
{
public:
	int processMessage(int type, unsigned char code, unsigned char flags);

private:
	unsigned char m_pad00[0x400];
	int m_state;
};

int BfmeMessageStateHandler::processMessage(
	int type, unsigned char code, unsigned char flags)
{
	if (type != 21)
		return 0;

	switch (code)
	{
		case 1:
			if ((flags & 1) != 0)
			{
				if (m_state == 2 || m_state == 3)
					reinterpret_cast<BfmeAptScreenSkirmish *>(this)->_bfme_close(0);
				else
					reinterpret_cast<BfmeAptScreenSkirmish *>(this)->_bfme_exit(0);
			}
			return 1;

		case 28:
			if ((flags & 2) != 0 && m_state == 2)
				reinterpret_cast<BfmeAptScreenSkirmish *>(this)->personaAccept(0);
			return 1;
	}
	return 0;
}
