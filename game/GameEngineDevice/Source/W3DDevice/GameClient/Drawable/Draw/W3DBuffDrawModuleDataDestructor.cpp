// cl: /EHsc /Igame/Libraries/Source/WWVegas/WWLib

// W3DBuffDrawModuleData's adjacent exact constructor initializes the owning
// AsciiString at +0x08 and a flag at +0x0C.  The retail destructor tears down
// that string under an EH guard and restores its module-data base vptr.

#include "ascii_string.h"

class W3DBuffDrawModuleDataBase
{
public:
	virtual ~W3DBuffDrawModuleDataBase() {}

private:
	unsigned int m_word;
};

class W3DBuffDrawModuleData : public W3DBuffDrawModuleDataBase
{
public:
	virtual ~W3DBuffDrawModuleData();

private:
	AsciiString m_modelName;
	bool m_flag;
};

W3DBuffDrawModuleData::~W3DBuffDrawModuleData()
{
}
