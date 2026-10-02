// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib
// stlport

// Open-BFME5: AttributeModifierAuraUpdateModuleDataMemberD's destructor, retail
// 0x00129C80, 90 bytes. AttributeModifierAuraUpdateModuleData's own destructor
// -- already ledgered -- is what holds this class as its last member. The
// three twelve-byte members are STLport vector<AsciiString> instances whose
// shared matched destructor body is reached through ILT 0x00026AB2.
//
// Three members at +0x30, +0x3C and +0x48, destroyed in that order, which is
// reverse declaration order. They are contiguous and twelve bytes apart, so
// each is twelve bytes wide. There is no vptr store and no base call.

#include <vector>
#include "ascii_string.h"

extern template _STL::vector<AsciiString>::~vector();

typedef char StringVectorMustBeTwelveBytes[
	sizeof(_STL::vector<AsciiString>) == 12 ? 1 : -1];

class AttributeModifierAuraUpdateModuleDataMemberD
{
public:
	~AttributeModifierAuraUpdateModuleDataMemberD();

private:
	unsigned char m_bfmeHead[0x30];
	_STL::vector<AsciiString> m_bfmeFirst;				// +0x30
	_STL::vector<AsciiString> m_bfmeSecond;				// +0x3C
	_STL::vector<AsciiString> m_bfmeThird;				// +0x48
};

// ??1AttributeModifierAuraUpdateModuleDataMemberD@@QAE@XZ
AttributeModifierAuraUpdateModuleDataMemberD::~AttributeModifierAuraUpdateModuleDataMemberD()
{
}
