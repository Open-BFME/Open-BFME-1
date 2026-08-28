// BFME's full PathfindLayer reset differs from the later reference body: after
// releasing the cell allocation it also clears the bridge and trigger state.
// The existing AIPathfind.cpp owns the public reset name, so this focused TU
// uses a collision-free selector for the retail body.

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
	void bfmeResetFull(void);
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

// ?bfmeResetFull@PathfindLayer@@QAEXXZ
void PathfindLayer::bfmeResetFull(void)
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
