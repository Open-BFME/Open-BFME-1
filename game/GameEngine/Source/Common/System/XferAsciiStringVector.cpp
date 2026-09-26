// cl: /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /MD /EHsc /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/asciistring_thin /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#define BFME_STLP_NODE_ALLOC
#include <vector>

#include "ascii_string.h"

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef bool Bool;

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
	virtual Xfer &xferVersion(XferVersion &version);
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
	virtual Xfer &xferAsciiString(AsciiString &value);
	virtual void slot27();
	virtual void slot28();
	virtual Xfer &xferUnsignedInt(UnsignedInt &value);
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

typedef _STL::vector<AsciiString> AsciiStringVector;

// ?xferAsciiStringVector@@YAPAVXfer@@PAV1@PAV?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@@Z
Xfer *xferAsciiStringVector(Xfer *xfer, AsciiStringVector *vector)
{
	XferVersion version;
	version.m_version = 1;
	version.m_currentVersion = 1;
	xfer->xferVersion(version);

	UnsignedInt count = vector->size();
	xfer->xferTypeName("std::vector").xferUnsignedInt(count);

	if (xfer->isSaving())
	{
		AsciiString *end = vector->end();
		AsciiString *current = vector->begin();
		while (current != end)
		{
			xfer->xferAsciiString(*current);
			++current;
		}
	}
	else
	{
		if (!vector->empty())
		{
			XferException error;
			bfmeFormatText(&error, 4, "Vector must be empty on load");
			_CxxThrowException(&error, &g_guardTargetTypeThrowInfo);
		}

		vector->reserve(count);
		AsciiString value;
		while (count != 0)
		{
			--count;
			xfer->xferAsciiString(value);
			vector->push_back(value);
		}
		--count;
	}
	return xfer;
}
