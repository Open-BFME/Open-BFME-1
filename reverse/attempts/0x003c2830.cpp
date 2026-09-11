// ?Rva003C2830XferMissionObjectiveStateVector@@YAPAVXfer@@PAV1@PAV?$vector@UMissionObjectiveState@@V?$allocator@UMissionObjectiveState@@@_STL@@@_STL@@@Z
// partial score=0.98 date=2026-09-11
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /MD /EHsc /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad
// stlport
//
// Retail 0x003C2830, 326 bytes; same Xfer<T>Vector family as the matched
// XferBoolVector/XferScienceVector/XferCoord3DVector/XferObjectIDVector
// siblings (shared "std::vector" literal at 0x01075548). Element size 2
// (sar edx,1 on the begin/end difference) with two xferBool calls per
// element identifies MissionObjectiveState { Bool m_visible; Bool
// m_completed; }, the exact struct already landed in
// LivingWorldLogicSetMissionObjectiveVisible.cpp, whose vector member sits
// at LivingWorldLogic+0x84. reverse/symbols.csv pins the STLport overflow
// helper for this element type at 0x0000791E, proven by the
// setMissionObjectiveVisible push_back call at the neighboring 0x003C29D0.
// No named caller reaches this vector-xfer helper itself, so the function
// name is address-derived like its ScienceVector sibling.

#define BFME_STLP_NODE_ALLOC
#include <vector>

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
	virtual Xfer &xferAsciiString(void *value);
	virtual void slot27(void);
	virtual void slot28(void);
	virtual Xfer &xferUnsignedShort(UnsignedInt *value);
	virtual void slot30(void);
	virtual void slot31(void);
	virtual void slot32(void);
	virtual void slot33(void);
	virtual void slot34(void);
	virtual Xfer &xferBool(Bool *value);
};

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException(void);
	char *text;
	int tagValue;
};

struct MissionObjectiveState
{
	Bool m_visible;
	Bool m_completed;
};

typedef _STL::vector<MissionObjectiveState> MissionObjectiveStateVector;

// ?Rva003C2830XferMissionObjectiveStateVector@@YAPAVXfer@@PAV1@PAV?$vector@UMissionObjectiveState@@V?$allocator@UMissionObjectiveState@@@_STL@@@_STL@@@Z
Xfer *Rva003C2830XferMissionObjectiveStateVector(Xfer *xfer, MissionObjectiveStateVector *vector)
{
	UnsignedInt count;
	union VersionStorage
	{
		XferVersion version;
		MissionObjectiveState value;
		unsigned char padding[4];
	} versionStorage;
	versionStorage.version.m_version = 1;
	versionStorage.version.m_currentVersion = 1;
	xfer->xferVersion(&versionStorage.version);

	count = vector->size();
	xfer->xferTypeName("std::vector").xferUnsignedShort(&count);

	if (xfer->isSaving())
	{
		MissionObjectiveState *end = vector->end();
		MissionObjectiveState *current = vector->begin();
		while (current != end)
		{
			xfer->xferBool(&current->m_visible);
			xfer->xferBool(&current->m_completed);
			++current;
		}
	}
	else
	{
		if (!vector->empty())
		{
			throw XferException(4, "Vector must be empty on load");
		}

		vector->reserve(count);

		versionStorage.value.m_visible = true;
		versionStorage.value.m_completed = false;
		while (count != 0)
		{
			--count;
			xfer->xferBool(&versionStorage.value.m_visible);
			xfer->xferBool(&versionStorage.value.m_completed);
			vector->push_back(versionStorage.value);
		}
	}
	return xfer;
}
