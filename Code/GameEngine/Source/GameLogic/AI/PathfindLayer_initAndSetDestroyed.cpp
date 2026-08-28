// cl: /DNDEBUG /MD /EHsc
// readable body of ?init@PathfindLayer@@QAE_NPAVBridge@@W4PathfindLayerEnum@@@Z: Code/GameEngine/Source/GameLogic/AI/AIPathfind.cpp
// readable body of ?setDestroyed@PathfindLayer@@QAE_N_N@Z: Code/GameEngine/Source/GameLogic/AI/AIPathfind.cpp

// Open-BFME5: PathfindLayer::init (42B at 0x003FB950) and
// PathfindLayer::setDestroyed (44B at 0x003FCEC0). Both carried only machine
// byte-dump rows; reverse/reloc_names.csv holds their names with
// identity=real.
//
// They extend the layout the isUsed body at 0x003FBB90 already fixed: the two
// pointers at +0x38 and +0x3C that decide whether the layer is in use. init
// refuses when either is set, then stores the bridge at +0x38, the layer enum
// at +0x28 and clears the flag at +0x34. setDestroyed is a no-op returning
// false when the flag already matches, and otherwise picks its notification by
// whether the bridge at +0x38 is set.

typedef bool Bool;

class Bridge;

enum PathfindLayerEnum { BFME_LAYER_INVALID = 0 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindLayer
{
public:
	Bool init(Bridge *bridge, PathfindLayerEnum layer);
	Bool setDestroyed(Bool destroyed);

private:
	void bfmeNotifyBridge(void);				// retail 0x0003B250
	void bfmeNotifyPlain(void);				// retail 0x0003A03F

	char m_bfmeHeadA[0x28];
	PathfindLayerEnum m_bfmeLayer;				// +0x28
	char m_bfmeHeadB[0x34 - 0x2C];
	Bool m_bfmeDestroyed;					// +0x34
	char m_bfmeHeadC[0x38 - 0x35];
	Bridge *m_bfmeBridge;					// +0x38
	Bridge *m_bfmeOther;					// +0x3C
};

// ?init@PathfindLayer@@QAE_NPAVBridge@@W4PathfindLayerEnum@@@Z
Bool PathfindLayer::init(Bridge *bridge, PathfindLayerEnum layer)
{
	if (m_bfmeBridge != 0 || m_bfmeOther != 0)
		return false;

	m_bfmeBridge = bridge;
	m_bfmeLayer = layer;
	m_bfmeDestroyed = false;
	return true;
}

// ?setDestroyed@PathfindLayer@@QAE_N_N@Z
Bool PathfindLayer::setDestroyed(Bool destroyed)
{
	if (destroyed == m_bfmeDestroyed)
		return false;

	m_bfmeDestroyed = destroyed;

	if (m_bfmeBridge != 0)
		bfmeNotifyBridge();
	else
		bfmeNotifyPlain();

	return true;
}
