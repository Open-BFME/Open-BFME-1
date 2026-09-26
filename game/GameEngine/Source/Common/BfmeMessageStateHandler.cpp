// cl: /DNDEBUG /MD /EHsc

class BfmeMessageStateHandler
{
public:
	int processMessage(int type, unsigned char code, unsigned char flags);
	void handleStateTwo(int value);
	void handleDefaultState(int value);
	void handleActiveState(int value);

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
					handleActiveState(0);
				else
					handleDefaultState(0);
			}
			return 1;

		case 28:
			if ((flags & 2) != 0 && m_state == 2)
				handleStateTwo(0);
			return 1;
	}
	return 0;
}
