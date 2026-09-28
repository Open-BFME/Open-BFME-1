// ?xferSelfAndCurLocoPtr@Rva001B74D0Owner@@QAEXPAVXfer@@PAPAX@Z
// Retail 0x001B74D0, 387 bytes.
// LocomotorSet transfer family: ZH xferSelfAndCurLocoPtr and BFME vector at +4.
// name_oracle LocomotorSet+4 witnesses m_locomotors.
// Native vector access and scoped version lifetime reproduce retail allocation.
// cl: /O2 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#include "ascii_string.h"
#include <vector>

template<> inline bool StringBase<char>::isEmpty() const { return !m_data || m_data->length == 0; }

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
	std::vector<void*> m_locomotors;
	void xferSelfAndCurLocoPtr(Xfer *xfer, void **output);
};

// ?xferSelfAndCurLocoPtr@Rva001B74D0Owner@@QAEXPAVXfer@@PAPAX@Z
void Rva001B74D0Owner::xferSelfAndCurLocoPtr(Xfer *xfer, void **output)
{
	Rva001B74D0Owner *self = this;
	{
	Rva001B74D0Version version;
	version.version = 1;
	version.currentVersion = 1;
	xfer->xferVersion(&version);
	}
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
			for (; i < self->m_locomotors.size(); ++i)
			{
				if (((Rva001B6070Owner *)self->m_locomotors[i])->getResolvedValue().compare(value) == 0)
				{
					*output = self->m_locomotors[i];
					return;
				}
			}
			{
				XferException error;
				bfmeFormatText(&error, 5, 0);
				_CxxThrowException(&error, &_g_rva005c5100ThrowInfo);
			}
		}
	}
}
