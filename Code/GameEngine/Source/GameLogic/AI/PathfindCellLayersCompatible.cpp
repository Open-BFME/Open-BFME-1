// cl: /DNDEBUG /MD
//
// Retail 0x004022D0 (80B): free cdecl bool comparing two PathfindCell flag
// words for layer / connect-layer compatibility.

typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindCell
{
public:
	unsigned char m_pad[0x0c];
	unsigned int m_flags;
};

// ?bfmeLayersCompatible@@YA_NPBVPathfindCell@@0@Z
Bool bfmeLayersCompatible(const PathfindCell *a, const PathfindCell *b)
{
	unsigned int fa = a->m_flags;
	unsigned int fb = b->m_flags;
	if (((fa ^ fb) & 7) == 0)
	{
		int layerA = (int)((fa >> 6) & 0x3f);
		int layerB = (int)((fb >> 6) & 0x3f);
		if (layerA == layerB)
			return true;
		int connectB = (int)((fb >> 12) & 0x3f);
		if (layerA == connectB)
			return true;
		int connectA = (int)((fa >> 12) & 0x3f);
		if (connectA == layerB)
			return true;
		if (connectA == 0x10)
		{
			if (connectB == connectA)
				return true;
		}
	}
	return false;
}
