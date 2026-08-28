// Advance BFME's cached optimized-path cursor and return its cached point.
// This state is absent from the later reference Path layout, so the focused
// body uses a descriptive collision-free selector.

typedef float Real;

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
	int m_layer;
	bool m_canOptimize;
	unsigned char m_padding[3];
	int m_waypointID;
};

class Path
{
public:
	void bfmeAdvanceCachedPoint(Coord3D &position);

private:
	unsigned char m_head[4];
	PathNode *m_path;
	PathNode *m_pathTail;
	int m_isOptimized;
	PathNode *m_cpopRecentStart;
	Coord3D m_cachedPosition;
	Real m_cachedDistance;
};

// ?bfmeAdvanceCachedPoint@Path@@QAEXAAUCoord3D@@@Z
void Path::bfmeAdvanceCachedPoint(Coord3D &position)
{
	if (m_path == 0)
	{
		position.x = 0.0f;
		position.y = 0.0f;
		position.z = 0.0f;
		return;
	}
	if (m_cpopRecentStart != 0)
		m_cpopRecentStart = m_cpopRecentStart->m_nextOptimized;
	if (m_cpopRecentStart != 0 && m_cpopRecentStart->m_nextOptimized != 0)
	{
		m_cachedPosition = m_cpopRecentStart->m_position;
		m_cachedDistance = 0.0f;
	}
	position.x = m_cachedPosition.x;
	position.y = m_cachedPosition.y;
	position.z = m_cachedPosition.z;
}
