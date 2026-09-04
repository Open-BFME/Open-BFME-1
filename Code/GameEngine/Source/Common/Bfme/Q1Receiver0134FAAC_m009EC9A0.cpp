// cl: /DNDEBUG /MD /EHsc

typedef int Int;
typedef bool Bool;

extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned long);

extern volatile Bool g_q1Flag0134FAA8;

class Q1Receiver0134FAAC
{
public:
	void m009EC9A0(Int which);

private:
	unsigned char m_unmodelled_000[0x1EC];
	Bool m_flag0;
	Bool m_flag1;
	Bool m_flag2;
};

void Q1Receiver0134FAAC::m009EC9A0(Int which)
{
	switch (which)
	{
		case 0:
			g_q1Flag0134FAA8 = false;
			if (g_q1Flag0134FAA8)
			{
				m_flag0 = false;
				break;
			}
			m_flag0 = false;
		spin:
			Sleep(1);
			if (!g_q1Flag0134FAA8)
				goto spin;
			break;
		case 1:
			m_flag1 = false;
			break;
		case 2:
			m_flag2 = false;
			break;
	}
}
