// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// 0x0020EB40: slot 11 of the ActiveBody-family vtables. The slot alone does
// not establish a unique semantic owner, so this method keeps its address.
// The two one-pointer entries at module data +0x30/+0x34 are checked through
// the StringBase<char> header layout inlined by retail. The first call target
// is the already matched address-derived BfmeOwnerXI body; its one-pointer
// argument ABI is independently visible in the retail callee.

#include "ascii_string.h"

class Object
{
public:
	bool applyAttributeModifier(const AsciiString &name, int duration);
};

class BfmeMsgXI;
class BfmeOwnerXI
{
public:
	void bfmeSendXI(BfmeMsgXI *message);
};

struct Rva0020EB40Pair
{
	unsigned char m_pad00[0x30];
	AsciiString m_first;
	AsciiString m_second;
};

struct Rva0020EB40StringHeader
{
	int references;
	unsigned short length;
	unsigned short capacity;
};

static inline bool hasString(const AsciiString &value)
{
	// ascii_string.h delegates isNotEmpty() out of line; retail performs this
	// pointer/length check in line. The StringBase<char> header supplies both.
	const Rva0020EB40StringHeader *data = *(const Rva0020EB40StringHeader *const *)&value;
	return data && data->length != 0;
}

class Rva0020EB40Owner
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void rva0020EB40ApplyModifiers();
private:
	Rva0020EB40Pair *m_pair;
	Object *m_object;
	unsigned char m_pad0C[0x24];
	int m_mode;
};

void Rva0020EB40Owner::rva0020EB40ApplyModifiers()
{
	Rva0020EB40Pair *pair = m_pair;
	switch(m_mode) {
	case 1:
		if(hasString(pair->m_first))
			m_object->applyAttributeModifier(pair->m_first, -1);
		break;
	case 2:
		if(hasString(pair->m_first))
			((BfmeOwnerXI *)m_object)->bfmeSendXI((BfmeMsgXI *)&pair->m_first);
		if(hasString(pair->m_second))
			m_object->applyAttributeModifier(pair->m_second, -1);
		return;
	default:
		if(hasString(pair->m_first))
			((BfmeOwnerXI *)m_object)->bfmeSendXI((BfmeMsgXI *)&pair->m_first);
		break;
	}
	if(hasString(pair->m_second))
		((BfmeOwnerXI *)m_object)->bfmeSendXI((BfmeMsgXI *)&pair->m_second);
}
