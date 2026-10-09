// GeometryInfo snapshot transfer; the BFME layout follows the matched constructors.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c- /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include/Common /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib
#include "snapshot.h"
#include "xfer.h"
#include "coord3d.h"
#include "ascii_string.h"

struct BfmeCoord3D
{
	__forceinline BfmeCoord3D() throw() : x(0.0f), y(0.0f), z(0.0f) {}

	float x;
	float y;
	float z;
};

class BfmeAsciiString : public AsciiString
{
};

struct BfmeElem60Head
{
	BfmeElem60Head() : m_type(0), m_height(1.0f), m_majorRadius(1.0f), m_minorRadius(1.0f) {}
	int m_type;
	float m_height;
	float m_majorRadius;
	float m_minorRadius;
};

struct BfmeElem60 : public BfmeElem60Head
{
	__forceinline BfmeElem60() throw()
		: m_center(), m_name(), m_enabled(true)
	{
	}

	BfmeCoord3D m_center;
	BfmeAsciiString m_name;
	bool m_enabled;
	unsigned char m_padding[3];
};

class BfmeVec60
{
public:
	void resize(unsigned int count, BfmeElem60 value);
	void resize(unsigned int count) { resize(count, BfmeElem60()); }

	BfmeElem60 *m_begin;
	BfmeElem60 *m_end;
	BfmeElem60 *m_capacity;
};

class Rva00880600Xfer36View
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual Xfer &slot36(const char *tag, void *data, unsigned int size) = 0;
};

namespace Rva00880600
{
struct Version : Xfer::Version
{
	Version(unsigned char major, unsigned char minor)
	{
		data[0] = major;
		data[1] = minor;
	}
};
}

class GeometryInfo : public Snapshot
{
public:
	virtual void DoXfer(Xfer &xfer);

private:
	bool m_isSmall;
	unsigned char m_pad05[3];
	int m_scalar08;
	int m_scalar0c;
	float m_scalar10;
	float m_scalar14;
	Coord3DBase m_coord18;
	float m_scalar24;
	float m_scalar28;
	BfmeVec60 m_shapes;
	unsigned char m_records[0x0C];
	Coord3DBase m_coord44;
	Coord3DBase m_coord50;
};

// ?DoXfer@GeometryInfo@@UAEXAAVXfer@@@Z
void GeometryInfo::DoXfer(Xfer &xfer)
{
	if (xfer.IsLightCRC())
		return;

	int shape_frame_shapeCount_140;
	Rva00880600::Version version(1, 2);
	xfer == version;

	xfer == m_isSmall;

	shape_frame_shapeCount_140 = (int)(m_shapes.m_end - m_shapes.m_begin);
	xfer == shape_frame_shapeCount_140;

	m_shapes.resize((unsigned int)shape_frame_shapeCount_140);

	int i;
	i = 0;
	if (shape_frame_shapeCount_140 > 0)
	{
		for (; i < shape_frame_shapeCount_140; ++i)
		{
			BfmeElem60 *shape = &m_shapes.m_begin[i];
			((Rva00880600Xfer36View &)xfer).slot36("GeometryType", &shape->m_type, sizeof(int));
			xfer == shape->m_height;
			xfer == shape->m_majorRadius;
			xfer == shape->m_minorRadius;
			xfer == (Coord3DBase &)shape->m_center;

			if (version.data[1] > 1)
				xfer == shape->m_enabled;
		}
	}

	xfer == m_scalar10;
	xfer == m_scalar14;
	xfer == m_scalar24;
	xfer == m_scalar28;
	xfer == m_coord18;
	xfer == m_coord44;
	xfer == m_coord50;
}
