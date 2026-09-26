// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// BFME retail RVA 0x000EAE70: ScoreKeeper snapshot transfer.

#include <map>

typedef int Int;
typedef bool Bool;
typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;
typedef unsigned int UnsignedInt;

struct XferVersion
{
	XferVersion(UnsignedByte version, UnsignedByte currentVersion) :
		m_version(version), m_currentVersion(currentVersion)
	{
	}

	UnsignedByte m_version;
	UnsignedByte m_currentVersion;
};

class Xfer
{
public:
	virtual void slot00();
	virtual Bool IsLoading() const;
	virtual Bool IsStoring() const;
	virtual Bool IsCRC() const;
	virtual Bool IsLightCRC() const;
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void xferVersion(XferVersion *version);
	virtual void slot11();
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
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void xferUnsignedInt(UnsignedInt *value);
	virtual void xferInt(Int *value);
	virtual void xferUnsignedShort(UnsignedShort *value);
};

class ThingTemplate;
typedef _STL::map<const ThingTemplate *, Int> ObjectCountMap;

struct XferException
{
	char *text;
	Int tag;
};

extern "C" XferException *__cdecl bfmeFormatText(
	XferException *result, Int tag, const char *format, ...);
extern void __declspec(noreturn) __stdcall _CxxThrowException(
	void *object, void *throwInfo);

class Snapshot
{
public:
	virtual ~Snapshot() {}
	virtual void crc(Xfer *xfer) = 0;
	virtual void xfer(Xfer *xfer) = 0;
	virtual void loadPostProcess() = 0;
};

class ScoreKeeper : public Snapshot
{
public:
	void xferObjectCountMap(Xfer *xfer, ObjectCountMap *map);

protected:
	virtual void xfer(Xfer *xfer);

private:
	Int m_totalMoneyEarned;
	Int m_totalMoneySpent;
	Int m_totalUnitsDestroyed[32];
	Int m_totalUnitsBuilt;
	Int m_totalUnitsLost;
	Int m_totalBuildingsDestroyed[32];
	Int m_totalBuildingsBuilt;
	Int m_totalBuildingsLost;
	Int m_heroesVetted;
	Int m_unitsVetted;
	Int m_powerPoints;
	Int m_pad128;
	Int m_regionCommandPoints;
	Int m_regionResources;
	Int m_regionPowerPoints;
	Int m_currentScore;
	UnsignedInt m_frameOverride;
	Int m_myPlayerIdx;
	ObjectCountMap m_objectsBuilt;
	ObjectCountMap m_objectsDestroyed[32];
	ObjectCountMap m_objectsLost;
	ObjectCountMap m_objectsCaptured;
};

// ?xfer@ScoreKeeper@@MAEXPAVXfer@@@Z
void ScoreKeeper::xfer(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;

	XferVersion version(1, 4);
	xfer->xferVersion(&version);

	xfer->xferInt(&m_totalMoneyEarned);
	xfer->xferInt(&m_totalMoneySpent);

	for (Int i = 0; i < 32; ++i)
	{
		xfer->xferInt(&m_totalUnitsDestroyed[i]);
		xfer->xferInt(&m_totalBuildingsDestroyed[i]);
	}

	xfer->xferInt(&m_totalUnitsBuilt);
	xfer->xferInt(&m_totalUnitsLost);
	xfer->xferInt(&m_totalBuildingsBuilt);
	xfer->xferInt(&m_totalBuildingsLost);
	xfer->xferInt(&m_pad128);
	xfer->xferInt(&m_currentScore);
	xfer->xferInt(&m_myPlayerIdx);

	if (version.m_currentVersion >= 2)
	{
		Int legacyPowerPoints = 0;
		xfer->xferInt(&m_heroesVetted);
		xfer->xferInt(&m_unitsVetted);
		xfer->xferInt(&legacyPowerPoints);
		xfer->xferInt(&m_powerPoints);
	}

	if (version.m_currentVersion >= 3)
	{
		xfer->xferInt(&m_regionCommandPoints);
		xfer->xferInt(&m_regionResources);
		xfer->xferInt(&m_regionPowerPoints);
	}

	if (version.m_currentVersion >= 4)
		xfer->xferUnsignedInt(&m_frameOverride);

	if (xfer->IsCRC())
		return;

	xferObjectCountMap(xfer, &m_objectsBuilt);

	UnsignedShort destroyedArraySize = 32;
	xfer->xferUnsignedShort(&destroyedArraySize);
	if (destroyedArraySize != 32)
	{
		XferException error;
		bfmeFormatText(&error, 5, 0);
		_CxxThrowException(&error, (void *)0x011DFE5C);
	}

	for (UnsignedShort i = 0; i < destroyedArraySize; ++i)
		xferObjectCountMap(xfer, &m_objectsDestroyed[i]);

	xferObjectCountMap(xfer, &m_objectsLost);
	xferObjectCountMap(xfer, &m_objectsCaptured);
}
