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
	const Coord3D *getPosition() const { return &m_position; }

private:
	PathNode *m_next;
	PathNode *m_previous;
	PathNode *m_nextOptimized;
	Coord3D m_position;
};

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

		const Coord3D *position = node->getPosition();
		debug << "(" << position->x << ", " << position->y << ", " << position->z << ")";
	}

	debug << "]\n";
	return debug;
}
