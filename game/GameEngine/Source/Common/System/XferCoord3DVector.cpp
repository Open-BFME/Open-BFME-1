// cl: /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /MD /EHsc /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/asciistring_thin /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad
// stlport

#define BFME_STLP_NODE_ALLOC
#include <vector>

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;

struct Coord3D
{
	float x;
	float y;
	float z;

	Coord3D(void) {}
	Coord3D(const Coord3D &that)
	{
		x = that.x;
		y = that.y;
		z = that.z;
	}
	~Coord3D(void) {}
};

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
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
	virtual Xfer &xferAsciiString(void *value);
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
extern int g_guardTargetTypeThrowInfo;
extern void __declspec(noreturn) __stdcall _CxxThrowException(
	void *object, void *throwInfo);

typedef _STL::vector<Coord3D> Coord3DVector;

// ?xferCoord3DVector@@YAPAVXfer@@PAV1@PAV?$vector@UCoord3D@@V?$allocator@UCoord3D@@@_STL@@@_STL@@@Z
Xfer *xferCoord3DVector(Xfer *xfer, Coord3DVector *vector)
{
	Coord3D value;
	union VersionStorage
	{
		XferVersion version;
		unsigned char padding[4];
	} versionStorage;
	UnsignedInt count;
	versionStorage.version.m_version = 1;
	versionStorage.version.m_currentVersion = 1;
	xfer->xferVersion(&versionStorage.version);

	count = vector->size();
	xfer->xferTypeName("std::vector").xferUnsignedShort(&count);

	if (xfer->isSaving())
	{
		Coord3D *end = vector->end();
		Coord3D *current = vector->begin();
		while (current != end)
		{
			xfer->xferCoord3D(current);
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
		while (count != 0)
		{
			--count;
			xfer->xferCoord3D(&value);
			vector->push_back(value);
		}
	}
	return xfer;
}
