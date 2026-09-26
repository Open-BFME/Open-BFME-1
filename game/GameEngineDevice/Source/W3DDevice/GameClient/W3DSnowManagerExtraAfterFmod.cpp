// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME5 conversion.
// Retail 0x00725620, 189 bytes.

class BfmeOverridable
{
public:
	const BfmeOverridable *getFinalOverride() const;

	void *m_vtable;
	const BfmeOverridable *m_nextOverride;
};

class BFMEWeatherOverride : public BfmeOverridable
{
public:
	unsigned char m_unmodelled_08[0x58 - 8];
	char m_flag58;
	unsigned char m_unmodelled_59[3];
	int m_5c;
};

class BFMEFrameState
{
public:
	unsigned char m_unmodelled_00[0x0c];
	int m_frame;
};

extern BFMEWeatherOverride *g_bfmeGlo012F15F8;
extern BFMEFrameState *g_bfmeGlo012F0FE0;
extern "C" float g_bfmeDefaultBU;

class W3DSnowManager
{
public:
	void extraAfterFmod(void);
	void copyFromOverride(void);
	void sibling(void);

private:
	unsigned char m_unmodelled_00[0x4c];
	int m_4c;
	unsigned char m_unmodelled_50[0x54 - 0x50];
	float m_54;
	unsigned char m_unmodelled_58[0x94 - 0x58];
	int m_94;
	int m_98;
};

static const BFMEWeatherOverride *walkSnowOverride(const BFMEWeatherOverride *d)
{
	if (d && d->m_nextOverride)
		return (const BFMEWeatherOverride *)d->m_nextOverride->getFinalOverride();
	return d;
}

void W3DSnowManager::extraAfterFmod(void)
{
	const BFMEWeatherOverride *ov = walkSnowOverride(g_bfmeGlo012F15F8);
	if (ov->m_flag58 == 0)
		return;

	if (m_98 != 0)
	{
		int state = m_98;
		int frame;
		int state94 = 2;
		if (state == 1 || state == 3)
			--m_4c;
		sibling();
		if (m_94 == state94)
		{
			frame = g_bfmeGlo012F0FE0->m_frame;
			if (frame != state94)
			{
				m_98 = 3;
				ov = walkSnowOverride(g_bfmeGlo012F15F8);
				m_4c = (int)((g_bfmeDefaultBU - m_54) * ov->m_5c);
				m_94 = frame;
			}
		}
	}
	else
	{
		int frame = g_bfmeGlo012F0FE0->m_frame;
		if (frame == 2 && m_94 != 2)
		{
			m_94 = frame;
			copyFromOverride();
		}
	}
}
