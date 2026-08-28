// BFME's PathfindLayer destructor has the same full-reset body as reset().
// The vector-destruction callback at the retail entry proves the identity;
// this focused TU uses a collision-free name because AIPathfind.cpp already
// defines the public destructor from the later reference source.

typedef int Int;

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

class PolygonTrigger
{
public:
	virtual ~PolygonTrigger();
};

struct ICoord2D
{
	Int x;
	Int y;
};

class PathfindLayer
{
public:
	void bfmeDestroy(void);
	void bfmeReset(void);

private:
	unsigned char m_head[0x18];
	ICoord2D m_startCell;
	ICoord2D m_endCell;
	PathfindLayerEnum m_layer;
	Int m_zone;
	Int m_unknown30;
	unsigned char m_destroyedAndPad[4];
	void *m_bridge;
	PolygonTrigger *m_trigger;
	Int m_triggerObjectID;
};

// ?bfmeDestroy@PathfindLayer@@QAEXXZ
void PathfindLayer::bfmeDestroy(void)
{
	m_bridge = 0;
	bfmeReset();
	m_layer = LAYER_GROUND;
	if (m_trigger)
		delete m_trigger;
	m_trigger = 0;
	m_zone = 0;
	m_unknown30 = 0;
	m_startCell.x = -1;
	m_startCell.y = -1;
	m_endCell.x = -1;
	m_endCell.y = -1;
	m_triggerObjectID = -1;
}
