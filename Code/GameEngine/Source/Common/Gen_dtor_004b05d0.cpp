// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
//
// Gen_dtor_004b05d0 is the polymorphic teardown at retail 0x004B0350.  The
// derived object owns an AsciiString at +0x08.  Its destructor first reports
// DeleteButtonFlash for that string, then releases the string and reseats the
// base vftable.
#include "string_base.h"

struct GenStringData
{
	int m_refCount;
	int m_capacity;
};

class GenString
{
public:
	GenStringData *m_data;
};

extern void Rva00565DA0(const GenString *value);

class AsciiString
{
public:
	~AsciiString()
	{
		((StringBase<char> *)this)->releaseBuffer();
	}

private:
	char *m_text;
};

class Gen_dtor_004b05d0Base
{
public:
	virtual ~Gen_dtor_004b05d0Base() {}

private:
	int m_baseField;
};

class Gen_dtor_004b05d0 : public Gen_dtor_004b05d0Base
{
public:
	virtual ~Gen_dtor_004b05d0();

private:
	AsciiString m_flashName;
};

Gen_dtor_004b05d0::~Gen_dtor_004b05d0()
{
	Rva00565DA0((const GenString *)&m_flashName);
}
