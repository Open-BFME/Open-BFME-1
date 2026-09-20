// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib /Ireference/shims/stlp_nodealloc /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad
// stlport
// TunnelTracker::xfer at retail RVA 0x000F8E20.
// The neighboring TunnelTracker bodies prove the three list headers and four
// scalar fields. The retail calls prove the BFME Xfer slots and the two ILT
// helpers used for ObjectID transfer.

#define BFME_STLP_NODE_ALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <list>

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef int Int;
typedef unsigned short UnsignedShort;
typedef bool Bool;
typedef unsigned int ObjectID;

struct XferVersion
{
	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

class Xfer;

class Rva000D7010XferView
{
public:
	virtual ~Rva000D7010XferView(void);
	virtual Bool isLoading(void) const;
	virtual Bool isSaving(void) const;
	virtual void slot03(void);
	virtual Bool isLightCRC(void) const;
	virtual void slot05(void);
	virtual void slot06(void);
	virtual void slot07(void);
	virtual void slot08(void);
	virtual void slot09(void);
	virtual Rva000D7010XferView &xferVersion(XferVersion &version);
	virtual Rva000D7010XferView &xferTypeName(const char *const &name);
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
	virtual Rva000D7010XferView &xferAsciiString(void *value);
	virtual void slot27(void);
	virtual void slot28(void);
	virtual Rva000D7010XferView &xferUnsignedInt(UnsignedInt &value);
	virtual Rva000D7010XferView &xferInt(Int &value);
};

class BfmeSeedTarget;
extern BfmeSeedTarget *bfmeHandOver_0000FFE2(BfmeSeedTarget *target, void *item);
extern void bfmeCalcTGC(void *target, int *item);

struct BfmeObject
{
	unsigned char m_padding[0x74];
	ObjectID m_id;
};

class TunnelTracker
{
protected:
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess(void);

private:
	_STL::list<ObjectID> m_tunnelIDs;
	_STL::list<BfmeObject *> m_containList;
	_STL::list<ObjectID> m_xferContainList;
	Int m_containListSize;
	UnsignedInt m_tunnelCount;
	ObjectID m_curNemesisID;
	UnsignedInt m_nemesisTimestamp;
};

// ?xfer@TunnelTracker@@MAEXPAVXfer@@@Z
void TunnelTracker::xfer(Xfer *xfer)
{
	UnsignedShort i;
	Rva000D7010XferView *receiver = (Rva000D7010XferView *)xfer;
	register TunnelTracker *self = this;
	ObjectID objectID;
	union VersionStorage
	{
		XferVersion version;
		unsigned char padding[4];
	} versionStorage;

	if (!receiver->isLightCRC())
	{
		versionStorage.version.m_version = 1;
		versionStorage.version.m_currentVersion = 1;
		receiver->xferVersion(versionStorage.version);
		bfmeHandOver_0000FFE2((BfmeSeedTarget *)xfer, &self->m_tunnelIDs);
		receiver->xferInt(self->m_containListSize);

		if (receiver->isSaving())
		{
			_STL::list<BfmeObject *>::const_iterator it = self->m_containList.begin();
			while (it != self->m_containList.end())
			{
				objectID = (*it)->m_id;
				bfmeCalcTGC(xfer, (int *)&objectID);
				++it;
			}
		}
		else
		{
			for (i = 0; i < self->m_containListSize; ++i)
			{
				bfmeCalcTGC(xfer, (int *)&objectID);
				self->m_xferContainList.push_back(objectID);
			}
		}

		receiver->xferUnsignedInt(self->m_tunnelCount);
		bfmeCalcTGC(xfer, (int *)&self->m_curNemesisID);
		receiver->xferUnsignedInt(self->m_nemesisTimestamp);
	}
}
