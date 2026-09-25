// ?xferSelfAndCurLocoPtr@Rva001B74D0Owner@@QAEXPAVXfer@@PAPAX@Z
// partial score=0.4393 date=2026-09-24
// cl: /O2 /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// stlport

#include "ascii_string.h"

typedef unsigned char UnsignedByte;
typedef bool Bool;

struct Rva001B74D0Version
{
	UnsignedByte version;
	UnsignedByte currentVersion;
};

class Xfer
{
public:
	virtual ~Xfer(void);
	virtual Bool isLoading(void);
	virtual Bool isSaving(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual void slot07(void);
	virtual void slot08(void);
	virtual void slot09(void);
	virtual Xfer &xferVersion(Rva001B74D0Version *version);
	virtual void slot11(void);
	virtual Xfer &xferSnapshot(void *object);
	virtual void slot13(void);
	virtual void slot14(void);
	virtual void slot15(void);
	virtual void slot16(void);
	virtual void slot17(void);
	virtual void slot18(void);
	virtual void slot19(void);
	virtual void slot20(void);
	virtual void slot21(void);
	virtual void slot22(void);
	virtual void slot23(void);
	virtual void slot24(void);
	virtual void slot25(void);
	virtual Xfer &xferAsciiString(AsciiString *value);

};

struct XferException
{
	char *text;
	int tag;
};
extern "C" XferException *__cdecl bfmeFormatText(
	XferException *result, int tag, const char *format, ...);
extern void __declspec(noreturn) __stdcall _CxxThrowException(
	void *object, void *throwInfo);
extern int _g_rva005c5100ThrowInfo;

class Rva001B6070Owner
{
public:
	AsciiString getResolvedValue(void) const;
};

struct Rva001B74D0Owner
{
	void *vtable;
	void **elementsBegin;
	void **elementsEnd;
	void **elementsCapacity;
	void xferSelfAndCurLocoPtr(Xfer *xfer, void **output);
};

// ?d_001b74d0@@YAXXZ
void Rva001B74D0Owner::xferSelfAndCurLocoPtr(Xfer *xfer, void **output)
{
	Rva001B74D0Version version;
	Rva001B74D0Owner *self = this;
	version.version = 1;
	version.currentVersion = 1;
	xfer->xferVersion(&version);
	xfer->xferSnapshot(this);

	if (xfer->isSaving())
	{
		AsciiString value;
		if (*output != 0)
			value = ((Rva001B6070Owner *)*output)->getResolvedValue();
		xfer->xferAsciiString(&value);
	}
	else
	{
		AsciiString value;
		xfer->xferAsciiString(&value);
		if (value.isEmpty())
		{
			*output = 0;
		}
		else
		{
			unsigned int i = 0;
			for (; i < (unsigned int)(self->elementsEnd - self->elementsBegin); ++i)
			{
				if (((Rva001B6070Owner *)self->elementsBegin[i])->getResolvedValue().compare(value) == 0)
					break;
			}
			if (i == (unsigned int)(self->elementsEnd - self->elementsBegin))
			{
				XferException error;
				bfmeFormatText(&error, 5, 0);
				_CxxThrowException(&error, &_g_rva005c5100ThrowInfo);
			}
			*output = self->elementsBegin[i];
		}
	}
}
