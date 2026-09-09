// ?xferListAsciiStringUINT@@YAPAVXfer@@PAV?$list@U?$pair@VAsciiString@@I@_STL@@V?$allocator@U?$pair@VAsciiString@@I@_STL@@@2@@_STL@@@Z
// partial score=0.97 date=2026-09-08
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME: xferListAsciiStringUINT, retail 0x00344310.

#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include "string_base.h"

typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;
typedef unsigned int UnsignedInt;
typedef bool Bool;

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

class AsciiString
{
public:
	AsciiString(void) : m_data(0) {}
	AsciiString(const AsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&that);
	}
	~AsciiString(void)
	{
		((StringBase<char> *)this)->releaseBuffer();
	}

private:
	char *m_data;
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
	virtual Xfer &xferVersion(XferVersion *version);
	virtual Xfer &xferTypeName(const char *const &name);
	virtual void slot12(void);
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
	virtual void slot27(void);
	virtual void slot28(void);
	virtual Xfer &xferUnsignedShort(unsigned int *value);
};

struct XferException
{
	char *text;
	int tag;
};

extern "C" XferException *__cdecl bfmeFormatText(
	XferException *result, int tag, const char *format, ...);
extern int g_guardTargetTypeThrowInfo;
extern void __declspec(noreturn) __stdcall _CxxThrowException(
	void *object, void *throwInfo);

typedef _STL::pair<AsciiString, UnsignedInt> PairAsciiStringUINT;
typedef _STL::list<PairAsciiStringUINT> ListAsciiStringUINT;

// ?xferListAsciiStringUINT@@YAPAVXfer@@PAV1@PAV?$list@U?$pair@VAsciiString@@I@_STL@@V?$allocator@U?$pair@VAsciiString@@I@_STL@@@2@@_STL@@@Z
Xfer *xferListAsciiStringUINT(Xfer *xfer, ListAsciiStringUINT *list)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	xfer->xferVersion(&version);

	unsigned int count = list->size();
	xfer->xferTypeName("std::list").xferUnsignedShort(&count);

	if (xfer->isSaving())
	{
		ListAsciiStringUINT::_Node *sentinel = list->_M_node._M_data;
		ListAsciiStringUINT::_Node *node =
			(ListAsciiStringUINT::_Node *)sentinel->_M_next;
		while (node != sentinel)
		{
			PairAsciiStringUINT *pair = &node->_M_data;
			xfer->xferAsciiString(&pair->first)
				.xferUnsignedShort(&pair->second);
			node = (ListAsciiStringUINT::_Node *)node->_M_next;
		}
	}
	else
	{
		if (!list->empty())
		{
			XferException error;
			bfmeFormatText(&error, 4, "List must be empty on load");
			_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
		}

		PairAsciiStringUINT newPair;
		while (count != 0)
		{
			--count;
			xfer->xferAsciiString(&newPair.first)
				.xferUnsignedShort(&newPair.second);
			list->push_back(newPair);
		}
		--count;
	}
	return xfer;
}
