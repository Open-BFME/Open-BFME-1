// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /I../../../vendor/stlport
// stlport

#include "../../../Libraries/Source/WWVegas/WWLib/string_base.h"
#define _STLP_USE_NAMESPACES 1
#define _STLP_USE_OWN_NAMESPACE 1
#include <set>

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
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
	virtual void slot27();
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
	AsciiString m_value;
};

struct AsciiStringSetLayout
{
	RbNode *m_header;
	UnsignedInt m_count;
};

typedef _STL::set<AsciiString> AsciiStringSet;

// ?xferTree@@YAPAVXfer@@PAV1@PAX@Z
Xfer *xferTree(Xfer *xfer, void *rawTree)
{
	AsciiStringSet *tree = (AsciiStringSet *)rawTree;
	AsciiStringSetLayout *layout = (AsciiStringSetLayout *)rawTree;
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	xfer->xferVersion(&version);

	UnsignedInt count = layout->m_count;
	xfer->xferTypeName("std::set").xferUnsignedInt(&count);

	if (xfer->isSaving())
	{
		RbNode *sentinel = layout->m_header;
		RbNode *node = sentinel->m_left;
		while (node != sentinel)
		{
			xfer->xferAsciiString(&node->m_value);
			node = (RbNode *)_STL::_Rb_global<bool>::_M_increment(
				(_STL::_Rb_tree_node_base *)node);
		}
	}
	else
	{
		if (layout->m_count != 0)
		{
			XferException error;
			bfmeFormatText(&error, 4, "Set must be empty on load");
			_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
		}
		AsciiString value;
		while (count != 0)
		{
			--count;
			xfer->xferAsciiString(&value);
			tree->insert(value);
		}
		--count;
	}
	return xfer;
}
