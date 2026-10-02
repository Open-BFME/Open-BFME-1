// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME5: AttributeModifierAuraUpdateModuleData dtor.
// Four staggered members @+0x08/+0x0c/+0x24/+0x28.

#include <vector>
#include "ascii_string.h"

// ILT 0x00026AB2 reaches the shared vector destructor at 0x000658A0.
extern template _STL::vector<AsciiString>::~vector();

// ILT 0x0001A401 reaches AttributeHandleStandIn's destructor at 0x0039D550.
class AttributeHandleStandIn
{
public:
	~AttributeHandleStandIn();
private:
	unsigned char m_pad[4];
};

class AttributeModifierAuraUpdateModuleDataMemberD
{
public:
	~AttributeModifierAuraUpdateModuleDataMemberD();
private:
	unsigned char m_pad[4];
};

class AttributeModifierAuraUpdateModuleDataBase
{
public:
	virtual ~AttributeModifierAuraUpdateModuleDataBase() {}
private:
	unsigned char m_pad[4];
};

class __declspec(novtable) AttributeModifierAuraUpdateModuleData
	: public AttributeModifierAuraUpdateModuleDataBase
{
public:
	virtual ~AttributeModifierAuraUpdateModuleData();
private:
	AsciiString m_a;
	_STL::vector<AsciiString> m_b;
	unsigned char m_gap[0x0c];
	AttributeHandleStandIn m_c;
	AttributeModifierAuraUpdateModuleDataMemberD m_d;
};

// ??1AttributeModifierAuraUpdateModuleData@@UAE@XZ
AttributeModifierAuraUpdateModuleData::~AttributeModifierAuraUpdateModuleData()
{
}
