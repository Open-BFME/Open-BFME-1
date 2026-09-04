// cl: /DNDEBUG /MD
//
// Retail 0x003E38F0: BFME Pathfinder::xfer.  The BFME Xfer ABI uses the
// overloaded operator== slots for the scalar and region transfers; the two
// small helper loops below are the already reconstructed retail array bodies.

typedef int Int;

struct IRegion2D
{
	Int loX;
	Int loY;
	Int hiX;
	Int hiY;
};

class Snapshot;
struct ICoord3D;
struct Region3D;
struct IRegion3D;
class Coord2D;
struct ICoord2D;
struct Region2D;
struct RealRange;
struct RGBColor;
struct RGBAColorReal;
struct RGBAColorInt;
struct XferReservedTag;
class AsciiString;
class UnicodeString;
struct Coord3DBase;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Xfer.h
class Xfer
{
public:
	class Version
	{
	public:
		unsigned char data[2];
	};

	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual bool IsCRC();
	virtual bool slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual Xfer &XferRawBytes(void *, unsigned int);

	virtual Xfer &xferVersion(Version *);
	virtual Xfer &slot11();
	virtual Xfer &slot12();
	virtual Xfer &slot13();
	virtual Xfer &slot14();
	virtual Xfer &slot15();
	virtual Xfer &slot16();
	virtual Xfer &xferIRegion2D(IRegion2D *);
	virtual Xfer &slot18();
	virtual Xfer &slot19();
	virtual Xfer &slot20();
	virtual Xfer &slot21();
	virtual Xfer &slot22();
	virtual Xfer &slot23();
	virtual Xfer &slot24();
	virtual Xfer &slot25();
	virtual Xfer &slot26();
	virtual Xfer &slot27();
	virtual Xfer &slot28();
	virtual Xfer &slot29();
	virtual Xfer &xferInt(Int *);
	virtual Xfer &slot31();
	virtual Xfer &slot32();
	virtual Xfer &slot33();
	virtual Xfer &slot34();
	virtual Xfer &xferBool(bool *);
};

// These are the named array helpers already landed beside the Pathfinder
// sources.  The first helper is the element operation used by the 512-cell
// loop; the second transfers the 64-entry floating-point array.
extern Xfer &__cdecl xferRva003D6CB0(Xfer &, Int (&)[512]);
extern Xfer &__cdecl xferRva003D6D40(Xfer &, float (&)[64]);
extern void __cdecl bfmeCalcTGC(void *, Int *);
extern void __cdecl bfmeXfer246FC(Xfer *, Int *);

class PathfindCell
{
public:
	void xfer(Xfer *xfer);

	void *m_info;					// +0x00
	Int m_field04;
	Int m_field08;
	Int m_field0c;
};

class PathfindLayer
{
public:
	void xfer(Xfer *xfer);

	char m_pad[0x44];
};

union PathfinderXferLocal
{
	Xfer::Version version;
	Int loopValue;
};

// The fields are named by their proven retail offsets.  In particular, the
// map is an array of columns of 16-byte cells, and the extent's high members
// are the loop limits used by the CRC branch.
class Pathfinder
{
public:
	virtual void xfer(Xfer *xfer);

	bool m_field04;				// +0x04
	char m_pad05[0x0c - 0x05];
	PathfindCell **m_map;			// +0x0c
	IRegion2D m_extent;			// +0x10
	Int m_field20;				// +0x20
	Int m_field24;				// +0x24
	Int m_field28;				// +0x28
	Int m_field2c;				// +0x2c
	char m_pad2d[0x830 - 0x30];
	Int m_field830;				// +0x830
	char m_pad834[4];
	bool m_field838;				// +0x838
	char m_pad839[3];
	Int m_field83c;				// +0x83c
	Int m_field840;				// +0x840
	char m_pad844[0x858 - 0x844];
	PathfindLayer m_layers[16];		// +0x858
	char m_padC98[0x243f0 - 0xc98];
	bool m_field243f0;			// +0x243f0
	bool m_field243f1;			// +0x243f1
	char m_pad243f2[2];
	Int m_field243f4;			// +0x243f4
	float m_field243f8[64];		// +0x243f8
	char m_pad244f8[0x246f8 - 0x244f8];
	Int m_field246f8;				// +0x246f8
	Int m_field246fc;				// +0x246fc
	char m_pad24700[0x24714 - 0x24700];
	Int m_field24714[512];			// +0x24714
	Int m_field24f14;				// +0x24f14
	Int m_field24f18;				// +0x24f18
};

void Pathfinder::xfer(Xfer *xfer)
{
	if (xfer->IsCRC())
	{
		Int x;
		Int y;
		xfer->xferIRegion2D(&m_extent);
		xfer->xferBool(&m_field04);
		xfer->xferBool(&m_field838);
		bfmeCalcTGC(xfer, &m_field840);
		xferRva003D6CB0(*xfer, m_field24714);
		xfer->xferInt(&m_field24f14);
		xfer->xferInt(&m_field24f18);
		xfer->xferInt(&m_field243f4);
		xferRva003D6D40(*xfer, m_field243f8);
		xfer->xferInt(&m_field83c);
		xfer->xferBool(&m_field243f0);
		xfer->xferBool(&m_field243f1);

		if (m_map != 0)
		{
			for (y = 0; y <= m_extent.hiY; ++y)
			{
				for (x = 0; x <= m_extent.hiX; ++x)
				{
					if (m_map[x][y].m_info != 0)
						m_map[x][y].xfer(xfer);
				}
			}
		}

		for (Int i = 0; i < 16; ++i)
			m_layers[i].xfer(xfer);
	}
	else
	{
		Xfer::Version version;
		version.data[0] = 1;
		version.data[1] = 1;
		xfer->xferVersion(&version);
		xfer->xferInt(&m_field28);
		xfer->xferInt(&m_field2c);
		xfer->xferInt(&m_field20);
		xfer->xferInt(&m_field24);
		xfer->xferInt(&m_field830);
		bfmeXfer246FC(xfer, &m_field246fc);
		xfer->xferInt(&m_field246f8);
	}
}
