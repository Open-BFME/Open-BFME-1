// cl: /DNDEBUG /MD /EHs-c-

// FILE: W3DTerrainLogicExtent.cpp ////////////////////////////////////////////
//
// W3DTerrainLogic::getExtentIncludingBorder, retail 0x006BE190.
//
// No port of W3DTerrainLogic.cpp exists under Code/, so this is written from
// the reference body and the disassembly.  BFME's version is Zero Hour's plus
// two statements: after the four x/y writes it copies two members, at +0x18fc
// and +0x1900, into extent->lo.z and extent->hi.z.  Zero Hour never touches z
// here at all.
//
// Everything else the body needs it states itself: the border comes from
// TheTerrainRenderObject->getMap() at +0x2ff4 and an Int at +0x10 of that map
// (fild, so integer), scaled by the float constant at 0x01075c74; m_mapDX and
// m_mapDY are Ints at +0x10 and +0x14.  The lo.x and lo.y stores fold to one
// fchs because the reference writes 0.0f first and then subtracts.
//
// The class is a stand-in at the offsets this one body proves and nothing more.
// getExtentIncludingBorder is virtual and const, which is where the vtable
// pointer at +0x0 comes from -- it is not a member.
//
///////////////////////////////////////////////////////////////////////////////

typedef float Real;
typedef int Int;

// Scaled through the DIR32 site at 0x01075c74, which the byte comparison masks,
// so the literal only has to be a float.
#define MAP_XY_FACTOR 10.0f

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
class Coord3D
{
public:
	Real x;
	Real y;
	Real z;
};

// A struct, not a class: the mangled name spells it PAURegion3D@@.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Region3D
{
	Coord3D lo;
	Coord3D hi;
};

class BfmeWorldHeightMap
{
public:
	Int getBorderSizeInline( void ) const { return m_bfmeBorderSize; }
private:
	char m_bfmeHead[0x10];
	Int m_bfmeBorderSize;												// @0x10
};

class BfmeTerrainRenderObject
{
public:
	BfmeWorldHeightMap *getMap( void ) const { return m_bfmeMap; }
private:
	char m_bfmeHead[0x2ff4];
	BfmeWorldHeightMap *m_bfmeMap;							// @0x2ff4
};

extern BfmeTerrainRenderObject *TheTerrainRenderObject;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameLogic/W3DTerrainLogic.h
class W3DTerrainLogic
{
public:

	virtual void getExtentIncludingBorder( Region3D *extent ) const;

private:

	// vptr @0x0
	char m_bfmeHead[0x10 - 4];
	Int m_mapDX;																// @0x10
	Int m_mapDY;																// @0x14
	char m_bfmeMiddle[0x18fc - 0x18];
	Real m_bfmeExtentLoZ;												// @0x18fc
	Real m_bfmeExtentHiZ;												// @0x1900

};

void W3DTerrainLogic::getExtentIncludingBorder( Region3D *extent ) const
{
	extent->lo.x = 0.0f;
	extent->lo.y = 0.0f;

	Real border = TheTerrainRenderObject->getMap()->getBorderSizeInline() * MAP_XY_FACTOR;
	extent->lo.x -= border;
	extent->lo.y -= border;
	extent->hi.x = (m_mapDX * MAP_XY_FACTOR)-border;
	extent->hi.y = (m_mapDY * MAP_XY_FACTOR)-border;
	extent->lo.z = m_bfmeExtentLoZ;
	extent->hi.z = m_bfmeExtentHiZ;
}
