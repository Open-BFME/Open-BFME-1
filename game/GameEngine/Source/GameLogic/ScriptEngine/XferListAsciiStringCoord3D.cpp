// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME: xferListAsciiStringCoord3D, retail 0x00344530.

#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include "string_base.h"

typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;
typedef bool Bool;

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

#include "ascii_string.h"

struct AsciiStringCoord3DPair
{
	AsciiString first;
	Coord3D second;
	AsciiStringCoord3DPair(void) {}
	AsciiStringCoord3DPair(const AsciiStringCoord3DPair &that) : first(that.first)
	{
		second.x = that.second.x;
		second.y = that.second.y;
		second.z = that.second.z;
	}
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
	virtual void xferCoord3D(Coord3D *value);
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

typedef _STL::list<AsciiStringCoord3DPair> ListAsciiStringCoord3D;

// ?xferListAsciiStringCoord3D@@YAPAVXfer@@PAV1@PAV?$list@UAsciiStringCoord3DPair@@V?$allocator@UAsciiStringCoord3DPair@@@_STL@@@_STL@@@Z
Xfer *xferListAsciiStringCoord3D(Xfer *xfer, ListAsciiStringCoord3D *list)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	xfer->xferVersion(&version);

	unsigned int count = list->size();
	xfer->xferTypeName("std::list").xferUnsignedShort(&count);

	if (xfer->isSaving())
	{
		ListAsciiStringCoord3D::_Node *sentinel = list->_M_node._M_data;
		ListAsciiStringCoord3D::_Node *node =
			(ListAsciiStringCoord3D::_Node *)sentinel->_M_next;
		while (node != sentinel)
		{
			AsciiStringCoord3DPair *pair = &node->_M_data;
			xfer->xferAsciiString(&pair->first)
				.xferCoord3D(&pair->second);
			node = (ListAsciiStringCoord3D::_Node *)node->_M_next;
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

		AsciiStringCoord3DPair newPair;
		while (count != 0)
		{
			--count;
			xfer->xferAsciiString(&newPair.first)
				.xferCoord3D(&newPair.second);
			list->push_back(newPair);
		}
		--count;
	}
	return xfer;
}
