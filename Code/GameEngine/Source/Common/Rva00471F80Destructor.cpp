// cl: /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString();

private:
	char *m_data;
};

class Rva00471F80Owned
{
public:
	virtual ~Rva00471F80Owned();
};

class Rva00471F80Base
{
public:
	virtual ~Rva00471F80Base() {}
};

class Rva00471F80 : public Rva00471F80Base
{
public:
	virtual ~Rva00471F80();

private:
	char m_pad[0x18];
	Rva00471F80Owned *m_owned;
	int m_unused;
	AsciiString m_name;
};

// ??1Rva00471F80@@UAE@XZ
Rva00471F80::~Rva00471F80()
{
	delete m_owned;
	m_owned = 0;
}
