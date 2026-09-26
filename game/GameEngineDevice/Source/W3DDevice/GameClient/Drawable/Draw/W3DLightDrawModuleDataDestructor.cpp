// cl: /EHsc /Igame/Libraries/Source/WWVegas/WWLib

// The exact constructor initializes W3DLightDrawModuleData's sole owning
// AsciiString at +0x44 before its scalar fields.  The retail destructor tears
// that member down under an EH guard and restores the module-data base vptr.

#include "ascii_string.h"

class W3DLightDrawModuleDataBase
{
public:
	virtual ~W3DLightDrawModuleDataBase() {}

private:
	unsigned int m_word;
};

class W3DLightDrawModuleData : public W3DLightDrawModuleDataBase
{
public:
	virtual ~W3DLightDrawModuleData();

private:
	unsigned char m_fields08[ 0x3C ];
	AsciiString m_textureName;
};

W3DLightDrawModuleData::~W3DLightDrawModuleData()
{
}
