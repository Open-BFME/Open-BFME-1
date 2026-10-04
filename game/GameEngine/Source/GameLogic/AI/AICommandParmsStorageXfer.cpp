// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// AICommandParmsStorage::doXfer, retail 0x00187860 (805 bytes, ret 4).
// Zero Hour AIStates.cpp doXfer line for line on the BFME storage layout that
// the matched store/reconstitute pair (AICommandParmsStorage.cpp, 0x001805B0 /
// 0x00180710) establishes: BFME adds a version block, a second team string at
// +0x20, and transfers the two enums through the typed slot-0x90 helpers.
// Callers reach it through ILT 0x00002DEC (pinned for the matched version-
// block seeders as BfmeSubAccept_00002DEC::bfmeAccept); it transfers the
// storage embedded at +0x340 / +0x34C of those AI update objects.

#include <vector>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x;
	Real y;
	Real z;

	void set(const Coord3D *other)
	{
		x = other->x;
		y = other->y;
		z = other->z;
	}
};

enum ObjectID
{
	INVALID_ID = 0
};

template <typename T> struct StringBaseData
{
	Int m_refCount;
	unsigned short m_length;
	unsigned short m_capacity;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;

public:
	void set(const StringBase<T> &other);

private:
	StringBase(void) : m_data(0) {}
	StringBase(const StringBase<T> &other);
	~StringBase(void) { releaseBuffer(); }
	void releaseBuffer(void);

	StringBaseData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(void) : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString(void) {}
	AsciiString &operator=(const AsciiString &other)
	{
		StringBase<char>::set(other);
		return *this;
	}
	Bool isNotEmpty(void) const { return m_data != 0 && m_data->m_length != 0; }
};

// BFME's version block: the first byte is the version read back, the second
// the writer's current version (see S3VersionBlocks.cpp). Retail packs it
// onto the same frame slot as the coordinate-loop counter and the two
// compiler temporaries, above the four-byte locals; a two-byte object sorts
// below them instead, so the frame witnesses a four-byte object here.
struct XferVersionBlock
{
	unsigned char m_version;
	unsigned char m_currentVersion;
	unsigned short m_unmodelled02;
};

class Xfer;

class Snapshot
{
public:
	virtual void xfer(Xfer *xfer) = 0;
};

class Xfer
{
public:
	virtual void slot00(void);
	virtual Bool isLoading(void);
	virtual void slot02(void);
	virtual void slot03(void);
	virtual void slot04(void);
	virtual void slot05(void);
	virtual void slot06(void);
	virtual void slot07(void);
	virtual void slot08(void);
	virtual void slot09(void);
	virtual void xferVersion(XferVersionBlock *version);
	virtual void slot11(void);
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
	virtual void xferCoord3D(Coord3D *coord);
	virtual void slot25(void);
	virtual void xferAsciiString(AsciiString *string);
	virtual void slot27(void);
	virtual void slot28(void);
	virtual void xferUnsignedInt(UnsignedInt *value);
	virtual void xferInt(Int *value);
	virtual void slot31(void);
	virtual void slot32(void);
	virtual void slot33(void);
	virtual void slot34(void);
	virtual void xferBool(Bool *value);

	void xferSnapshot(Snapshot *snapshot) { snapshot->xfer(this); }
};

class MidVirtualSlot90Receiver;
// Typed enum transfers (the 25-byte slot-0x90 forwarders).
void Rva0010C020(MidVirtualSlot90Receiver *receiver, void *context);
void Rva0010BE00(MidVirtualSlot90Receiver *receiver, void *context);
class Xfer; class MidVirtualSlot90Receiver; Xfer &Rva0010C3C0(MidVirtualSlot90Receiver *receiver, void *value);

class Waypoint
{
public:
	UnsignedInt getID(void) const { return m_id; }

private:
	void *m_vtable;
	UnsignedInt m_id;
};

class PolygonTrigger
{
public:
	const AsciiString &getTriggerName(void) const { return m_triggerName; }

private:
	unsigned char m_unmodelled00[8];
	AsciiString m_triggerName;
};

class CommandButton
{
public:
	const AsciiString &getName(void) const { return m_name; }

private:
	unsigned char m_unmodelled00[0xC];
	AsciiString m_name;
};

class Path
{
public:
	Path(void);
	void xfer00401C70(Xfer *xfer);

private:
	unsigned char m_storage[0x24];
};

