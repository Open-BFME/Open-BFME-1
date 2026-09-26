// ?xfer@LivingWorldPlayerArmy@@UAEXPAVXfer@@@Z
// The field order and offsets match INILivingWorldPlayerArmy.cpp.  The army
// vector stores the 0xB4-byte BfmeOwnVUM record established by its ctor, copy
// ctor, destructor, and save body.

// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#include <vector>

typedef unsigned char Bool;
typedef unsigned int UnsignedInt;
typedef int Int;

#include "ascii_string.h"

struct Coord2DBase
{
	Int x;
	Int y;
};

struct XferCharSlot;
struct XferUnsignedCharSlot;
struct XferShortSlot;
struct XferUnsignedShortSlot;
struct XferInt64Slot;
struct XferFloatSlot;
struct XferUnicodeSlot;
struct XferCoord3Slot;
struct XferICoord3Slot;
struct XferRegion3Slot;
struct XferIRegion3Slot;
struct XferICoord2Slot;
struct XferRegion2Slot;
struct XferIRegion2Slot;
struct XferRealRangeSlot;
struct XferRGBSlot;
struct XferRGBRealSlot;
struct XferRGBIntSlot;
struct XferSnapshotSlot;
struct XferReservedSlot;

class Xfer
{
public:
	class Version
	{
	public:
		unsigned char data[2];
	};

	virtual ~Xfer();
	virtual Bool IsLoading() const;
	virtual Bool IsStoring() const;
	virtual Bool IsCRC() const;
	virtual Bool IsLightCRC() const;
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual Xfer &slot09(void *, UnsignedInt);
	virtual Xfer &operator == (Bool &value);
	virtual Xfer &operator == (XferCharSlot &value);
	virtual Xfer &operator == (XferUnsignedCharSlot &value);
	virtual Xfer &operator == (XferShortSlot &value);
	virtual Xfer &operator == (XferUnsignedShortSlot &value);
	virtual Xfer &operator == (Int &value);
	virtual Xfer &operator == (UnsignedInt &value);
	virtual Xfer &operator == (XferInt64Slot &value);
	virtual Xfer &operator == (XferFloatSlot &value);
	virtual Xfer &operator == (AsciiString &value);
	virtual Xfer &operator == (XferUnicodeSlot &value);
	virtual Xfer &operator == (XferCoord3Slot &value);
	virtual Xfer &operator == (XferICoord3Slot &value);
	virtual Xfer &operator == (XferRegion3Slot &value);
	virtual Xfer &operator == (XferIRegion3Slot &value);
	virtual Xfer &operator == (Coord2DBase &value);
	virtual Xfer &operator == (XferICoord2Slot &value);
	virtual Xfer &operator == (XferRegion2Slot &value);
	virtual Xfer &operator == (XferIRegion2Slot &value);
	virtual Xfer &operator == (XferRealRangeSlot &value);
	virtual Xfer &operator == (XferRGBSlot &value);
	virtual Xfer &operator == (XferRGBRealSlot &value);
	virtual Xfer &operator == (XferRGBIntSlot &value);
	virtual Xfer &operator == (XferSnapshotSlot &value);
	virtual Xfer &operator == (XferReservedSlot &value);
	virtual Xfer &operator == (Version &version);
	virtual Xfer &XferEnum(const char *name, void *data, UnsignedInt size);
};

class BfmeAgentBH;

class BfmeOwnVUM
{
public:
	BfmeOwnVUM();
	BfmeOwnVUM(const BfmeOwnVUM &other);
	~BfmeOwnVUM();
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	void bfmeSaveBH(BfmeAgentBH *xfer);

private:
	char m_fields[0xB0];
};

class LivingWorldPlayerArmy
{
public:
	virtual void crc(Xfer *xfer);

	public:
	virtual void xfer(Xfer *xfer);

public:
	virtual void loadPostProcess();

	Int m_index;
	Bool m_isActive;
	unsigned char m_padding09[3];
	AsciiString m_name;
	AsciiString m_faction;
	AsciiString m_icon;
	Int m_color;
	Int m_nightColor;
	Int m_startingCommandPoints;
	Int m_unmodelled24;
	Int m_unmodelled28;
	Int m_unmodelled2C;
	std::vector<BfmeOwnVUM> m_armies;
	Coord2DBase m_unmodelled3C;
	Int m_survivalThreshold;
	AsciiString m_displayNameTag;
	Bool m_unmodelled4C;
	Int m_minCommandPoints;
	AsciiString m_replenishArmyName;
};

void LivingWorldPlayerArmy::xfer(Xfer *xfer)
{
	union VersionAndCount
	{
		Xfer::Version version;
		Int count;
	} versionAndCount;
	versionAndCount.version.data[0] = 1;
	versionAndCount.version.data[1] = 1;
	*xfer == versionAndCount.version;
	*xfer == m_index;
	*xfer == m_isActive;
	*xfer == m_name;
	*xfer == m_faction;
	*xfer == m_icon;
	*xfer == m_color;
	*xfer == m_nightColor;
	*xfer == m_unmodelled24;
	*xfer == m_unmodelled28;
	*xfer == m_unmodelled2C;
	xfer->XferEnum("ReinforcementState", &m_startingCommandPoints, sizeof(m_startingCommandPoints));
	*xfer == m_survivalThreshold;
	*xfer == m_unmodelled4C;
	*xfer == m_displayNameTag;
	*xfer == m_minCommandPoints;
	*xfer == m_replenishArmyName;
	xfer->operator == (m_unmodelled3C);

	if (xfer->IsLoading())
	{
		*xfer == versionAndCount.count;
		for (Int i = 0; i < versionAndCount.count; ++i)
		{
			BfmeOwnVUM army;
			army.bfmeSaveBH((BfmeAgentBH *)xfer);
			m_armies.push_back(army);
		}
	}
	else
	{
		Int count = (Int)m_armies.size();
		*xfer == count;
		for (Int i = 0; i < count; ++i)
			m_armies[i].bfmeSaveBH((BfmeAgentBH *)xfer);
	}
}
