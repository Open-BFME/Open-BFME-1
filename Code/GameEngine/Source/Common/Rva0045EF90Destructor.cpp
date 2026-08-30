// cl: /DNDEBUG /MD /EHsc

class AsciiString
{
public:
	~AsciiString();

private:
	unsigned m_value;
};

class Rva0045EF90Registry
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void remove(unsigned handle);
};

extern Rva0045EF90Registry *TheRva0045EF90Registry;

class Rva0045EF90Base
{
public:
	virtual ~Rva0045EF90Base() {}

private:
	unsigned m_value;
};

class Rva0045EF90Object : public Rva0045EF90Base
{
public:
	virtual ~Rva0045EF90Object();

private:
	AsciiString m_first;
	AsciiString m_second;
	unsigned m_handle;
	unsigned m_value14;
	unsigned m_value18;
	unsigned m_value1c;
	unsigned m_value20;
	unsigned char m_value24;
	unsigned char m_padding25[3];
	AsciiString m_last;
};

Rva0045EF90Object::~Rva0045EF90Object()
{
	if (TheRva0045EF90Registry != 0)
	{
		TheRva0045EF90Registry->remove(m_handle);
	}
	m_handle = 0;
}
