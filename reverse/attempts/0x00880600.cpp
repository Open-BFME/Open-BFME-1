// ?DoXfer@GeometryInfo@@UAEXAAVXfer@@@Z
// partial score=0.07 date=2026-09-21
// ?DoXfer@GeometryInfo@@UAEXAAVXfer@@@Z [retail body 0x00880600]
// GeometryInfo's vtable 0x01086138 slot 3 (Snapshot::DoXfer); slots 0-2 are
// still dumps but the GeometryInfo identity is proven by vtable_lookup.py:
// the SAME vtable is installed by the already-matched
// GeometryInfoDefaultConstructor.cpp / GeometryInfoCopyConstructor.cpp /
// GeometryInfoConstructor.cpp. Field offsets +0x2c (m_shapes, a BfmeVec60 of
// BfmeElem60 -- the identical element type Rva00880260Resize.cpp already
// matched) and the resize() call itself are shared with those files.
// Xfer vtable slots cross-checked against the independently matched
// Rva001C2E50Xfer.cpp: xferVersion=+0x28, xferInt=+0x78, xferBool=+0x8c.
// The string "GeometryType" at 0x01132a70 names the tagged xfer call used
// for BfmeElem60's leading enum field.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;

class XferVersionRec
{
public:
	XferVersionRec(UnsignedByte major, UnsignedByte minor) : m_major(major), m_minor(minor) {}
	UnsignedByte m_major;
	UnsignedByte m_minor;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Xfer.h
// Slot order proven against Rva001C2E50Xfer.cpp (matched): xferVersion@10,
// xferInt@30, xferBool@35. Slot 4 (+0x10), 24 (+0x60), 27 (+0x6c) and 36
// (+0x90) have no independent identity yet; address-derived names.
class Xfer
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual Bool slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void xferVersion(XferVersionRec &value);
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
	virtual void slot24(void *value);
	virtual void slot25();
	virtual void slot26();
	virtual void slot27(Real *value);
	virtual void slot28();
	virtual void slot29();
	virtual void xferInt(Int *value);
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void xferBool(Bool *value);
	virtual void slot36(const char *tag, void *data, Int size);
};

// upstream layout matches Rva00880260Resize.cpp (matched ?resize@BfmeVec60@@...)
struct BfmeTail60
{
	char *m_p;
	void release();
};

struct BfmeElem60
{
	BfmeElem60() : m_00(0), m_04(1.0f), m_08(1.0f), m_0C(1.0f), m_10(0), m_14(0), m_18(0), m_20(1)
	{
		m_1C.m_p = 0;
	}

	Int m_00;
	Real m_04;
	Real m_08;
	Real m_0C;
	Real m_10;
	Int m_14;
	Int m_18;
	BfmeTail60 m_1C;
	char m_20;
	char m_pad[3];
};

class BfmeVec60
{
public:
	void resize(UnsignedInt n, BfmeElem60 value);

	BfmeElem60 *_M_start;
	BfmeElem60 *_M_finish;
	BfmeElem60 *_M_end_of_storage;
};

class GeometryInfo
{
public:
	virtual ~GeometryInfo();
	virtual void slot1();
	virtual void slot2();
	virtual void DoXfer(Xfer &xfer);

private:
	char m_pad00[4];
	Bool m_flagA;
	char m_pad05[0x0B];
	Real m_realA;
	Real m_realB;
	UnsignedByte m_byteC;
	char m_pad19[0x0B];
	Real m_realD;
	Real m_realE;
	BfmeVec60 m_shapes;
	char m_pad38[0x0C];
	UnsignedByte m_byteE;
	char m_pad45[0x0B];
	UnsignedByte m_byteF;
};

void GeometryInfo::DoXfer(Xfer &xfer)
{
	if (xfer.slot04())
		return;

	XferVersionRec version(1, 2);
	xfer.xferVersion(version);

	xfer.xferBool(&m_flagA);

	UnsignedInt shapeCount = (UnsignedInt)(m_shapes._M_finish - m_shapes._M_start);
	xfer.xferInt((Int *)&shapeCount);

	m_shapes.resize(shapeCount, BfmeElem60());

	if ((Int)shapeCount > 0)
	{
		BfmeElem60 *shape = m_shapes._M_start;
		for (UnsignedInt i = 0; i < shapeCount; ++i, ++shape)
		{
			xfer.slot36("GeometryType", &shape->m_00, sizeof(Int));
			xfer.slot27(&shape->m_04);
			xfer.slot27(&shape->m_08);
			xfer.slot27(&shape->m_0C);
			xfer.slot24(&shape->m_10);

			if (version.m_minor > 1)
			{
				xfer.xferBool((Bool *)&shape->m_20);
			}
		}
	}

	xfer.slot27(&m_realA);
	xfer.slot27(&m_realB);
	xfer.slot27(&m_realD);
	xfer.slot27(&m_realE);
	xfer.slot24(&m_byteC);
	xfer.slot24(&m_byteE);
	xfer.slot24(&m_byteF);
}
