// cl: /Igame/GameEngine/Source/Common
#include "debug.h"

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Xfer;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	Snapshot();
	~Snapshot();

protected:
	virtual void crc(Xfer *xfer) = 0;
	virtual void xfer(Xfer *xfer) = 0;
	virtual void loadPostProcess() = 0;
};

class PathNode
{
public:
	const PathNode *getNext() const { return m_next; }
	const PathNode *getNextOptimized() const { return m_nextOptimized; }

	PathNode *m_next;
	PathNode *m_previous;
	PathNode *m_nextOptimized;
	Coord3D m_position;
};

// PathNode::getPosition has no retail address (always inlined). A member here
// emitted a ?getPosition@PathNode@@ COMDAT unlike the first copy in link
// order (this view puts m_position at +0x0C), so this TU reads it through a
// file-local inline instead.
static inline const Coord3D *pathNodePosition(const PathNode *node)
{
	return &node->m_position;
}

class Path : public Snapshot
{
public:
	const PathNode *getFirstNode() const { return m_path; }

protected:
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();

private:
	PathNode *m_path;
};

Debug &Rva003D6300(Debug &debug, const Path &path)
{
	debug << "[path:";

	const PathNode *nextOptimized = path.getFirstNode();
	for (const PathNode *node = path.getFirstNode(); node; node = node->getNext())
	{
		debug << "\n  ";
		if (node == nextOptimized)
		{
			debug << "(opt)";
			nextOptimized = nextOptimized->getNextOptimized();
		}

		const Coord3D *position = pathNodePosition(node);
		debug << "(" << position->x << ", " << position->y << ", " << position->z << ")";
	}

	debug << "]\n";
	return debug;
}
