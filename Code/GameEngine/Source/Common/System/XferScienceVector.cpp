// cl: /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /MD /EHsc /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad
// stlport

#define BFME_STLP_NODE_ALLOC
#include <vector>

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum ScienceType
{
	SCIENCE_INVALID = -1
};

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

class AsciiString;

class Rva000D7010XferView
{
public:
	virtual ~Rva000D7010XferView(void);
	virtual Bool isLoading(void) const;                        // +04, raw predicate
	virtual Bool isSaving(void) const;                         // +08, raw save predicate
	virtual void slot03(void);                           // +0C
	virtual void slot04(void);                           // +10
	virtual void slot05(void);                           // +14
	virtual void slot06(void);                           // +18
	virtual void slot07(void);                           // +1C
	virtual void slot08(void);                           // +20
	virtual void slot09(void);                           // +24
	virtual Rva000D7010XferView &xferVersion(XferVersion &version); // +28, operator==(Version&)
	virtual Rva000D7010XferView &xferTypeName(const char *const &name); // +2C
	virtual void slot12(void);                           // +30
	virtual void slot13(void);                           // +34
	virtual void slot14(void);                           // +38
	virtual void slot15(void);                           // +3C
	virtual void slot16(void);                           // +40
	virtual void slot17(void);                           // +44
	virtual void slot18(void);                           // +48
	virtual void slot19(void);                           // +4C
	virtual void slot20(void);                           // +50
	virtual void slot21(void);                           // +54
	virtual void slot22(void);                           // +58
	virtual void slot23(void);                           // +5C
	virtual void slot24(void);                           // +60
	virtual void slot25(void);                           // +64
	virtual Rva000D7010XferView &xferAsciiString(AsciiString &value); // +68, operator==(AsciiString&)
	virtual void slot27(void);                           // +6C
	virtual void slot28(void);                           // +70
	virtual Rva000D7010XferView &xferUnsignedInt(UnsignedInt &value); // +74, operator==(unsigned int&)
};
class Xfer;

// The ThrowInfo at VA 0x011DFE5C has TypeDescriptor ".?AVXferException@@"
// and an 8-byte catchable object.  Its copy and destructor are nontrivial.
// The natural variadic constructor is declared here and pinned to the proven
// retail constructor/formatter body at 0x009D6220 during integration.  No
// local wrapper or formatter adapter is emitted in this TU.
class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException(void);
	char *text;
	int tagValue;
};

typedef _STL::vector<ScienceType> ScienceVec;

// Raw 0x0010C5E0 returns its Xfer* (EAX=ESI) on both save/load exits.
Xfer *__cdecl Rva0010C5E0XferScience(Xfer *xfer, ScienceType *science);

// Retail 0x000D7010, full raw extent 294 bytes [0x000D7010,0x000D7136).
Xfer *__cdecl Rva000D7010XferScienceVector(Xfer *xfer, ScienceVec *vector)
{
	Rva000D7010XferView *receiver = reinterpret_cast<Rva000D7010XferView *>(xfer);
	union VersionStorage
	{
		XferVersion version;
		unsigned char padding[4];
	} versionStorage;
	UnsignedInt count;
	versionStorage.version.m_version = 1;
	versionStorage.version.m_currentVersion = 1;
	receiver->xferVersion(versionStorage.version);

	count = vector->size();
	receiver->xferTypeName("std::vector").xferUnsignedInt(count);

	if (receiver->isSaving())
	{
		ScienceType *end = vector->end();
		ScienceType *current = vector->begin();
		while (current != end)
		{
			Rva0010C5E0XferScience(xfer, current);
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
		while (count != 0)
		{
			ScienceType value;
			--count;
			Rva0010C5E0XferScience(xfer, &value);
			vector->push_back(value);
		}
	}
	return xfer;
}
