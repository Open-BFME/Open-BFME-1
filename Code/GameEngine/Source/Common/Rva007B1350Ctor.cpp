// cl: /O2 /Ob0

class Rva007B12F0Base
{
public:
	void initialize();
	virtual void handle();

private:
	char m_pad[0x54];
};

class Rva007B1350
{
	Rva007B12F0Base m_base;
	volatile int m_58;
	volatile int m_5C;
	volatile float m_60;
	volatile char m_64;

public:
	void initialize();
};

void Rva007B1350::initialize()
{
	m_base.initialize();
	m_58 = 0;
	m_5C = 0;
	m_60 = 20.0f;
	m_64 = 0;
}
