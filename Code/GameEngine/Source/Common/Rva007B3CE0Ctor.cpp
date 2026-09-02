// cl: /O2 /Ob0

class BfmeThingSE
{
public:
	void bfmeStartSE();

private:
	char m_pad[0x58];
};

class Rva007B12F0Base : public BfmeThingSE
{
public:
	void initialize();
};

class Rva007B3CE0 : public Rva007B12F0Base
{
	int m_58;
	int m_5C;
	float m_60;
	char m_64;

public:
	void initialize();
};

void Rva007B3CE0::initialize()
{
	Rva007B12F0Base::initialize();
	m_58 = 0;
	m_5C = 0;
	m_60 = 20.0f;
	m_64 = 0;
	bfmeStartSE();
}
