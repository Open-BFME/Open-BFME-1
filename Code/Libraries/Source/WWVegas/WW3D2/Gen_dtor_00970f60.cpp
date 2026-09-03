// cl: /DNDEBUG /MD /EHsc

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/wwstring.h
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

class Gen_dtor_00970f60Held
{
public:
	virtual void destroy();
	int m_refs;
};

class Gen_dtor_00970f60 : public Rva009EB810TailBase
{
public:
	virtual ~Gen_dtor_00970f60();

private:
	Gen_dtor_00970f60Held *m_ptr;
	StringClass m_name;
};

Gen_dtor_00970f60::~Gen_dtor_00970f60()
{
	Gen_dtor_00970f60Held *ptr = m_ptr;
	if (ptr && --ptr->m_refs == 0)
		ptr->destroy();
}
