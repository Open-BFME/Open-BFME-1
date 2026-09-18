// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: ObjectCreationUpgradeModuleData dtor.
// Member @+0x10, triple AsciiString @+0x78/+0x7c/+0x80.

class ObjectCreationUpgradeModuleDataMemberA
{
public:
	~ObjectCreationUpgradeModuleDataMemberA();
private:
	unsigned char m_pad[0x68];
};

// The three strings destroy their buffers through retail 0x00887940.
#include "../../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"


class ObjectCreationUpgradeModuleDataBase
{
public:
	virtual ~ObjectCreationUpgradeModuleDataBase() {}
private:
	unsigned char m_pad[0xc];
};

class __declspec(novtable) ObjectCreationUpgradeModuleData
	: public ObjectCreationUpgradeModuleDataBase
{
public:
	virtual ~ObjectCreationUpgradeModuleData();
private:
	ObjectCreationUpgradeModuleDataMemberA m_a;
	// Named factory 0x0011D4A0 -> callback 0x002D6D60 registers table
	// RVA 0x00CCD6C0: RemoveUpgrade/+78, GrantUpgrade/+7c and
	// ThingToSpawn/+80 all use INI::parseAsciiString (0x00851EE0).
	AsciiString m_removeUpgrade;
	AsciiString m_grantUpgrade;
	AsciiString m_thingToSpawn;
};

// ??1ObjectCreationUpgradeModuleData@@UAE@XZ
ObjectCreationUpgradeModuleData::~ObjectCreationUpgradeModuleData()
{
}
