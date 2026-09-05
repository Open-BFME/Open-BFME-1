// cl: /DNDEBUG /MD /EHsc

// Byte-twin of ??1Gen_dtor_00970f60@@UAE@XZ at 0x00970C40
// (Gen_dtor_00970f60.cpp): identical 103 bytes once relocations are masked;
// only the installed vtable (0x0113A510, tools/vtable_lookup.py) differs, so
// this is a sibling class with the same layout, claimed address-derived.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/wwstring.h
class StringClass
{
public:
	~StringClass();
	char *m_buffer;
};

class Rva0090BC40TailBase
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
	virtual ~Rva0090BC40TailBase();

private:
	char m_pad[0x10];
};

class Rva0090BC40Held
{
public:
	virtual void destroy();
	int m_refs;
};

class Rva0090BC40Dtor : public Rva0090BC40TailBase
{
public:
	virtual ~Rva0090BC40Dtor();

private:
	Rva0090BC40Held *m_ptr;
	StringClass m_name;
};

Rva0090BC40Dtor::~Rva0090BC40Dtor()
{
	Rva0090BC40Held *ptr = m_ptr;
	if (ptr && --ptr->m_refs == 0)
		ptr->destroy();
}
