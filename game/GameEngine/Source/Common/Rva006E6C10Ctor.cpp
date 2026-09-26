// cl: /O2 /Ob0

class Rva006E6C10Base
{
public:
	Rva006E6C10Base();
	virtual void handle();

private:
	char m_pad[0x1C];
};

class Rva006E6C10 : public Rva006E6C10Base
{
	int m_20;
	int m_24;
	int m_28;
	int m_2C;

public:
	Rva006E6C10();
};

Rva006E6C10::Rva006E6C10()
{
	m_20 = 0;
	m_2C = 0;
	m_24 = 9;
	m_28 = 13;
}
