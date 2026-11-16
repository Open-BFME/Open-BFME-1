class GlobalWeatherSystem { public: void setWeather(int which); };

class BfmeModeGF
{
public:
	// Field-access view only; the call below uses its existing native owner.

	unsigned char m_bfmeHeadGF[0xc];
	int m_bfmeKindGF;
};

// Retail 0x012F0FE0: use the existing data owner; retain the local pointee view.
extern struct RetailGlobalWeatherSystem *TheGlobalWeatherSystem;

class BfmeTimerGF
{
public:
	void bfmeTickGF(void);

	unsigned char m_bfmeHeadGF[0xc];
	int m_bfmeOtherGF;
	int m_bfmeStateGF;
	int m_bfmeCountGF;
};

void BfmeTimerGF::bfmeTickGF(void)
{
	if (m_bfmeStateGF != 1)
		return;

	int remaining = --m_bfmeCountGF;

	if (remaining > 0)
		return;

	m_bfmeCountGF = 0;
	m_bfmeStateGF = 0;

	if (reinterpret_cast<BfmeModeGF *>(TheGlobalWeatherSystem)->m_bfmeKindGF == 4)
		reinterpret_cast<GlobalWeatherSystem *>(TheGlobalWeatherSystem)->setWeather(0);

	m_bfmeOtherGF = 0;
}
