// cl: /EHsc /Igame/Libraries/Source/WWVegas/WWLib

// The matched W3DFloorDrawModuleDataBase constructor leaves an AsciiString at
// +0x08.  Its destructor tears that member down under an EH guard and restores
// the module-data parent vptr.

#include "ascii_string.h"

class W3DFloorDrawModuleDataParent
{
public:
	virtual ~W3DFloorDrawModuleDataParent() {}

private:
	unsigned int m_word;
};

class W3DFloorDrawModuleDataBase : public W3DFloorDrawModuleDataParent
{
public:
	virtual ~W3DFloorDrawModuleDataBase();

private:
	AsciiString m_name;
};

W3DFloorDrawModuleDataBase::~W3DFloorDrawModuleDataBase()
{
}
