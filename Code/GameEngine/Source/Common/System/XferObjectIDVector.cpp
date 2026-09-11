// cl: /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /MD /EHsc /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad
// stlport
//
// The retail body at 0x00372670 has the same ObjectID-vector serialization
// semantics as upstream Xfer::xferSTLObjectIDVector. Retail exposes a distinct
// free cdecl two-pointer helper, however, and no named caller recovers its
// authentic source spelling. The RVA-qualified symbol is deliberately neutral.

#define BFME_STLP_NODE_ALLOC
#include <vector>

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

class Xfer;

class Rva00372670XferView
{
public:
	virtual ~Rva00372670XferView(void);
	virtual Bool isLoading(void);
	virtual Bool isSaving(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual void slot07(void);
	virtual void slot08(void);
	virtual void slot09(void);
	virtual Rva00372670XferView &xferVersion(XferVersion &version);
	virtual Rva00372670XferView &xferTypeName(const char *const &name);
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
	virtual void slot26(void);
	virtual void slot27(void);
	virtual void slot28(void);
	virtual Rva00372670XferView &xferUnsignedInt(UnsignedInt &value);
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

extern void friend_xferObjectID(Xfer *xfer, ObjectID *objectID);

typedef _STL::vector<ObjectID> ObjectIDVector;

// ?Rva00372670XferObjectIDVector@@YAPAVXfer@@PAV1@PAV?$vector@W4ObjectID@@V?$allocator@W4ObjectID@@@_STL@@@_STL@@@Z
Xfer *__cdecl Rva00372670XferObjectIDVector(Xfer *xfer, ObjectIDVector *vector)
{
	Rva00372670XferView *receiver = reinterpret_cast<Rva00372670XferView *>(xfer);
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
		ObjectID *end = vector->end();
		ObjectID *current = vector->begin();
		while (current != end)
		{
			friend_xferObjectID(xfer, current);
			++current;
		}
	}
	else
	{
		if (!vector->empty())
			throw XferException(4, "Vector must be empty on load");

		vector->reserve(count);
		while (count != 0)
		{
			--count;
			ObjectID value;
			friend_xferObjectID(xfer, &value);
			vector->push_back(value);
		}
	}
	return xfer;
}
