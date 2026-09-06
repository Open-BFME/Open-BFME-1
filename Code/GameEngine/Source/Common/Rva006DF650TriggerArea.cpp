// cl: /O2 /DNDEBUG /MD /EHsc /Ireference/shims/stringinline

#include "StringInline.h"

// 0x006DF650, 168 bytes, __thiscall returning Bool, `ret 8`.
//
// IDENTITY.  The object is the one constructed at 0x006DF550 (vtable
// 0x0111E188), already spelled `Rva006DF550` by the recompute body at
// 0x006DF090; that constructor zeroes exactly +0x1C and +0x20/+0x24/+0x28,
// which is the pointer and the three floats this body writes.  The two callees
// are pinned, not guessed: 0x0004AB6F is
// ?pointInTrigger@PolygonTrigger@@QBE_NAAUICoord3D@@@Z (decoded out of
// PartitionFilterPolygonTrigger::allow) and 0x00007AD6 is
// ?getCenterPoint@PolygonTrigger@@QBEXPAUCoord3D@@@Z.  That fixes +0x1C as a
// PolygonTrigger* and +0x20 as a Coord3D, and it fixes the global at
// 0x012EF4CC -- independently pinned as ?TheTerrainLogic@@3PAVTerrainLogic@@A
// -- as the singleton whose virtual at +0x90 hands back a PolygonTrigger for
// an AsciiString passed BY VALUE.  The copy constructor at 0x00887B60 is the
// refcounting StringBase<char> copy already pinned as ??0AsciiString@@QAE@ABV0@@Z.
//
// WHAT IS *NOT* RECOVERED is the name of the enclosing class and of this
// member, so both stay address-derived.  The virtual index 36 on TerrainLogic
// and index 21 on the owner are read off the byte offsets 0x90 and 0x54; the
// intervening slots are placeholders and carry no claim.
//
// SHAPE.  The temporary AsciiString is built at ESP and consumed by the
// virtual call with no cleanup, which is only consistent with a by-value class
// parameter whose type has no destructor here; spelling the argument as a
// temporary copy is what puts the copy constructor immediately before the
// `call [edx+0x90]` with nothing in between.  The three __ftol2 calls are the
// int members of the ICoord3D reference pointInTrigger takes, assigned in
// x/y/z order -- that interleaving of `fld` and the store of the previous
// result is the compiler's, not source order.

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct ICoord3D
{
	int x;
	int y;
	int z;
};

class PolygonTrigger
{
public:
	bool pointInTrigger(ICoord3D &point) const;
	void getCenterPoint(Coord3D *center) const;
};

class TerrainLogic
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0c();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1c();
	virtual void v20();
	virtual void v24();
	virtual void v28();
	virtual void v2c();
	virtual void v30();
	virtual void v34();
	virtual void v38();
	virtual void v3c();
	virtual void v40();
	virtual void v44();
	virtual void v48();
	virtual void v4c();
	virtual void v50();
	virtual void v54();
	virtual void v58();
	virtual void v5c();
	virtual void v60();
	virtual void v64();
	virtual void v68();
	virtual void v6c();
	virtual void v70();
	virtual void v74();
	virtual void v78();
	virtual void v7c();
	virtual void v80();
	virtual void v84();
	virtual void v88();
	virtual void v8c();
	virtual PolygonTrigger *getTriggerAreaByName(AsciiString name);
};

extern TerrainLogic *TheTerrainLogic;

class Rva006DF550
{
public:
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0c();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1c();
	virtual void v20();
	virtual void v24();
	virtual void v28();
	virtual void v2c();
	virtual void v30();
	virtual void v34();
	virtual void v38();
	virtual void v3c();
	virtual void v40();
	virtual void v44();
	virtual void v48();
	virtual void v4c();
	virtual void v50();
	virtual void v54(const Coord3D *position);

	bool bfmeSetTriggerArea(const AsciiString &name, const Coord3D *position);

private:
	char m_pad04[0x1c - 0x04];
	PolygonTrigger *m_trigger1c;
	Coord3D m_center20;
};

bool Rva006DF550::bfmeSetTriggerArea(const AsciiString &name, const Coord3D *position)
{
	m_trigger1c = TheTerrainLogic->getTriggerAreaByName(name);
	if (m_trigger1c == 0)
		return false;

	if (position == 0)
		return false;

	ICoord3D cell;
	cell.x = (int)position->x;
	cell.y = (int)position->y;
	cell.z = (int)position->z;

	if (m_trigger1c->pointInTrigger(cell))
	{
		m_center20 = *position;
		return false;
	}

	m_trigger1c->getCenterPoint(&m_center20);
	v54(position);
	return true;
}
