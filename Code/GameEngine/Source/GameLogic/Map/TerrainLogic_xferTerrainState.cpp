// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc /Ireference/shims/stringinline
// stlport
// TerrainLogic::xferTerrainState, retail 0x001AD370 size 1515.
// Reached from the xfer row at 0x006BE430 through ILT 0x00043ED7 (the pinned
// xferTerrainState tail call).  The body opens with the Zero Hour
// TerrainLogic::xfer water-update transfer (setActiveBoundary through ILT
// 0x0001E29A, the polygon-trigger lookup and getWaterHandle) and then carries
// the BFME terrain state: the 0xB0-byte cell nodes on the global list at
// 0x012EF4D0, the int map at +0x550, the 48-byte record vector at +0x55C and
// the 2500 16-bit words at +0x568.

#include <map>
#include <vector>

#include "StringInline.h"

typedef unsigned char UnsignedByte;
typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

struct XferVersion
{
	UnsignedByte version;
	UnsignedByte currentVersion;
	UnsignedByte pad[2];
};

struct BfmeFormattedText
{
	char *m_text;
	int m_tag;
};

extern "C" BfmeFormattedText *__cdecl bfmeFormatText(BfmeFormattedText *, int, const char *, ...);
extern __declspec(noreturn) void __stdcall _CxxThrowException(void *, void *);

class Xfer
{
public:
	virtual void slot00();
	virtual Bool isLoading() const;
	virtual Bool isStoring() const;
	virtual void slot03();
	virtual Bool isLightCRC() const;
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void xferUser(void *data, UnsignedInt size);
	virtual void xferVersion(XferVersion *version);
	virtual void slot11();
	virtual void xferSnapshot(void *snapshot);
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
	virtual void xferAsciiString(void *value);
	virtual void xferReal(Real *value);
	virtual void slot28();
	virtual void xferUnsignedInt(UnsignedInt *value);
	virtual void xferInt(Int *value);
	virtual void xferUnsignedShort(unsigned short *value);
	virtual void slot32(short *value);
	virtual void slot33();
	virtual void slot34();
	virtual void xferBool(Bool *value);
};

extern "C" void __cdecl bfmeXferIntAX(Xfer *xfer, Int *value);
extern int g_Va012ACC30;

class PolygonTrigger;

class WaterHandle
{
public:
	PolygonTrigger *m_polygon;
};

class PolygonTrigger
{
public:
	const WaterHandle *getWaterHandle() const;

	char m_pad00[0x0c];
	Int m_triggerID;
};

class BfmeEntryCN;
BfmeEntryCN *bfmeLookup(void *id);

struct WaterToUpdate
{
	const WaterHandle *waterTable;
	Real changePerFrame;
	Real targetHeight;
	Real damageAmount;
	Real currentHeight;
};

struct Rva001AB600Arg
{
	int m_values[3];
};

class Rva001A1E20CellState
{
public:
	void reset(void);
};

class Rva001A2D50Node
{
public:
	// ILT 0x0001ADB1 -> body 0x001AB600 (ret 0x24), called on the operator new
	// result under the new-expression EH state
	Rva001A2D50Node(Int cell, AsciiString a, const Rva001AB600Arg &b, AsciiString c,
		AsciiString d, AsciiString e, Bool f, Int g, AsciiString h);
	void Rva001A7020(Xfer *xfer);	///< ILT 0x00016A3B -> body 0x001A7020

	char m_pad00[0x1c];
	Rva001A2D50Node *m_next;
	char m_pad20[0xb0 - 0x20];
};

extern Rva001A2D50Node *g_rva012EF4D0;

struct Gen_t_001a6d20_p4pod
{
	int m_value;
};

struct Rva001AD370Triple
{
	Rva001AD370Triple() {}
	Rva001AD370Triple(const Rva001AD370Triple &other)
		: x(other.x), y(other.y), z(other.z)
	{
	}
	int x;
	int y;
	int z;
};

struct Gen_t_001ac070_p48cd
{
	Gen_t_001ac070_p48cd()
		: m_c(0), m_d(0), m_e(0), m_flag18(false), m_int28(1),
		  m_flag2c(true), m_flag2d(true), m_short2e(-1)
	{
		m_a = 0;
		m_b = 0;
		m_f = 0;
	}
	void Rva001A78B0(Xfer *xfer);	///< ILT 0x00033FFA -> body 0x001A78B0

	Real m_a;
	Real m_b;
	Real m_f;
	int m_c;
	int m_d;
	int m_e;
	Bool m_flag18;
	Rva001AD370Triple m_1c;
	int m_int28;
	Bool m_flag2c;
	Bool m_flag2d;
	short m_short2e;
};

