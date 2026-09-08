// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline

#include "StringInline.h"

enum ScienceType
{
	SCIENCE_INVALID = -1
};
typedef bool Bool;

class Rva0010C5E0XferView
{
public:
	virtual ~Rva0010C5E0XferView(void);
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
	virtual Rva0010C5E0XferView &xferAsciiString(AsciiString &value); // +68
	virtual void slot27(void);                         // +6C
	virtual void slot28(void);                         // +70
	virtual void slot29(void);                         // +74
	virtual void slot30(void);                         // +78
	virtual void slot31(void);                         // +7C
	virtual void slot32(void);                         // +80
	virtual void slot33(void);                         // +84
	virtual void slot34(void);                         // +88
	virtual void slot35(void);                         // +8C
	virtual Rva0010C5E0XferView &xferEnum(const char *name, void *data, unsigned int size); // +90
};
class Xfer;

class ScienceStore
{
public:
	AsciiString getInternalNameForScience(ScienceType science) const;
	ScienceType getScienceFromInternalName(const AsciiString &name) const;
};
extern ScienceStore *TheScienceStore;

class XferException
{
public:
    XferException(int tag, const char *format, ...);
    XferException(const XferException &that);
    ~XferException(void);
    char *text;
    int tagValue;
};

// Retail 0x0010C5E0: complete 258-byte transfer, including both string cleanup states.
Xfer *__cdecl Rva0010C5E0XferScience(Xfer *xfer, ScienceType *science)
{
	Rva0010C5E0XferView *receiver = reinterpret_cast<Rva0010C5E0XferView *>(xfer);
	if (receiver->isLightCRC())
	{
		receiver->xferEnum("ScienceType", science, 4);
		return xfer;
	}
	if (receiver->isSaving())
	{
		AsciiString name = TheScienceStore->getInternalNameForScience(*science);
		receiver->xferAsciiString(name);
	}
	else
	{
		AsciiString name;
		receiver->xferAsciiString(name);
		*science = TheScienceStore->getScienceFromInternalName(name);
		if (*science == SCIENCE_INVALID)
		{
			throw XferException(0, 0);
		}
	}
	return xfer;
}
