// ?privateFollowPath@GiantBirdAIUpdate@@QAEXPBUPathNode@@PAXW4CommandSourceType@@_N@Z
// partial score=0.32 date=2026-09-21
// cl: /DNDEBUG /MD /EHsc
//
// Open-BFME: anonymous carved body at 0x002C2C10 (435 bytes). The landed
// sibling GiantBirdAIUpdate::privateFollowPathAppend (0x002C2830, see
// GiantBirdAIUpdate_privateFollowPathAppend.cpp) already proves the
// PathVector/AIStateMachine/GiantBirdAIUpdate shapes reused here: this+0x30
// is getStateMachine(), the vector-of-Coord3D push_back/overflow pattern is
// the same PathVector layout, and 0x0000DE68/0x000070CC are the same
// ~PathVector / insertInitial alternate-name callees. This body walks a
// caller-supplied circular linked list of Coord3D nodes (Coord3D at node+0xc,
// a "more" flag at node+0x4c, next pointer at node+0x20) into a local
// PathVector, picks the node at 1/3 of the accumulated element count, and
// forwards it as the new goal position -- best read as
// GiantBirdAIUpdate::privateFollowPath, the method
// privateFollowPathAppend calls.
//
// this-relative fields (brief evidence): +0x08 body pointer, +0x1cc a
// secondary object with a field at +0x44 mirrored to +0x478, +0x344 bit 0 on
// the body is an early-exit flag, +0x478/+0x488 already named by the sibling
// comment ("dynamic path reset byte at +0x488").

typedef bool Bool;
typedef int Int;

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_AI = 1
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

class PathVector
{
public:
	PathVector() : m_start(0), m_finish(0), m_endOfStorage(0) {}
	~PathVector();

	Coord3D *m_start;
	Coord3D *m_finish;
	Coord3D *m_endOfStorage;
};

extern "C" void Rva000070CCOverflow(PathVector *v, Coord3D *pos, bool atEnd);

struct PathNode
{
	unsigned char m_pad0[0x0c];
	Coord3D m_position;
	unsigned char m_pad1[0x20 - 0x18];
	PathNode *m_next;
	unsigned char m_pad2[0x4c - 0x24];
	int m_more;
};

class ObjectIsMobileBody
{
public:
	bool isMobile() const;

	unsigned char m_pad[0x344];
	unsigned char m_flags344;
};

class BfmeSub30_7F0
{
public:
	void setGoalPosition(const Coord3D *pos);
	void step2(void *arg);
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
};

class Rva002BC470StateAction
{
public:
	void finish(void *arg);
};

class Rva002BC470Sub
{
public:
	int m_pad[0x44 / 4];
};

class GiantBirdAIUpdate
{
public:
	void privateFollowPath(const PathNode *path, void *ignoreObject,
		CommandSourceType commandSource, Bool exitProduction);

private:
	unsigned char m_pad0[8];
	ObjectIsMobileBody *m_body;
	unsigned char m_pad1[0x30 - 0xc];
	BfmeSub30_7F0 *m_stateMachine;
	unsigned char m_pad2[0x1cc - 0x34];
	Rva002BC470Sub *m_sub1cc;
	unsigned char m_pad3[0x478 - 0x1d0];
	int m_field478;
	unsigned char m_pad5[0x488 - 0x47c];
	unsigned char m_field488;
};

// address-derived identity: called from GiantBirdAIUpdate::privateFollowPathAppend
void GiantBirdAIUpdate::privateFollowPath(const PathNode *path,
	void * /*ignoreObject*/, CommandSourceType commandSource, Bool /*exitProduction*/)
{
	if (m_body->m_flags344 & 1)
		return;
	if (!m_body->isMobile())
		return;

	if (Rva002BC470Sub *sub = m_sub1cc)
	{
		m_field478 = sub->m_pad[0x44 / 4 - 1];
		m_field488 = 0;
	}

	PathVector localPath;

	if (path)
	{
		const PathNode *node = path;
		for (;;)
		{
			if (localPath.m_finish != localPath.m_endOfStorage)
			{
				*localPath.m_finish = node->m_position;
				++localPath.m_finish;
			}
			else
			{
				Rva000070CCOverflow(&localPath, (Coord3D *)&node->m_position, true);
			}

			if (!node->m_more)
				break;
			node = node->m_next;
			if (node == path)
				break;
		}
	}

	m_field488 = 1;
	m_stateMachine->slot14();

	int count = (int)(localPath.m_finish - localPath.m_start) / 3;
	if (count != 0)
	{
		Coord3D *mid = (Coord3D *)((char *)localPath.m_start + (count * 3) * 4 - 0xc);
		m_stateMachine->setGoalPosition(mid);
		m_stateMachine->step2(&localPath.m_start);
	}

	Rva002BC470StateAction *action = (Rva002BC470StateAction *)this;
	action->finish((void *)(int)(commandSource != CMD_FROM_PLAYER ? 0x3f8 : 0x3f7));
}
