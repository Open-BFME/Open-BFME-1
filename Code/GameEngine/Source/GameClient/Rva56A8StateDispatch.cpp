// cl: /DNDEBUG /MD /EHsc

class BfmeH1065
{
};

int bfmeAptLevel00465CE0(BfmeH1065 *window);

class WindowManager
{
public:
	void unidentified_00015235(int movie, const char *function, int argumentCount,
		const void *p1, const void *p2, const void *p3, const void *p4, const void *p5);
};

extern WindowManager *g_theWindowManager;

class BfmeGlobal_012f19e8
{
public:
	void bfmeCall_000290d2();
};

class Rva56A8StateOwner
{
public:
	void dispatchState(int state);

private:
	char m_pad0[0x258];
	int m_state;
	char m_pad25c[0x20];
	int m_auxiliaryState;
};

void Rva56A8StateOwner::dispatchState(int state)
{
	switch (state)
	{
	case 3:
	{
		int currentState = m_state;
		if (currentState == 8)
		{
			g_theWindowManager->unidentified_00015235(
				bfmeAptLevel00465CE0((BfmeH1065 *)this),
				reinterpret_cast<const char *>(0x0110a4e8), 1,
				reinterpret_cast<const char *>(0x0110a4f8), 0, 0, 0, 0);
			m_state = 9;
			if (*reinterpret_cast<volatile int *>(0x012f4b44) != 0)
				reinterpret_cast<BfmeGlobal_012f19e8 **>(0x012f19e8)[0]->bfmeCall_000290d2();
		}
		else if (currentState == 0x12)
			m_state = 1;
		break;
	}

	case 1:
		if (m_state == 7)
			m_state = 6;
		break;
	}
}