class TerrainLogic
{
public:
	virtual void slot00(void); virtual void slot01(void); virtual void slot02(void); virtual void slot03(void);
	virtual void slot04(void); virtual void slot05(void); virtual void slot06(void); virtual void slot07(void);
	virtual void slot08(void); virtual void slot09(void); virtual void slot10(void); virtual void slot11(void);
	virtual void slot12(void); virtual void slot13(void); virtual void slot14(void); virtual void slot15(void);
	virtual void slot16(void); virtual void slot17(void); virtual void slot18(void); virtual void slot19(void);
	virtual void slot20(void); virtual void slot21(void); virtual void slot22(void); virtual void slot23(void);
	virtual void slot24(void); virtual void slot25(void); virtual void slot26(void); virtual void slot27(void);
	virtual void slot28(void); virtual void slot29(void); virtual void slot30(void); virtual void slot31(void);
	virtual Waypoint *getWaypointByID(UnsignedInt id);
	virtual void slot33(void); virtual void slot34(void); virtual void slot35(void);
	virtual PolygonTrigger *getTriggerAreaByName(AsciiString name);
};

extern TerrainLogic *TheTerrainLogic;

class ControlBar
{
public:
	const CommandButton *findCommandButton(const AsciiString &name);
};

extern ControlBar *TheControlBar;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Damage.h
class DamageInfo : public Snapshot
{
public:
	virtual void xfer(Xfer *xfer);

private:
	unsigned char m_in[0x4C];
	Real m_actualDamageDealt;
	Real m_actualDamageClipped;
	Bool m_noEffect;
};

#define INVALID_WAYPOINT_ID 0x7fffffff

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AI.h
class AICommandParmsStorage
{
public:
	void doXfer(Xfer *xfer);

private:
	Int m_cmd;
	Int m_cmdSource;
	Coord3D m_pos;
	ObjectID m_obj;
	ObjectID m_otherObj;
	AsciiString m_teamName;
	AsciiString m_teamOwner;
	_STL::vector<Coord3D> m_coords;
	Waypoint *m_waypoint;
	PolygonTrigger *m_polygon;
	Int m_intValue;
	DamageInfo m_damage;
	const CommandButton *m_commandButton;
	Path *m_path;
};

void AICommandParmsStorage::doXfer(Xfer *xfer)
{
	{
		XferVersionBlock version;
		version.m_version = 1;
		version.m_currentVersion = 1;
		xfer->xferVersion(&version);
	}

	Rva0010C020((MidVirtualSlot90Receiver *)xfer, &m_cmd);
	Rva0010BE00((MidVirtualSlot90Receiver *)xfer, &m_cmdSource);
	xfer->xferCoord3D(&m_pos);
	Rva0010C3C0((MidVirtualSlot90Receiver *)xfer, &m_obj);
	Rva0010C3C0((MidVirtualSlot90Receiver *)xfer, &m_otherObj);
	xfer->xferAsciiString(&m_teamName);
	xfer->xferAsciiString(&m_teamOwner);
	Int numCoords = m_coords.size();
	xfer->xferInt(&numCoords);
	Int i;
	if (xfer->isLoading())
	{
		for (i = 0; i < numCoords; i++)
		{
			Coord3D pos;
			xfer->xferCoord3D(&pos);
			m_coords.push_back(pos);
		}
	}
	else
	{
		for (i = 0; i < numCoords; i++)
		{
			Coord3D pos;
			pos.set(&m_coords[i]);
			xfer->xferCoord3D(&pos);
		}
	}

	UnsignedInt id = INVALID_WAYPOINT_ID;
	if (m_waypoint)
		id = m_waypoint->getID();
	xfer->xferUnsignedInt(&id);
	if (xfer->isLoading() && id != INVALID_WAYPOINT_ID)
		m_waypoint = TheTerrainLogic->getWaypointByID(id);

	AsciiString triggerName;
	if (m_polygon)
		triggerName = m_polygon->getTriggerName();
	xfer->xferAsciiString(&triggerName);
	if (xfer->isLoading())
	{
		if (triggerName.isNotEmpty())
			m_polygon = TheTerrainLogic->getTriggerAreaByName(triggerName);
	}

	xfer->xferInt(&m_intValue);

	xfer->xferSnapshot(&m_damage);

	AsciiString cmdName;
	if (m_commandButton)
		cmdName = m_commandButton->getName();
	xfer->xferAsciiString(&cmdName);
	if (cmdName.isNotEmpty() && m_commandButton == 0)
		m_commandButton = TheControlBar->findCommandButton(cmdName);

	Bool hasPath = m_path != 0;
	xfer->xferBool(&hasPath);
	if (hasPath && m_path == 0)
		m_path = new Path;
	if (hasPath)
		m_path->xfer00401C70(xfer);
}
