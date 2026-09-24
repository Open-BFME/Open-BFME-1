// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/ini
// stlport
// Retail 0x003D47A0 is called through ILT 0x00039117 by the matched
// Rva003D0A40Map::xfer loading branch. That caller passes a
// LargeGroupAudioKeyMap and Xfer, and this body rebuilds its key bits from
// transferred tokens. The method name retains the address token because no
// original declaration has been found.
#include "Common/AsciiString.h"
#include <vector>

typedef bool Bool;
typedef unsigned char UnsignedByte;

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

struct XferVersionSlot
{
	// Xfer reads the first two bytes. Reserving a four-byte local gives the
	// two string temporaries their observed retail stack positions.
	XferVersion m_active;
	XferVersion m_reserved;
};

class Xfer
{
public:
	virtual ~Xfer();
	virtual Bool isLoading();
	virtual Bool isSaving();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual Xfer &xferVersion(XferVersion *version);
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
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

class LargeGroupAudioKeyMap : public _STL::vector<void *, _STL::allocator<void *> >
{
public:
	void rva003D47A0Load(Xfer *xfer);
	void bfmeAddKey(const AsciiString &name);
};

class LGA_MemberObj;
void bfmeClearMembers(LGA_MemberObj *map);

void LargeGroupAudioKeyMap::rva003D47A0Load(Xfer *xfer)
{
	XferVersionSlot slot;
	slot.m_active.m_version = 1;
	slot.m_active.m_currentVersion = 1;
	xfer->xferVersion(&slot.m_active);
	if (!xfer->isLoading())
	{
		XferException error;
		bfmeFormatText(&error, 5, 0);
		_CxxThrowException(&error, (void *)0x011DFE5C);
	}

	AsciiString value;
	xfer->xferAsciiString(&value);
	for (iterator item = begin(); item != end(); ++item)
	{
		if (*item)
		{
			bfmeClearMembers((LGA_MemberObj *)this);
			erase(begin(), end());
			break;
		}
	}

	AsciiString name;
	while (value.nextToken(&name, 0))
		bfmeAddKey(name);
}
