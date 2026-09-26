// cl: /O2 /Ob0

class Rva007B12F0Base
{
public:
	Rva007B12F0Base();
	virtual void handle();

private:
	char m_pad[0x54];
};

class Rva007B12F0 : public Rva007B12F0Base
{
	int m_58;
	int m_5C;
	float m_60;
	char m_64;

public:
	Rva007B12F0();
};

Rva007B12F0::Rva007B12F0()
{
	m_58 = 0;
	m_5C = 0;
	m_64 = 0;
	m_60 = 20.0f;
}
