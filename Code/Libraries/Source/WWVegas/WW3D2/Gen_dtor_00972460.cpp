// cl: /DNDEBUG /MD /EHsc

void __cdecl operator delete(void *);

class StringClass
{
	void Free_String();
	friend class Gen_dtor_00972460;
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

class Gen_dtor_00972460 : public Rva009EB810TailBase
{
public:
	virtual ~Gen_dtor_00972460();

private:
	void *m_ptr;
	StringClass m_name;
};

Gen_dtor_00972460::~Gen_dtor_00972460()
{
	operator delete(m_ptr);
	m_name.Free_String();
}
