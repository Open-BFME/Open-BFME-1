// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: BroadcastStealthUpdateModuleData dtor. dual different members SEH.

// The +0x28 member is destroyed by the inlined StringBase<char> destructor,
// i.e. a direct call to StringBase<char>::releaseBuffer at 0x00887940, so the
// member is the real AsciiString (four bytes, no added data) rather than an
// invented class with an undefined destructor.
#include "../../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

class AttributeModifierAuraUpdateModuleDataMemberD
{
public:
	~AttributeModifierAuraUpdateModuleDataMemberD();
private:
	unsigned char m_pad[4];
};

class BroadcastStealthUpdateModuleDataBase
{
public:
	virtual ~BroadcastStealthUpdateModuleDataBase() {}
private:
	unsigned char m_pad[0x24];
};

class __declspec(novtable) BroadcastStealthUpdateModuleData : public BroadcastStealthUpdateModuleDataBase
{
public:
	virtual ~BroadcastStealthUpdateModuleData();
private:
	AsciiString m_a;
	AttributeModifierAuraUpdateModuleDataMemberD m_b;
};

// ??1BroadcastStealthUpdateModuleData@@UAE@XZ
BroadcastStealthUpdateModuleData::~BroadcastStealthUpdateModuleData()
{
}
