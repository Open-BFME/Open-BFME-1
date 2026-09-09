// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME: xferListAsciiStringObjectID, retail 0x00344750.

#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include "string_base.h"

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef bool Bool;

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
	unsigned short m_padding;
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

	AsciiString &operator=(const AsciiString &that)
	{
		((StringBase<char> *)this)->StringBase<char>::operator=(
			*(const StringBase<char> *)&that);
		return *this;
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
	virtual Xfer &xferUnsignedShort(UnsignedInt *value);
};

struct XferException
{
	char *text;
	int tag;
};

extern "C" XferException *__cdecl bfmeFormatText(
	XferException *result, int tag, const char *format, ...);
extern void __cdecl bfmeCalcTGC(void *xfer, int *value);
extern int g_guardTargetTypeThrowInfo;
extern void __declspec(noreturn) __stdcall _CxxThrowException(
	void *object, void *throwInfo);

typedef _STL::pair<AsciiString, int> AsciiStringObjectIDPair;
typedef _STL::list<AsciiStringObjectIDPair> ListAsciiStringObjectID;

// ?xferListAsciiStringObjectID@@YAPAVXfer@@PAV1@PAV?$list@U?$pair@VAsciiString@@H@_STL@@V?$allocator@U?$pair@VAsciiString@@H@_STL@@@2@@_STL@@@Z
Xfer *xferListAsciiStringObjectID(
	Xfer *xfer, ListAsciiStringObjectID *list)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	xfer->xferVersion(&version);

	UnsignedInt count = list->size();
	xfer->xferTypeName("std::list").xferUnsignedShort(&count);

	if (xfer->isSaving())
	{
		ListAsciiStringObjectID::_Node *sentinel = list->_M_node._M_data;
		ListAsciiStringObjectID::_Node *node =
			(ListAsciiStringObjectID::_Node *)sentinel->_M_next;
		while (node != sentinel)
		{
			AsciiStringObjectIDPair *pair = &node->_M_data;
			bfmeCalcTGC(
				&xfer->xferAsciiString(&pair->first),
				(int *)&pair->second);
			node = (ListAsciiStringObjectID::_Node *)node->_M_next;
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

		AsciiStringObjectIDPair newPair;
		while (count != 0)
		{
			--count;
			bfmeCalcTGC(
				&xfer->xferAsciiString(&newPair.first),
				(int *)&newPair.second);
			list->push_back(newPair);
		}
		--count;
	}
	return xfer;
}