class TerrainLogic
{
public:
	void setActiveBoundary(Int newActiveBoundary);

protected:
	void xferTerrainState(Xfer *xfer);

	char m_pad00[0x30];
	Int m_activeBoundary;
	char m_pad34[0x38 - 0x34];
	Bool m_bridgeDamageStatesChanged;
	char m_pad39[0x3c - 0x39];
	UnsignedInt m_value3c;
	char m_pad40[0x44 - 0x40];
	Bool m_flag44;
	char m_pad45[0x4c - 0x45];
	WaterToUpdate m_waterToUpdate[64];
	UnsignedInt m_numWaterToUpdate;
	std::map<Int, Gen_t_001a6d20_p4pod> m_map550;
	std::vector<Gen_t_001ac070_p48cd> m_records;
	short m_words[2500];
	UnsignedInt m_value18f0;
	Bool m_flag18f4;
};

void TerrainLogic::xferTerrainState(Xfer *xfer)
{
	if (xfer->isLightCRC())
		return;

	XferVersion version;
	version.version = 1;
	version.currentVersion = 2;
	xfer->xferVersion(&version);

	xfer->xferBool(&m_bridgeDamageStatesChanged);
	xfer->xferBool(&m_flag44);

	Int activeBoundary = m_activeBoundary;
	xfer->xferInt(&activeBoundary);
	if (xfer->isLoading())
		setActiveBoundary(activeBoundary);

	xfer->xferInt((Int *)&m_numWaterToUpdate);
	for (UnsignedInt i = 0; i < m_numWaterToUpdate; ++i)
	{
		if (xfer->isStoring())
		{
			Int triggerID = m_waterToUpdate[i].waterTable->m_polygon->m_triggerID;
			xfer->xferInt(&triggerID);
		}
		else
		{
			Int triggerID;
			xfer->xferInt(&triggerID);
			PolygonTrigger *poly = (PolygonTrigger *)bfmeLookup((void *)triggerID);
			if (poly == 0)
			{
				BfmeFormattedText error;
				bfmeFormatText(&error, 5, 0);
				_CxxThrowException(&error, (void *)0x011DFE5C);
			}
			m_waterToUpdate[i].waterTable = poly->getWaterHandle();
			if (m_waterToUpdate[i].waterTable == 0)
			{
				BfmeFormattedText error;
				bfmeFormatText(&error, 5, 0);
				_CxxThrowException(&error, (void *)0x011DFE5C);
			}
		}
		xfer->xferReal(&m_waterToUpdate[i].changePerFrame);
		xfer->xferReal(&m_waterToUpdate[i].targetHeight);
		xfer->xferReal(&m_waterToUpdate[i].damageAmount);
		xfer->xferReal(&m_waterToUpdate[i].currentHeight);
	}

	Int globalValue = g_Va012ACC30;
	bfmeXferIntAX(xfer, &globalValue);
	g_Va012ACC30 = globalValue;

	if (xfer->isLoading())
	{
		Bool more;
		xfer->xferBool(&more);
		if (more)
		{
			do
			{
				Rva001AB600Arg arg;
				Rva001A2D50Node *node = new Rva001A2D50Node(0x7fffffff, AsciiString::TheEmptyString,
					arg, AsciiString::TheEmptyString, AsciiString::TheEmptyString,
					AsciiString::TheEmptyString, false, 0, AsciiString::TheEmptyString);
				node->Rva001A7020(xfer);
				xfer->xferBool(&more);
			} while (more);
		}
		for (Rva001A2D50Node *node = g_rva012EF4D0; node; node = node->m_next)
			((Rva001A1E20CellState *)node)->reset();
		m_map550.clear();
	}
	else
	{
		Bool more = true;
		for (Rva001A2D50Node *node = g_rva012EF4D0; node; node = node->m_next)
		{
			xfer->xferBool(&more);
			node->Rva001A7020(xfer);
		}
		more = false;
		xfer->xferBool(&more);
	}

	Int count = m_records.size();
	xfer->xferInt(&count);
	if (xfer->isLoading())
	{
		m_records.clear();
		m_records.reserve(count);
		Gen_t_001ac070_p48cd record;
		for (Int i = 0; i < count; ++i)
			m_records.push_back(record);
	}
	for (Int j = 0; j < count; ++j)
		m_records[j].Rva001A78B0(xfer);

	for (Int k = 0; k < 2500; ++k)
		xfer->slot32(&m_words[k]);
	xfer->xferUnsignedInt(&m_value18f0);
	xfer->xferBool(&m_flag18f4);
	if (version.currentVersion >= 2)
		xfer->xferUnsignedInt(&m_value3c);
}
