// cl: /O2 /Ob0

class GameWindow
{
public:
	void *winGetUserData(void);
	void winSetUserData(void *data);
	void winSetStatus(unsigned int status);
};

struct _PushButtonData
{
};

extern _PushButtonData *getNewPushButtonData(void);

struct Rva004BCB20Data
{
	char m_prefix[0x24];
	int m_value;
};

void Rva004BCB20(GameWindow *window, int value)
{
	if (window != 0)
	{
		Rva004BCB20Data *data =
			(Rva004BCB20Data *)window->winGetUserData();
		if (data == 0)
		{
			data = (Rva004BCB20Data *)getNewPushButtonData();
			window->winSetUserData(data);
		}
		data->m_value = value;
		window->winSetStatus(0x02000000);
	}
}
