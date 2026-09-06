// cl: /O2 /Ob0

extern void d_00904be0(void);
extern void W3DRadarResetLock(void);
extern void BFME_DX8_Thread_Assert(void);

typedef void *(__cdecl *Rva00904Be0)(int, int, int, int, int, int);

class Rva0090C2F0Inner
{
	void *m_vptr;
	char m_04;
	void *m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
	int m_30;
	int m_34;
	int m_38;
	int m_3C;
	int m_40;
	int m_44;

public:
	void go(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7);
};

void Rva0090C2F0Inner::go(int arg1, int arg2, int arg3, int arg4, int arg5, int arg6, int arg7)
{
	if (m_08 != 0)
		return;

	m_34 = arg4;
	m_3C = arg3;
	m_40 = arg5;
	m_44 = arg6;
	m_38 = arg7;

	int mode;
	switch (arg5) {
	case 0:
		mode = 0;
		break;
	case 1:
		mode = 1;
		break;
	case 2:
		mode = 2;
		break;
	default:
		mode = 0;
		break;
	}

	int flags;
	switch (arg6) {
	case 0:
		flags = 0;
		break;
	case 1:
		flags = 1;
		break;
	case 2:
		flags = 0x200;
		break;
	default:
		flags = 0;
		break;
	}

	W3DRadarResetLock();
	m_08 = ((Rva00904Be0)d_00904be0)(arg1, arg2, arg3, arg4, mode, flags);
	BFME_DX8_Thread_Assert();
	m_24 = arg1;
	m_2C = arg1;
	m_28 = arg2;
	m_30 = arg2;
}
