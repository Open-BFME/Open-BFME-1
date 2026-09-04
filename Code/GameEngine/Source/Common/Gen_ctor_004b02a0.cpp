// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
//
// Constructor body at retail 0x004B02A0.  The object is the polymorphic
// button-flash action holder paired with Gen_dtor_004b05d0: its base counter,
// two POD fields and one AsciiString are initialized before the Create and
// Show action-sink forwarders receive the generated Flash%d name.
#include "ascii_string.h"

class GenString
{
	void *m_data;
};

extern void Rva00565D50(const GenString *value);
extern void Rva00565E90(const GenString *value);

extern int g_buttonFlashNumber;

class Gen_ctor_004b02a0Base
{
public:
	Gen_ctor_004b02a0Base() : m_baseField(0) {}
	virtual ~Gen_ctor_004b02a0Base() {}

private:
	int m_baseField;
};

class Gen_ctor_004b02a0 : public Gen_ctor_004b02a0Base
{
public:
	Gen_ctor_004b02a0();
	virtual ~Gen_ctor_004b02a0();

private:
	AsciiString m_flashName;
	int m_field0C;
	int m_field10;
};

Gen_ctor_004b02a0::Gen_ctor_004b02a0()
{
	m_field0C = 0;
	m_field10 = 0;
	int flashNumber = g_buttonFlashNumber++;
	m_flashName.format(AsciiString("Flash%d"), flashNumber);
	Rva00565D50((const GenString *)&m_flashName);
	Rva00565E90((const GenString *)&m_flashName);
}
