// Open-BFME5 conversions.
// Each callee is a real EA identity already landed in game/:
//   ILT 0x00013A61 -> Rva00411700::broadcast        (R3VirtualBroadcastLoops.cpp)
//   ILT 0x00006D7F -> Pathfinder::removeObjectFromPathfindMap (PathfindMapObjectWrappers.cpp)
//   ILT 0x0000B81B -> Pathfinder::addObjectToPathfindMap    (PathfindMapObjectWrappers.cpp)

class BfmeHostCL;
class Object;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class Pathfinder
{
public:
	void addObjectToPathfindMap(Object *object);
	void removeObjectFromPathfindMap(Object *object);
};

class PartitionData
{
public:
	void makeDirty();
};

class Rva009A2350
{
public:
	void init();
};

class Rva009F2BA0
{
public:
	void init();
};

class Rva00411700
{
public:
	void broadcast();
};

class AI
{
public:
	unsigned char m_bfmeHeadCL[0xc];
	Pathfinder *m_bfmePathCL;
};

extern AI *TheAI;

class BfmeHostCL
{
public:
	void bfmeResetCL(char full);

	unsigned char m_bfmeHeadCL[0x80];
	Rva00411700 *m_bfmeGateCL;
	unsigned char m_bfmeMidCL[0x32c];
	PartitionData *m_bfmePartCL;
	Rva009F2BA0 *m_bfmeThirdCL;
	Rva009A2350 *m_bfmeSecondCL;
};

void BfmeHostCL::bfmeResetCL(char full)
{
	if (m_bfmePartCL != 0)
		m_bfmePartCL->makeDirty();

	if (m_bfmeSecondCL != 0)
		m_bfmeSecondCL->init();

	if (m_bfmeThirdCL != 0)
		m_bfmeThirdCL->init();

	if (m_bfmeGateCL != 0)
		m_bfmeGateCL->broadcast();

	if (full != 0)
	{
		TheAI->m_bfmePathCL->removeObjectFromPathfindMap((Object *)this);
		TheAI->m_bfmePathCL->addObjectToPathfindMap((Object *)this);
	}
}