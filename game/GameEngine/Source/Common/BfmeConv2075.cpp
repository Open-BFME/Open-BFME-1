// Retail VAs 0x010C7450 and 0x010C7E28, emitted by
// GiantBirdAIUpdateDestructorThunk.cpp.
extern "C" void *__identifier("??_7GiantBirdNestedBase@@6B@")[];
extern "C" void *__identifier("??_7GiantBirdNested@@6B@")[];

// ILT 0x0002A1B2 routes to ParabolicEase::setEaseTimes at RVA 0x00094970.
class ParabolicEase
{
public:
	void setEaseTimes(float easeInTime, float easeOutTime, float duration);

	unsigned char m_bfmeGapIC[8];
};

class BfmeBaseIC
{
public:
	BfmeBaseIC()
	{
		m_bfmeVftIC = __identifier("??_7GiantBirdNestedBase@@6B@");
		m_bfmeSubIC.setEaseTimes(0.0f, 0.0f, 1.0f);
		m_bfme04IC = 0;
		m_bfme08IC = 0;
		m_bfme18IC = 0;
		m_bfme1cIC = 0;
		m_bfme20IC = 0;
		m_bfme28IC = 0;
	}

	void *m_bfmeVftIC;
	volatile int m_bfme04IC;
	volatile int m_bfme08IC;
	int m_bfme0cIC;
	ParabolicEase m_bfmeSubIC;
	volatile int m_bfme18IC;
	volatile int m_bfme1cIC;
	volatile int m_bfme20IC;
	char m_bfme24IC;
	unsigned char m_bfmePad0IC[3];
	volatile int m_bfme28IC;
};

class BfmeThingIC : public BfmeBaseIC
{
public:
	BfmeThingIC();

	int m_bfme2cIC;
	int m_bfme30IC;
	int m_bfme34IC;
	int m_bfme38IC;
	int m_bfme3cIC;
	int m_bfme40IC;
	char m_bfme44IC;
	char m_bfme45IC;
	char m_bfme46IC;
	unsigned char m_bfmePad1IC[1];
	int m_bfme48IC;
	int m_bfme4cIC;
	int m_bfme50IC;
	int m_bfme54IC;
	int m_bfme58IC;
	int m_bfme5cIC;
};

BfmeThingIC::BfmeThingIC()
{
	*(void *volatile *)&m_bfmeVftIC = __identifier("??_7GiantBirdNested@@6B@");
	*(volatile int *)&m_bfme2cIC = 0;
	m_bfme30IC = 0;
	m_bfme34IC = 0;
	m_bfme38IC = 0;
	m_bfme3cIC = 0;
	m_bfme40IC = 0;
	m_bfme48IC = 0;
	m_bfme4cIC = 0;
	m_bfme50IC = 0;
	m_bfme24IC = 0;
	m_bfme44IC = 0;
	m_bfme45IC = 0;
	m_bfme46IC = 0;
	m_bfme54IC = 0;
	m_bfme58IC = 0;
	m_bfme5cIC = 0;
}
