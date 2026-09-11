// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline

#include "StringInline.h"

typedef bool Bool;
typedef int Int;

enum KindOfType
{
	KINDOF_INVALID = -1
};

extern const char *TheKindOfBitNames[0xB5];

class KindOfMaskType
{
public:
	static const char *getNameFromSingleBit(Int bit)
	{
		if (bit < 0 || bit >= sizeof(TheKindOfBitNames)/sizeof(TheKindOfBitNames[0]))
			return 0;
		return TheKindOfBitNames[bit];
	}
};

extern int bfmeLookup_000d1020(void *name); // ILT 0x0004AFFC

class Xfer;

class Rva0010C980XferView
{
public:
	virtual ~Rva0010C980XferView(void);
	virtual Bool slot01(void);                         // +04
	virtual Bool isSaving(void) const;                 // +08
	virtual Bool slot03(void);                         // +0C
	virtual Bool isLightCRC(void) const;               // +10
	virtual void slot05(void);                         // +14
	virtual void slot06(void);                         // +18
	virtual void slot07(void);                         // +1C
	virtual void slot08(void);                         // +20
	virtual void slot09(void);                         // +24
	virtual void slot10(void);                         // +28
	virtual void slot11(void);                         // +2C
	virtual void slot12(void);                         // +30
	virtual void slot13(void);                         // +34
	virtual void slot14(void);                         // +38
	virtual void slot15(void);                         // +3C
	virtual void slot16(void);                         // +40
	virtual void slot17(void);                         // +44
	virtual void slot18(void);                         // +48
	virtual void slot19(void);                         // +4C
	virtual void slot20(void);                         // +50
	virtual void slot21(void);                         // +54
	virtual void slot22(void);                         // +58
	virtual void slot23(void);                         // +5C
	virtual void slot24(void);                         // +60
	virtual void slot25(void);                         // +64
	virtual Rva0010C980XferView &xferAsciiString(AsciiString &value); // +68
	virtual void slot27(void);                         // +6C
	virtual void slot28(void);                         // +70
	virtual void slot29(void);                         // +74
	virtual void slot30(void);                         // +78
	virtual void slot31(void);                         // +7C
	virtual void slot32(void);                         // +80
	virtual void slot33(void);                         // +84
	virtual void slot34(void);                         // +88
	virtual void slot35(void);                         // +8C
	virtual Rva0010C980XferView &xferEnum(const char *name, void *data, unsigned int size); // +90
};

// Retail 0x0010C980 transfers a KindOfType as an enum during LightCRC and as
// an AsciiString during save and load.
Xfer *__cdecl Rva0010C980XferKindOf(Xfer *xfer, KindOfType *kindOfData)
{
	Rva0010C980XferView *receiver = reinterpret_cast<Rva0010C980XferView *>(xfer);
	if (receiver->isLightCRC())
	{
		receiver->xferEnum("KindOfType", kindOfData, 4);
		return xfer;
	}
	if (receiver->isSaving())
	{
		AsciiString kindOfName = KindOfMaskType::getNameFromSingleBit(*kindOfData);
		receiver->xferAsciiString(kindOfName);
	}
	else
	{
		AsciiString kindOfName;
		receiver->xferAsciiString(kindOfName);
		Int bit = bfmeLookup_000d1020((void *)kindOfName.str());
		if (bit != -1)
			*kindOfData = (KindOfType)bit;
	}
	return xfer;
}
