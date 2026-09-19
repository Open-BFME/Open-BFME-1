// cl: /DNDEBUG /MD /EHsc

class AptPlayerStatus
{
public:
	virtual ~AptPlayerStatus();
	virtual int input(unsigned int message, unsigned int key, unsigned int state);
	void ReturnToGame(const char *argument);
};

__declspec(noinline) AptPlayerStatus::~AptPlayerStatus() {}

void Force_AptPlayerStatus_Deleting_Destructor(AptPlayerStatus *status)
{
	delete status;
}

enum
{
	GWM_CHAR = 0x15,
	KEY_ESC = 1,
	KEY_TAB = 15,
	KEY_ENTER = 28,
	KEY_STATE_UP = 1
};

// The primary vtable slot immediately after the deleting destructor is the
// input slot on the other identified APT screens. The labels preserve the
// shared ignored block that both the message and key tests branch to.
// ?input@AptPlayerStatus@@UAEHIII@Z
int AptPlayerStatus::input(unsigned int message, unsigned int key, unsigned int state)
{
	if (message != GWM_CHAR)
		goto ignored;

	switch ((unsigned char)key)
	{
	case KEY_ESC:
	case KEY_TAB:
	case KEY_ENTER:
		goto accepted;
	default:
		goto ignored;
	}

ignored:
	return 0;

accepted:
	if (state & KEY_STATE_UP)
		ReturnToGame(0);
	return 1;
}
