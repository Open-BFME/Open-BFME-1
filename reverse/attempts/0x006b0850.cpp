// ?xferMap@@YAPAVXfer@@PAV1@PAX@Z
// partial score=0.9 date=2026-09-12
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /I../../../vendor/stlport
// stlport

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"
#define _STLP_USE_NAMESPACES 1
#define _STLP_USE_OWN_NAMESPACE 1
#include <map>

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	AsciiString(const AsciiString &other)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&other);
	}
	~AsciiString()
	{
		((StringBase<char> *)this)->releaseBuffer();
	}

private:
	char *m_data;
};

inline bool operator<(const AsciiString &, const AsciiString &)
{
	return false;
}

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

struct XferMapData
{
	UnsignedInt m_count;
	XferVersion m_version;
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
	virtual Xfer &xferTypeName(const char *const &name);
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
	virtual Xfer &xferReal(float *value);
	virtual void slot28();
	virtual Xfer &xferUnsignedInt(UnsignedInt *value);
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

struct RbNode
{
	int m_color;
	RbNode *m_parent;
	RbNode *m_left;
	RbNode *m_right;
};

struct RbPair
{
	AsciiString m_key;
	float m_value;
};

struct AsciiStringFloatMapLayout
{
	RbNode *m_header;
	UnsignedInt m_count;
};

typedef _STL::map<AsciiString, float> AsciiStringFloatMap;

class AsciiStringFloatMapIndex
{
public:
	float &operator[](const AsciiString &key);
};

#pragma comment(linker, "/alternatename:??AAsciiStringFloatMapIndex@@QAEAAMABVAsciiString@@@Z=?j_0000d9d1@@YAXXZ")

// ?xferMap@@YAPAVXfer@@PAV1@PAX@Z
Xfer *xferMap(Xfer *xfer, void *rawMap)
{
	AsciiStringFloatMap *map = (AsciiStringFloatMap *)rawMap;
	AsciiStringFloatMapLayout *layout = (AsciiStringFloatMapLayout *)rawMap;
	UnsignedInt count;
	{
		__declspec(align(8)) XferVersion version;
		version.m_version = 1;
		version.m_currentVersion = 1;
		xfer->xferVersion(&version);
	}

	count = layout->m_count;
	xfer->xferTypeName("std::map").xferUnsignedInt(&count);

	if (xfer->isSaving())
	{
		RbNode *sentinel = layout->m_header;
		RbNode *node = sentinel->m_left;
		while (node != sentinel)
		{
			RbPair *pair = (RbPair *)(node + 1);
			AsciiString key(pair->m_key);
			float value = pair->m_value;
			xfer->xferAsciiString(&key);
			xfer->xferReal(&value);
			node = (RbNode *)_STL::_Rb_global<bool>::_M_increment(
				(_STL::_Rb_tree_node_base *)node);
		}
	}
	else
	{
		if (layout->m_count != 0)
		{
			XferException error;
			bfmeFormatText(&error, 4, "Map must be empty on load");
			_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
		}

		AsciiString key;
		float value = 0;
		while (count != 0)
		{
			--count;
			xfer->xferAsciiString(&key);
			xfer->xferReal(&value);
			(*(AsciiStringFloatMapIndex *)map)[key] = value;
		}
		--count;
	}
	return xfer;
}
