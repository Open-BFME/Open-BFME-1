// cl: /O2 /Ob0

class Rva00412140
{
	void *m_00;
	int m_attackRateX;
	int m_attackRateY;
	int m_attackRateZ;
	int m_decayRateX;
	int m_decayRateY;
	int m_decayRateZ;
	int m_peakColorX;
	int m_peakColorY;
	int m_peakColorZ;
	int m_currentColorX;
	int m_currentColorY;
	int m_currentColorZ;
	int m_sustainCounter;
	char m_envState;
	char m_affect;
	int m_3C;
	int m_40;
	int m_44;
	int m_48;
	int m_4C;

public:
	Rva00412140();
};

// TintEnvelope's one vtable. __identifier lets this TU name the mangled
// vftable data symbol directly, so no linker alias pragma is needed
// (same pattern as AIAttackMeleeEngageStateCtor.cpp).
extern "C" void *__identifier("??_7TintEnvelope@@6B@")[];

Rva00412140::Rva00412140()
{
	m_00 = __identifier("??_7TintEnvelope@@6B@");
	m_attackRateX = 0;
	m_attackRateY = 0;
	m_attackRateZ = 0;
	m_decayRateX = 0;
	m_decayRateY = 0;
	m_decayRateZ = 0;
	m_peakColorX = 0;
	m_peakColorY = 0;
	m_peakColorZ = 0;
	m_currentColorX = 0;
	m_currentColorY = 0;
	m_currentColorZ = 0;
	m_44 = 0;
	m_48 = 0;
	m_4C = 0;
	m_envState = 0;
	m_sustainCounter = 0;
	m_affect = 0;
	m_3C = 0;
	m_40 = 0;
}
