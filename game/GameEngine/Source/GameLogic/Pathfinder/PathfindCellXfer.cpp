// cl: /O2 /DNDEBUG /MD

typedef int Int;

class Xfer
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual bool IsCRC();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual Xfer &slot09(void *, unsigned int);
	virtual Xfer &slot10(void *);
	virtual Xfer &slot11();
	virtual Xfer &slot12();
	virtual Xfer &slot13();
	virtual Xfer &slot14();
	virtual Xfer &slot15();
	virtual Xfer &slot16();
	virtual Xfer &slot17(void *);
	virtual Xfer &slot18();
	virtual Xfer &slot19(void *);
	virtual Xfer &slot20();
	virtual Xfer &slot21();
	virtual Xfer &slot22();
	virtual Xfer &slot23();
	virtual Xfer &slot24();
	virtual Xfer &slot25();
	virtual Xfer &slot26();
	virtual Xfer &slot27();
	virtual Xfer &slot28();
	virtual Xfer &slot29();
	virtual Xfer &xferInt(Int *);
	virtual Xfer &slot31(void *);
	virtual Xfer &slot32();
	virtual Xfer &slot33();
	virtual Xfer &slot34();
	virtual Xfer &xferBool(bool *);
};

extern void __cdecl bfmeCalcTGC(void *, Int *);

struct PathfindCellInfo
{
	char m_pad[0x10];
	unsigned short m_totalCost;
	unsigned short m_costSoFar;
	unsigned int m_first;
	unsigned int m_second;
	unsigned int m_third;
	unsigned int m_fourth;
	unsigned int m_flags;
};

class PathfindCell
{
public:
	void xfer(Xfer *xfer);

	PathfindCellInfo *m_info;
	unsigned int m_zoneAndGoals;
	unsigned short m_cellTypeAndUnitFlags;
	unsigned short m_layerFlags;
	unsigned int m_pathFlags;
};

void PathfindCell::xfer(Xfer *xfer)
{
	if (!xfer->IsCRC())
		return;
	int isFree;
	int blockedByAlly;
	int obstacleIsFence;
	int obstacleIsTransparent;
	int open;
	int cellType;
	int cellLayer;
	int zone;
	int goals;
	int aircraftGoal;
	int pinched;
	int connectsToLayer;
	int lastFlags;
	if (m_info != 0) {
		xfer->slot19(m_info);
		xfer->slot31((char *)m_info + 0x10);
		xfer->slot31((char *)m_info + 0x12);
		bfmeCalcTGC(xfer, (Int *)((char *)m_info + 0x14));
		bfmeCalcTGC(xfer, (Int *)((char *)m_info + 0x18));
		bfmeCalcTGC(xfer, (Int *)((char *)m_info + 0x1c));
		bfmeCalcTGC(xfer, (Int *)((char *)m_info + 0x20));
		isFree = (m_info->m_flags & 1) != 0;
		xfer->xferInt(&isFree);
		blockedByAlly = (m_info->m_flags >> 1 & 1) != 0;
		xfer->xferInt(&blockedByAlly);
		obstacleIsFence = (m_info->m_flags >> 2 & 1) != 0;
		xfer->xferInt(&obstacleIsFence);
		obstacleIsTransparent = (m_info->m_flags >> 3 & 1) != 0;
		xfer->xferInt(&obstacleIsTransparent);
		open = (m_info->m_flags >> 4 & 1) != 0;
		xfer->xferInt(&open);
	}
	xfer->slot31((char *)this + 8);
	xfer->slot31((char *)this + 0xa);
	cellType = m_pathFlags & 7;
	xfer->xferInt(&cellType);
	cellLayer = m_pathFlags >> 3 & 7;
	xfer->xferInt(&cellLayer);
	zone = m_pathFlags >> 6 & 0x3f;
	xfer->xferInt(&zone);
	goals = m_pathFlags >> 12 & 0x3f;
	xfer->xferInt(&goals);
	aircraftGoal = m_pathFlags >> 18 & 1;
	xfer->xferInt(&aircraftGoal);
	pinched = m_pathFlags >> 19 & 1;
	xfer->xferInt(&pinched);
	connectsToLayer = m_pathFlags >> 20 & 1;
	xfer->xferInt(&connectsToLayer);
	lastFlags = m_pathFlags >> 22 & 3;
	xfer->xferInt(&lastFlags);
}
