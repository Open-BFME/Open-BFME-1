// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// BFME loadBridges at 0x006DA8A0. Map nodes retain their authored Z offset
// above the terrain; both height queries dispatch through retail slot 0x248.
#include "StringInline.h"

typedef float Real;
typedef bool Bool;

class Vector3
{
public:
	Real X, Y, Z;
	Vector3() {}
	Vector3(const Vector3 &v) : X(v.X), Y(v.Y), Z(v.Z) {}
	void Set(Real x, Real y, Real z) { X = x; Y = y; Z = z; }
};

struct Coord3D { Real x, y, z; };
class Dict;

// Declaration-only vtable slices, as in W3DTerrainLogicGetLayerHeight.cpp.
#define UNUSED_VIRTUALS_16(prefix) \
	virtual void prefix##0() = 0; virtual void prefix##1() = 0; \
	virtual void prefix##2() = 0; virtual void prefix##3() = 0; \
	virtual void prefix##4() = 0; virtual void prefix##5() = 0; \
	virtual void prefix##6() = 0; virtual void prefix##7() = 0; \
	virtual void prefix##8() = 0; virtual void prefix##9() = 0; \
	virtual void prefix##a() = 0; virtual void prefix##b() = 0; \
	virtual void prefix##c() = 0; virtual void prefix##d() = 0; \
	virtual void prefix##e() = 0; virtual void prefix##f() = 0

class BaseHeightMapRenderObjClass
{
public:
	UNUSED_VIRTUALS_16(unused000_);
	UNUSED_VIRTUALS_16(unused040_);
	UNUSED_VIRTUALS_16(unused080_);
	UNUSED_VIRTUALS_16(unused0c0_);
	UNUSED_VIRTUALS_16(unused100_);
	UNUSED_VIRTUALS_16(unused140_);
	UNUSED_VIRTUALS_16(unused180_);
	UNUSED_VIRTUALS_16(unused1c0_);
	UNUSED_VIRTUALS_16(unused200_);
	virtual void unused240_0() = 0;
	virtual void unused240_1() = 0;
	virtual Real getHeightMapHeight(Real x, Real y, Coord3D *normal) const;
};
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

class W3DTerrainLogic
{
public:
	UNUSED_VIRTUALS_16(unused000_);
	UNUSED_VIRTUALS_16(unused040_);
	virtual void unused080() = 0;
	virtual void unused084() = 0;
	virtual void unused088() = 0;
	virtual void unused08c() = 0;
	virtual void unused090() = 0;
	virtual void unused094() = 0;
	virtual void unused098() = 0;
	virtual void unused09c() = 0;
	virtual void unused0a0() = 0;
	virtual void unused0a4() = 0;
	virtual void unused0a8() = 0;
	virtual void unused0ac() = 0;
	virtual void unused0b0() = 0;
	virtual void unused0b4() = 0;
	virtual void updateBridgeDamageStates(void);
};
#undef UNUSED_VIRTUALS_16

// Reuse the established coordinate-accessor identity at 0x00087CC0.
// These names are reconstruction views, not recovered retail class names.
class BfmeRetBWF { public: Real x, y, z; };

struct BfmeThingBWF
{
	unsigned char m_unmodelled_00[4];
	BfmeThingBWF *m_next;
	unsigned char m_unmodelled_08[0x14 - 8];
	AsciiString m_name;
	unsigned char m_unmodelled_18[8];
	unsigned int m_flags;

	BfmeRetBWF *bfmeGoBWF();
	unsigned char getFlag(int bit) const
	{
		return (unsigned char)(m_flags >> bit) & 1;
	}
	Dict *getProperties() { return (Dict *)((char *)this + 0x24); }
};

class BfmeMapObjectListHolder
{
public:
	BfmeThingBWF *m_head;
};
extern BfmeMapObjectListHolder *BfmeTheMapObjectListHolder;

class W3DBridgeBuffer
{
public:
	void clearAllBridges();
	void loadBridges(W3DTerrainLogic *terrain, Bool saveGame);
protected:
	void addBridge(Vector3 from, Vector3 to, AsciiString name,
		W3DTerrainLogic *terrain, Dict *properties);
};

void W3DBridgeBuffer::loadBridges(W3DTerrainLogic *terrain, Bool saveGame)
{
	clearAllBridges();
	for (BfmeThingBWF *node = BfmeTheMapObjectListHolder->m_head;
		node; node = node->m_next)
	{
		if (node->getFlag(4))
		{
			BfmeThingBWF *second = node->m_next;
			if (!second) break;
			if (!second->getFlag(5)) continue;
			Vector3 from, to;
			from.Set(node->bfmeGoBWF()->x, node->bfmeGoBWF()->y, node->bfmeGoBWF()->z);
			from.Z = TheTerrainRenderObject->getHeightMapHeight(from.X, from.Y, 0) + from.Z + 0.25f;
			to.Set(second->bfmeGoBWF()->x, second->bfmeGoBWF()->y, second->bfmeGoBWF()->z);
			to.Z = TheTerrainRenderObject->getHeightMapHeight(to.X, to.Y, 0) + to.Z + 0.25f;
			addBridge(from, to, node->m_name, terrain, node->getProperties());
			node = second;
		}
	}
	if (terrain) terrain->updateBridgeDamageStates();
}
