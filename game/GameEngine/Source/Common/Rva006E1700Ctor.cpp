// cl: /O2 /Ob0

class Rva006E1700Base
{
public:
	Rva006E1700Base();
	virtual void handle();

private:
	char m_pad[0x08];
};

class Rva006E1700 : public Rva006E1700Base
{
	int m_0C;
	int m_10;
	int m_14;

public:
	Rva006E1700();
};

Rva006E1700::Rva006E1700()
{
	m_0C = 0;
	m_10 = 0;
	m_14 = 0xFF;
}
