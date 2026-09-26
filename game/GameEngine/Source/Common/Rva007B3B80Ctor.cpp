// cl: /O2 /Ob0

class Rva007B12F0Base
{
public:
	Rva007B12F0Base();
	virtual void handle();

private:
	char m_pad[0x54];
};

class Rva007B3B80 : public Rva007B12F0Base
{
	int m_58;
	int m_5C;

public:
	Rva007B3B80();
};

Rva007B3B80::Rva007B3B80()
{
	m_58 = 0;
	m_5C = 0;
}
