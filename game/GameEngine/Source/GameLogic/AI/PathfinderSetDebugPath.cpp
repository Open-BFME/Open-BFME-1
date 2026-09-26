// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x003D9880: Pathfinder::setDebugPath.
// The BFME Pathfinder keeps debugPath at this+0x854.  The retail body also
// performs the GameInfo slot-11 call before checking the AI debug option.

typedef int Int;
typedef float Real;
typedef bool Bool;

enum PathfindLayerEnum
{
	LAYER_INVALID = 0,
	LAYER_GROUND = 1
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class PathNode
{
public:
	PathNode *m_next;
	PathNode *m_previous;
	PathNode *m_nextOptimized;
	Coord3D m_position;
	PathfindLayerEnum m_layer;
	Bool m_canOptimize;
	Int m_costSoFar;
};

class __declspec(novtable) Path
{
public:
	Path();
	void appendNode(const Coord3D *position, PathfindLayerEnum layer);

protected:
	virtual ~Path();

	public:
	PathNode *m_path;
	PathNode *m_pathTail;
	Bool m_isOptimized;
	char m_bfmeTail[0x24 - 0x10];
};

class BFMEDeletablePath : public Path
{
public:
	void destroy(void) { Path::~Path(); }
};

class PathAppendNodeILT
{
public:
	void appendNode(const Coord3D *position, PathfindLayerEnum layer);
};

class GameInfo
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
};

struct GlobalData
{
	char m_bfmeHead[0xA88];
	Int m_debugAI;
};

extern GameInfo *TheGameInfo;
extern GlobalData *TheWritableGlobalData;
extern void __cdecl operator delete(void *block);

class Pathfinder
{
public:
	void setDebugPath(Path *newDebugpath);

private:
	char m_bfmeHead[0x854];
	Path *debugPath;
};

void Pathfinder::setDebugPath(Path *newDebugpath)
{
	if (TheGameInfo)
		TheGameInfo->slot11();

	if (TheWritableGlobalData->m_debugAI)
	{
		if (debugPath)
		{
			Path *path = debugPath;
			reinterpret_cast<BFMEDeletablePath *>(path)->destroy();
			::operator delete(path);
		}

		debugPath = new Path;
		for (PathNode *copyNode = newDebugpath->m_path;
			copyNode;
			copyNode = copyNode->m_nextOptimized)
		{
			reinterpret_cast<PathAppendNodeILT *>(debugPath)->appendNode(
				&copyNode->m_position, copyNode->m_layer);
		}
	}
}
