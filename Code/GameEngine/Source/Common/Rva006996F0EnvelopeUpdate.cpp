// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Piecewise envelope update; clamp +0x9c; stdcall 6x2 refresh.

void __stdcall refreshPair(int a, int b);

class Rva006996F0Owner
{
public:
	void update(float dt);

	char m_pad0[0x9c];
	float m_f9c;  // +0x9c
	char m_pad1[0xac - 0xa0];
	float m_fac;  // +0xac
	float m_fb0;  // +0xb0
	float m_fb4;  // +0xb4
	float m_fb8;  // +0xb8
	float m_fbc;  // +0xbc
	float m_fc0;  // +0xc0
	unsigned char m_c4; // +0xc4
};

void Rva006996F0Owner::update(float dt)
{
	if (!m_c4)
		return;

	float t = dt * 0.001f + m_fc0;
	m_fc0 = t;

	if (t <= m_fb4)
	{
		m_f9c = m_fac + (t / m_fb4) * (m_fb0 - m_fac);
	}
	else
	{
		float t2 = t - m_fb4;
		if (t2 <= m_fb8)
		{
			m_f9c = m_fb0;
		}
		else
		{
			float t3 = t2 - m_fb8;
			if (t3 <= m_fbc)
			{
				m_f9c = m_fb0 + (t3 / m_fbc) * (m_fac - m_fb0);
			}
			else
			{
				m_c4 = 0;
				m_f9c = m_fac;
			}
		}
	}

	float v = m_f9c;
	if (v < 0.0f)
		v = 0.0f;
	else if (v > 1.0f)
		v = 1.0f;
	m_f9c = v;

	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 2; ++j)
			refreshPair(i, j);
	}
}
