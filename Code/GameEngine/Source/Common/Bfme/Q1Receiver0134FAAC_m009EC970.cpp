// cl: /DNDEBUG /MD /EHsc
// Open-BFME: Q1Receiver0134FAAC::m009EC970, retail 0x009EC970, 45 bytes.
//
// A three-way switch that sets one of three adjacent flags at this+0x1EC,
// +0x1ED and +0x1EE. MSVC walks the cases with a subtract and two decrements
// rather than a table, and every arm returns on the spot.

typedef int Int;
typedef bool Bool;

extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned long);

extern volatile Bool g_q1Flag0134FAA8;

class Q1Receiver0134FAAC
{
public:
	void m009EC970(Int which);
	void m009EC9A0(Int which);
	void m009ECA30(Int value);

private:
	unsigned char m_unmodelled_000[0x24];
	Int m_value;
	unsigned char m_unmodelled_028[0x1C4];
	Bool m_flag0;						// this+0x1EC
	Bool m_flag1;						// this+0x1ED
	Bool m_flag2;						// this+0x1EE
};

void Q1Receiver0134FAAC::m009EC970(Int which)
{
	switch (which)
	{
		case 0:
			m_flag0 = true;
			break;
		case 1:
			m_flag1 = true;
			break;
		case 2:
			m_flag2 = true;
			break;
	}
}

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

void Q1Receiver0134FAAC::m009ECA30(Int value)
{
	m_value = value;
	if (value < 1)
		m_value = 1;
}
