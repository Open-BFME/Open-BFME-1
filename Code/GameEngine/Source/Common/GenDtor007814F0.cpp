// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: 21-string derived destructor at retail 0x0077F920.

class AsciiString
{
public:
	~AsciiString();

private:
	int m_data;
};

class BfmeDtorBaseI
{
public:
	virtual ~BfmeDtorBaseI();

private:
	char m_bfmePad[0x158];
};

class Gen_dtor_007814f0 : public BfmeDtorBaseI
{
public:
	virtual ~Gen_dtor_007814f0();

private:
	AsciiString m_string00;
	AsciiString m_string01;
	AsciiString m_string02;
	AsciiString m_string03;
	AsciiString m_string04;
	AsciiString m_string05;
	AsciiString m_string06;
	AsciiString m_string07;
	AsciiString m_string08;
	AsciiString m_string09;
	AsciiString m_string10;
	AsciiString m_string11;
	AsciiString m_string12;
	AsciiString m_string13;
	AsciiString m_string14;
	AsciiString m_string15;
	AsciiString m_string16;
	AsciiString m_string17;
	AsciiString m_string18;
	AsciiString m_string19;
	AsciiString m_string20;
};

// ??1Gen_dtor_007814f0@@UAE@XZ
Gen_dtor_007814f0::~Gen_dtor_007814f0()
{
}
