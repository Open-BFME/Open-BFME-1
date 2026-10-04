// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/stringinline
// stlport
// Waypoint::xfer, retail 0x001A7020 size 648.

#include "StringInline.h"

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef int Int;
typedef bool Bool;
typedef float Real;

struct XferVersion
{
	UnsignedByte version;
	UnsignedByte currentVersion;
	UnsignedByte pad[2];
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Xfer
{
public:
	virtual void slot00();
	virtual Bool isLoading();
	virtual Bool isStoring();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void xferUser(void *data, Int size);
	virtual void xferVersion(XferVersion *version);
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void xferCoord3D(Coord3D *value);
	virtual void slot64();
	virtual void xferAsciiString(AsciiString *value);
	virtual void slot6C();
	virtual void slot70();
	virtual void xferUnsignedInt(UnsignedInt *value);
	virtual void xferInt(Int *value);
	virtual void slot7C();
	virtual void slot80();
	virtual void slot84();
	virtual void slot88();
	virtual void xferBool(Bool *value);
};

class Xfer; class MidVirtualSlot90Receiver;
void Rva0010BE80(MidVirtualSlot90Receiver *receiver, void *context);
Xfer & Rva0010C3C0(MidVirtualSlot90Receiver *receiver, void *context);
// retail defines 0x012ACC30 as the static member Rva001A1A30::s_value
// (see TinyGlobalStores.cpp), not as a free global.
class Rva001A1A30
{
public:
	static int s_value;
};

class BfmeSeedTarget;
class Rva000D6CF0Field
{
public:

	UnsignedInt m_values[6];
};

// Retail reaches the 0x000D6CF0 body through ILT 0x0003573D.
extern void j_0003573d();
class Route0003573D {};
static __forceinline void callRva000D6CF0(void *self, BfmeSeedTarget *target)
{
	typedef void (Route0003573D::*Fn)(BfmeSeedTarget *);
	union { void (*fn)(); Fn call; } route = { j_0003573d };
	(((Route0003573D *)self)->*route.call)(target);
}

enum { INVALID_WAYPOINT_ID = 0x7fffffff };

class Waypoint
{
public:
	void xfer(Xfer *xfer);
	// ?getID@Waypoint@@QBEHXZ absent-from-retail
	Int getID() const { return m_id; }

	char m_vtable[4];
	Int m_id;
	AsciiString m_name;
	Coord3D m_location;
	char m_pad18[4];
	Waypoint *m_next;
	Waypoint *m_links[8];
	Waypoint *m_linkSource;
	Waypoint *m_field44;
	Bool m_field48;
	Int m_numLinks;
	AsciiString m_pathLabel1;
	AsciiString m_pathLabel2;
	AsciiString m_pathLabel3;
	Bool m_biDirectional;
	UnsignedInt m_field60;
	AsciiString m_field64;
	Bool m_field68;
	Rva000D6CF0Field m_field6c;
	Bool m_field84;
	Rva000D6CF0Field m_field88;
	Bool m_fielda0;
	char m_padA1[7];
	UnsignedInt m_fielda8;
	UnsignedInt m_fieldac;
};

void Waypoint::xfer(Xfer *xfer)
{
	XferVersion version;
	version.version = 1;
	version.currentVersion = 3;
	xfer->xferVersion(&version);

	Rva0010BE80((MidVirtualSlot90Receiver *)xfer, &m_id);
	xfer->xferAsciiString(&m_name);
	xfer->xferCoord3D(&m_location);
	if (version.currentVersion >= 2)
		Rva0010BE80((MidVirtualSlot90Receiver *)xfer, &Rva001A1A30::s_value);

	if (xfer->isLoading())
	{
		Int count;
		Int id;
		xfer->xferInt(&count);
		Int i = 0;
		while (i < count)
		{
			Rva0010BE80((MidVirtualSlot90Receiver *)xfer, &id);
			if (i < 8)
				m_links[i] = (Waypoint *)id;
			++i;
		}
		if (i < 8)
		{
			while (i < 8)
				m_links[i++] = (Waypoint *)INVALID_WAYPOINT_ID;
		}

		Rva0010BE80((MidVirtualSlot90Receiver *)xfer, &id);
		m_field44 = (Waypoint *)id;
		if (version.currentVersion >= 2)
		{
			Rva0010BE80((MidVirtualSlot90Receiver *)xfer, &id);
			m_linkSource = (Waypoint *)id;
		}
		else
			m_linkSource = (Waypoint *)INVALID_WAYPOINT_ID;
	}
	else if (xfer->isStoring())
	{
		Int i = 8;
		xfer->xferInt(&i);
		i = 0;
		Int id;
		while (i < 8)
		{
			Waypoint *link = m_links[i];
			if (link != 0)
				id = link->m_id;
			else
				id = INVALID_WAYPOINT_ID;
			Rva0010BE80((MidVirtualSlot90Receiver *)xfer, &id);
			++i;
		}

		if (m_field44 != 0)
			id = m_field44->m_id;
		else
			id = INVALID_WAYPOINT_ID;
		Rva0010BE80((MidVirtualSlot90Receiver *)xfer, &id);
		if (version.currentVersion >= 2)
		{
			id = m_linkSource != 0 ? m_linkSource->getID() : INVALID_WAYPOINT_ID;
			Rva0010BE80((MidVirtualSlot90Receiver *)xfer, &id);
		}
	}

	xfer->xferBool(&m_field48);
	xfer->xferInt(&m_numLinks);
	xfer->xferAsciiString(&m_pathLabel1);
	xfer->xferAsciiString(&m_pathLabel2);
	xfer->xferAsciiString(&m_pathLabel3);
	xfer->xferBool(&m_biDirectional);
	xfer->xferUser(&m_field60, 4);
	xfer->xferAsciiString(&m_field64);
	xfer->xferBool(&m_field68);
	xfer->xferBool(&m_field84);
	xfer->xferBool(&m_fielda0);
	Rva0010C3C0((MidVirtualSlot90Receiver *)xfer, &m_fielda8);
	callRva000D6CF0(&m_field6c, (BfmeSeedTarget *)xfer);
	callRva000D6CF0(&m_field88, (BfmeSeedTarget *)xfer);
	if (version.currentVersion >= 3)
		xfer->xferUnsignedInt(&m_fieldac);
}
