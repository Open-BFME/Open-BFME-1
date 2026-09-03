// cl: /DNDEBUG /MD /EHsc

void __cdecl operator delete(void *);

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/htree.h
class HTreeClass
{
public:
	~HTreeClass();
};

class Gen_dtor_00971710 : public Rva009EB810TailBase
{
public:
	virtual ~Gen_dtor_00971710();

private:
	HTreeClass *m_ptr;
	StringClass m_name;
};

Gen_dtor_00971710::~Gen_dtor_00971710()
{
	delete m_ptr;
}
