// cl: /O2 /Ob0

class GameWindow
{
public:
	void *winGetUserData(void);
};

struct Rva004B5B30GlobalData
{
	char m_prefix[0x30];
	int m_scale;
};

extern Rva004B5B30GlobalData *TheGlobalData;

struct Rva004B5B30UserData
{
	int m_value;
};

class Rva004B5B30
{
	GameWindow *m_window;

public:
	void set(int value);
};

void Rva004B5B30::set(int value)
{
	if (m_window != 0)
	{
		Rva004B5B30UserData *data =
			(Rva004B5B30UserData *)m_window->winGetUserData();
		data->m_value = (TheGlobalData->m_scale * value) / 768;
	}
}
