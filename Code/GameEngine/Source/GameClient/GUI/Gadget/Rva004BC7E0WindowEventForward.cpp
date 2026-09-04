// cl: /O2 /Ob0
// Retail 0x004BC7E0 is the explicit-this event body used by the forwarder at
// 0x00793E20.  The event values and the two display-string constants are the
// only identity recovered for this address; the forwarded call remains the
// existing incremental-link thunk.

class GameWindow
{
public:
	unsigned int winGetStatus(void);
	void *winGetUserData(void);
};

struct Rva004BC7E0NestedData
{
	char m_prefix[0x18];
	int m_value;
};

struct Rva004BC7E0UserData
{
	char m_prefix[0x14];
	Rva004BC7E0NestedData *m_nested;
};

void j_00002e0f(void);
void j_00011f54(void);
typedef void (__cdecl *Rva004BC7E0StringCall)(void *stringData);
typedef void (__cdecl *Rva004BC7E0ForwardCall)(void *self, void *event,
	void *arg2, void *arg3);

void gen004BC7E0(void *self, void *event, void *arg2, void *arg3)
{
	GameWindow *window = (GameWindow *)self;
	int eventCode = (int)event;
	if (window != 0)
	{
		switch (eventCode)
		{
		case 13:
			{
				if ((window->winGetStatus() & 8) != 0)
					((Rva004BC7E0StringCall)j_00002e0f)((void *)0x010FD8D4);
				else
				{
					Rva004BC7E0UserData *data =
						(Rva004BC7E0UserData *)window->winGetUserData();
					if (data != 0 && data->m_nested != 0)
					{
						if ((data->m_nested->m_value & 0x80000000) == 0)
							((Rva004BC7E0StringCall)j_00002e0f)((void *)0x010FD8A4);
						else
							((Rva004BC7E0StringCall)j_00002e0f)((void *)0x010FD8D4);
					}
					else
						((Rva004BC7E0StringCall)j_00002e0f)((void *)0x010FD8A4);
				}
				break;
			}
		case 5:
			if ((window->winGetStatus() & 8) != 0)
				((Rva004BC7E0StringCall)j_00002e0f)((void *)0x010FD8D4);
			else
				((Rva004BC7E0StringCall)j_00002e0f)((void *)0x010FD8A4);
			break;
		}
	}

forward:
	((Rva004BC7E0ForwardCall)j_00011f54)(self, event, arg2, arg3);
}
