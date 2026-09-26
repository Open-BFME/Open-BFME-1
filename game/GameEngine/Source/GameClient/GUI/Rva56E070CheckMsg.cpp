// cl: /DNDEBUG /MD /EHsc

class BfmeThingME
{
public:
	void bfmeGoME(int value);
	int bfmeTestME();
	void apply();
};

class BfmeMsgHandler
{
public:
	int defaultHandler(int msg, void *control, void *data);
};

class GameWindow;
void GadgetListBoxSetSelected(GameWindow *listbox, int selectIndex);

class Rva0056C1C0Owner
{
public:
	void submitUnicode();
};

class Rva56E070StateOwner : public BfmeThingME
{
public:
	char m_pad0[0x258];
	int m_state;
	int m_direction;
	char m_pad260[4];
	void *m_arg264;
	void *m_arg268;
	void *m_context26c;
	int m_mode270;
	int m_value274;
	bool m_flag278;
	char m_pad279[3];
	int m_auxiliaryState;

	void beginState(int unused);
	int checkMsg(int msg, void *control, void *data);
};

int Rva56E070StateOwner::checkMsg(int msg, void *control, void *data)
{
	if (m_state >= 14 && m_state <= 18)
		return ((BfmeMsgHandler *)this)->defaultHandler(msg, control, data);

	switch (msg)
	{
	case 0x4014:
		if ((int)data >= 0)
		{
			if (control == m_arg264)
				GadgetListBoxSetSelected((GameWindow *)m_arg268, -1);
			else if (control == m_arg268)
				GadgetListBoxSetSelected((GameWindow *)m_arg264, -1);
		}
		apply();
		if (m_mode270 != 2)
			((Rva0056C1C0Owner *)this)->submitUnicode();
		goto success;
	case 0x4015:
		if (control == m_arg264 || control == m_arg268)
		{
			if (bfmeTestME())
			{
				if (m_mode270 == 3)
					bfmeGoME(0);
				else if (m_mode270 == 2)
					beginState(0);
			}
		}
		goto success;
	case 0x4030:
		if (control == m_context26c && data == 0 && m_mode270 == 3)
			bfmeGoME(0);
		goto success;
	default:
		return ((BfmeMsgHandler *)this)->defaultHandler(msg, control, data);
	}

success:
	return 1;
}
