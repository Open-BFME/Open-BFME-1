// ?rva001a7e30@TerrainLogic@@QBE_NPBUBridgeEndTestInfo001A7E30@@HH@Z
// partial score=0.5 date=2026-09-21
// ?rva001a7e30@TerrainLogic@@QBE_NHPBUBridgeEndTestInfo001A7E30@@H@Z
// cl: /DNDEBUG /MD /EHs-c-
//
// Retail 0x001A7E30 (252B). Reached only through the still-dump ILT thunks
// in the brief; no named caller. Walks the BfmeBridgeNode list (m_next at
// +4, m_layer at +0x88 -- Code/GameEngine/Source/GameLogic/Map/
// TerrainLogic.cpp:1717-1719) off a vslot-0x94 accessor on "this" for the
// node matching the layer argument, then tests the point against the
// bridge (isPointOnBridge) and the bridge's end cell (isCellOnEnd) before
// checking a height threshold via getBridgeHeight.

typedef bool Bool;
typedef int Int;
typedef float Real;

struct Coord3D
{
	Real x, y, z;
};

struct Region2D
{
	Real loX, loY, hiX, hiY;
};

class Bridge
{
public:
	bool isPointOnBridge(const Coord3D *point);
	bool isCellOnEnd(const Region2D *region);
	float getBridgeHeight(const Coord3D *pos, Coord3D *normal);

	void *m_unmodelled00;				// +0x00
	Bridge *m_next;					// +0x04
	unsigned char m_pad08[0x5c - 0x08];
	int m_bridgeType;					// +0x5c
	unsigned char m_pad60[0x88 - 0x60];
	int m_layer;						// +0x88
};

// Only the two fields the body reads; the struct is at least 0xc0 bytes.
struct BridgeEndTestInfo001A7E30
{
	unsigned char m_pad00[0x38];
	Coord3D m_point;					// +0x38 .. +0x44
	unsigned char m_pad44[0xbc - 0x44];
	Real m_radius;						// +0xbc
};

extern const float g_bfmeK1266C;
extern const float g_bfmeDirectionWeight1285;

class TerrainLogic
{
public:
	virtual void bfmeUnusedSlot00();
	virtual void bfmeUnusedSlot01();
	virtual void bfmeUnusedSlot02();
	virtual void bfmeUnusedSlot03();
	virtual void bfmeUnusedSlot04();
	virtual void bfmeUnusedSlot05();
	virtual void bfmeUnusedSlot06();
	virtual void bfmeUnusedSlot07();
	virtual void bfmeUnusedSlot08();
	virtual void bfmeUnusedSlot09();
	virtual void bfmeUnusedSlot10();
	virtual void bfmeUnusedSlot11();
	virtual void bfmeUnusedSlot12();
	virtual void bfmeUnusedSlot13();
	virtual void bfmeUnusedSlot14();
	virtual void bfmeUnusedSlot15();
	virtual void bfmeUnusedSlot16();
	virtual void bfmeUnusedSlot17();
	virtual void bfmeUnusedSlot18();
	virtual void bfmeUnusedSlot19();
	virtual void bfmeUnusedSlot20();
	virtual void bfmeUnusedSlot21();
	virtual void bfmeUnusedSlot22();
	virtual void bfmeUnusedSlot23();
	virtual void bfmeUnusedSlot24();
	virtual void bfmeUnusedSlot25();
	virtual void bfmeUnusedSlot26();
	virtual void bfmeUnusedSlot27();
	virtual void bfmeUnusedSlot28();
	virtual void bfmeUnusedSlot29();
	virtual void bfmeUnusedSlot30();
	virtual void bfmeUnusedSlot31();
	virtual void bfmeUnusedSlot32();
	virtual void bfmeUnusedSlot33();
	virtual void bfmeUnusedSlot34();
	virtual void bfmeUnusedSlot35();
	virtual void bfmeUnusedSlot36();
	// vslot 0x94 (index 37): yields the BfmeBridgeNode list head for the owner.
	virtual Bridge *bfmeGetFirstBridgeNode001A7E30() const;

	bool rva001a7e30(const BridgeEndTestInfo001A7E30 *info, int layer, int unused3) const;
};

bool TerrainLogic::rva001a7e30(const BridgeEndTestInfo001A7E30 *info, int layer, int unused3) const
{
	if (layer == 1)
		return false;

	Bridge *node = bfmeGetFirstBridgeNode001A7E30();

	while (node != 0)
	{
		if (node->m_layer == layer)
			break;
		node = node->m_next;
	}
	if (node == 0)
		return false;

	Bool onBridge = false;
	if (node->isPointOnBridge(&info->m_point))
		onBridge = true;

	Real radius = info->m_radius + g_bfmeK1266C;
	Region2D box;
	box.loX = info->m_point.x - radius;
	box.loY = info->m_point.y - radius;
	box.hiX = info->m_point.x + radius;
	box.hiY = info->m_point.y + radius;

	if (node->isCellOnEnd(&box))
		return true;

	if (!onBridge)
		return false;

	Real height = node->getBridgeHeight(&info->m_point, 0);
	if (((height - info->m_point.z) < 0 ? -(height - info->m_point.z) : (height - info->m_point.z))
		>= g_bfmeDirectionWeight1285)
		return false;

	if (onBridge)
	{
		if (node->m_bridgeType == 3)
			return false;
	}

	return true;
}
