// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME: OpenContain::getPassengerBoneName, retail 0x002228E0.
// The BFME passenger-bone list lives at OpenContainModuleData+0x11C. Each
// entry stores a 116-bit KindOf mask at +0x08 and an AsciiString at +0x20.

typedef bool Bool;
typedef unsigned int UnsignedInt;

template <int NUMBITS>
class BitFlags
{
public:
	UnsignedInt m_bits[(NUMBITS + 31) / 32];
};

typedef BitFlags<116> KindOfMaskType;

extern const KindOfMaskType KINDOFMASK_NONE;

#include "string_base.h"

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
};

class Thing
{
public:
	Bool isKindOfMulti(const KindOfMaskType &mustBeSet,
		const KindOfMaskType &mustBeClear) const;
};

class Object : public Thing
{
};

struct PassengerBoneNode
{
	PassengerBoneNode *m_next;
	PassengerBoneNode *m_prev;
	KindOfMaskType m_kindOf;
	char m_unreconstructed18[8];
	AsciiString m_boneName;
};

struct PassengerBoneList
{
	PassengerBoneNode *m_head;
};

class OpenContainModuleData
{
private:
	char m_unreconstructed00[0x11C];

public:
	PassengerBoneList m_passengerBonePrefix;
};

class OpenContain
{
public:
	virtual void unusedVirtual();
	AsciiString getPassengerBoneName(Object *object);

private:
	OpenContainModuleData *m_moduleData;
};

// ?getPassengerBoneName@OpenContain@@QAE?AVAsciiString@@PAVObject@@@Z
AsciiString OpenContain::getPassengerBoneName(Object *object)
{
	register OpenContainModuleData *moduleData = m_moduleData;
	register PassengerBoneNode *node =
		moduleData->m_passengerBonePrefix.m_head->m_next;
	while (node != moduleData->m_passengerBonePrefix.m_head)
	{
		if (object == 0 || object->isKindOfMulti(node->m_kindOf,
			KINDOFMASK_NONE))
			return node->m_boneName;
		node = node->m_next;
	}
	return AsciiString("ARROW_");
}
