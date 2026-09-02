// cl: /DNDEBUG /MD /EHsc

void __cdecl operator delete(void *);

class StringClass
{
public:
	~StringClass();
	char *m_buffer;
};

class Rva009EB810TailBase
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual ~Rva009EB810TailBase();

private:
	char m_pad[0x10];
};

class Gen0097D800
{
public:
	~Gen0097D800();
};

class Gen_dtor_00970920 : public Rva009EB810TailBase
{
public:
	virtual ~Gen_dtor_00970920();

private:
	Gen0097D800 *m_ptr;
	StringClass m_name;
};

Gen_dtor_00970920::~Gen_dtor_00970920()
{
	delete m_ptr;
}
